#include "bldcCtl.h"
#include "IF_timer.h"
#include "IF_gpio.h"



extern GpioNode_t g_xGpe_HallU ;
extern GpioNode_t g_xGpe_HallV ;
extern GpioNode_t g_xGpe_HallW ;


BldcSixStep_CtlCtx_t g_xBldcCtlCtx;

void CalcPeriod_OverflowCnt(void* args);




void InitBldcMeasRPM(TimerContainer_t* pxTmContainer){
	static TimerTask_t xTmTask1;

	xTmTask1 = CreateTimerTask(CalcPeriod_OverflowCnt, (void*)0, 1, HARD_TIMER_STARTED);
	RegisterTimer(pxTmContainer, &xTmTask1);
}




void InitBldcPwmCtl(BldcSixStep_CtlCtx_t* pxBldcCtx, BldcPWM_Ctx_t* pxPwmCtx){

	PWM_StartStop(pxPwmCtx, 1, ePWM_POLE_U_POS);
	PWM_StartStop(pxPwmCtx, 1, ePWM_POLE_U_NEG);

	PWM_StartStop(pxPwmCtx, 1, ePWM_POLE_V_POS);
	PWM_StartStop(pxPwmCtx, 1, ePWM_POLE_V_NEG);

	PWM_StartStop(pxPwmCtx, 1, ePWM_POLE_W_POS);
	PWM_StartStop(pxPwmCtx, 1, ePWM_POLE_W_NEG);


	pxBldcCtx->pxPwmCtx = pxPwmCtx;
}






uint8_t Bldc_HallPattern_Set(BldcSixStep_CtlCtx_t* pxCtx, BldcHallSect_t predefinePatt[]){

	for(uint8_t hallCode=eSECTION_EXCEP1; hallCode<eSECTION_MAX; ++hallCode){

		pxCtx->xHallMatchTb[hallCode].ucSection = predefinePatt[hallCode].ucSection;
		pxCtx->xHallMatchTb[hallCode].ucHallCode =  predefinePatt[hallCode].ucHallCode;
	}

	return 0;
}


uint8_t Bldc_findHallPattern(BldcSixStep_CtlCtx_t* pxCtx){

	BldcPwrOut_t xPhasePwrOut;
	uint8_t ucHall_u = 0, ucHall_v = 0, ucHall_w = 0;
	uint8_t ucHallCombi = 0;

	pxCtx->xHallTb[0]._U = 0;
	pxCtx->xHallTb[0]._V = 0;
	pxCtx->xHallTb[0]._W = 0;
	pxCtx->xHallMatchTb[0].ucSection = 0;
	pxCtx->xHallMatchTb[0].ucHallCode = 0;

	pxCtx->xHallTb[eSECTION_EXCEP2]._U = 1;
	pxCtx->xHallTb[eSECTION_EXCEP2]._V = 1;
	pxCtx->xHallTb[eSECTION_EXCEP2]._W = 1;
	pxCtx->xHallMatchTb[eSECTION_EXCEP2].ucSection = 0;
	pxCtx->xHallMatchTb[eSECTION_EXCEP2].ucHallCode = (1) + (1 << 1) + (1 << 2);


	for(uint8_t idx=eSECTION_1; idx<eSECTION_EXCEP2; ++idx){

		xPhasePwrOut = HallLocationFind_PwrPattern(idx);

		//PhaseFind, PhaseCtl

		ThreePhasePWMGen_1stSucceed(pxCtx->pxPwmCtx, &xPhasePwrOut, 600);

		HAL_Delay(1000);


		ucHall_u = ReadGpio(pxCtx->xHallPin.pxU);
		ucHall_v = ReadGpio(pxCtx->xHallPin.pxV);
		ucHall_w = ReadGpio(pxCtx->xHallPin.pxW);

		pxCtx->xHallTb[idx]._U = ucHall_u;
		pxCtx->xHallTb[idx]._V = ucHall_v;
		pxCtx->xHallTb[idx]._W = ucHall_w;

		ucHallCombi = (ucHall_u) + (ucHall_v << 1) + (ucHall_w << 2);
		pxCtx->ucHallCombi = ucHallCombi;

		pxCtx->xHallMatchTb[ucHallCombi].ucSection = idx;
		pxCtx->xHallMatchTb[ucHallCombi].ucHallCode =  (ucHall_u) + (ucHall_v << 1) + (ucHall_w << 2);

	}

	xPhasePwrOut = HallLocationFind_PwrPattern(0);
	ThreePhasePWMGen_1stSucceed(pxCtx->pxPwmCtx, &xPhasePwrOut, 0);


	for(uint8_t idx=eSECTION_1; idx<eSECTION_EXCEP2; ++idx){
		if(pxCtx->xHallMatchTb[ucHallCombi].ucSection == 0){
			// Hall Location find fail..
		}
	}

	return 0;
}

void Bldc_CtlMain(BldcSixStep_CtlCtx_t* pxCtx, uint32_t uiDuty){

	uint8_t ucHall_u = 0, ucHall_v = 0, ucHall_w = 0;
	uint8_t ucHallCombi = 0;
	uint8_t ucSection = 0;


	ucHall_u = ReadGpio(pxCtx->xHallPin.pxU);
	ucHall_v = ReadGpio(pxCtx->xHallPin.pxV);
	ucHall_w = ReadGpio(pxCtx->xHallPin.pxW);

	ucHallCombi = (ucHall_u) + (ucHall_v << 1) + (ucHall_w << 2);
	pxCtx->ucHallCombi = ucHallCombi;

	ucSection = pxCtx->xHallMatchTb[ucHallCombi].ucSection;

	if(pxCtx->ucDir == 0){
		pxCtx->xPwrOutPattern = Bldc_Ctl_PhaseCtl_CW(ucSection);
	}
	else {
		pxCtx->xPwrOutPattern = Bldc_Ctl_PhaseCtl_CCW(ucSection);
	}
	

	ThreePhasePWMGen_1stSucceed(pxCtx->pxPwmCtx, &pxCtx->xPwrOutPattern, pxCtx->usDuty);
}




BldcPwrOut_t Bldc_Ctl_PhaseCtl_CW(uint8_t ucCurrSection){

	BldcPwrOut_t pwrOut;

	switch(ucCurrSection){

		case 1:	// Section #1
			pwrOut.U_phase = BLDC_STEP_NEG;
			pwrOut.V_phase = BLDC_STEP_PLUS;
			pwrOut.W_phase = BLDC_STEP_HiZ;
			break;

		case 2:	// Section #2
			pwrOut.U_phase = BLDC_STEP_NEG;
			pwrOut.V_phase = BLDC_STEP_HiZ;
			pwrOut.W_phase = BLDC_STEP_PLUS;
			break;

		case 3:	// Section #3
			pwrOut.U_phase = BLDC_STEP_HiZ;
			pwrOut.V_phase = BLDC_STEP_NEG;
			pwrOut.W_phase = BLDC_STEP_PLUS;
			break;

		case 4:	// Section #4
			pwrOut.U_phase = BLDC_STEP_PLUS;
			pwrOut.V_phase = BLDC_STEP_NEG;
			pwrOut.W_phase = BLDC_STEP_HiZ;
			break;

		case 5:	// Section #5
			pwrOut.U_phase = BLDC_STEP_PLUS;
			pwrOut.V_phase = BLDC_STEP_HiZ;
			pwrOut.W_phase = BLDC_STEP_NEG;
			break;

		case 6:	// Section #6
			pwrOut.U_phase = BLDC_STEP_HiZ;
			pwrOut.V_phase = BLDC_STEP_PLUS;
			pwrOut.W_phase = BLDC_STEP_NEG;
			break;


		default:
			pwrOut.U_phase = BLDC_STEP_HiZ;
			pwrOut.V_phase = BLDC_STEP_HiZ;
			pwrOut.W_phase = BLDC_STEP_HiZ;
			break;
		}

	return pwrOut;
}





BldcPwrOut_t Bldc_Ctl_PhaseCtl_CCW(uint8_t ucCurrSection){

	BldcPwrOut_t pwrOut;

	switch(ucCurrSection){

		case 1:	// Section #1
			pwrOut.U_phase = BLDC_STEP_PLUS;		// 0
			pwrOut.V_phase = BLDC_STEP_NEG;		// -
			pwrOut.W_phase = BLDC_STEP_HiZ;	// +
			break;

		case 2:	// Section #2
			pwrOut.U_phase = BLDC_STEP_PLUS;	// +	
			pwrOut.V_phase = BLDC_STEP_HiZ;		// 0
			pwrOut.W_phase = BLDC_STEP_NEG;		// -
			break;

		case 3:	// Section #3
			pwrOut.U_phase = BLDC_STEP_HiZ;		
			pwrOut.V_phase = BLDC_STEP_PLUS;		
			pwrOut.W_phase = BLDC_STEP_NEG;		
			break;

		case 4:	// Section #4
			pwrOut.U_phase = BLDC_STEP_NEG;		
			pwrOut.V_phase = BLDC_STEP_PLUS;		
			pwrOut.W_phase = BLDC_STEP_HiZ;		
			break;

		case 5:	// Section #5
			pwrOut.U_phase = BLDC_STEP_NEG;		
			pwrOut.V_phase = BLDC_STEP_HiZ;		
			pwrOut.W_phase = BLDC_STEP_PLUS;		
			break;

		case 6:	// Section #6
			pwrOut.U_phase = BLDC_STEP_HiZ;
			pwrOut.V_phase = BLDC_STEP_NEG;
			pwrOut.W_phase = BLDC_STEP_PLUS;
			break;


		default:
			pwrOut.U_phase = BLDC_STEP_HiZ;
			pwrOut.V_phase = BLDC_STEP_HiZ;
			pwrOut.W_phase = BLDC_STEP_HiZ;
			break;
		}

	return pwrOut;
}







BldcPwrOut_t HallLocationFind_PwrPattern(uint8_t step){

	BldcPwrOut_t pwrOut;

	switch(step){

		case 1:	// Section #1
			pwrOut.U_phase = BLDC_STEP_PLUS;
			pwrOut.V_phase = BLDC_STEP_NEG;
			pwrOut.V_phase = BLDC_STEP_NEG;
			break;


		case 2:	// Section #2
			pwrOut.U_phase = BLDC_STEP_PLUS;
			pwrOut.V_phase = BLDC_STEP_PLUS;
			pwrOut.W_phase = BLDC_STEP_NEG;
			break;

		case 3:	// Section #3
			pwrOut.U_phase = BLDC_STEP_NEG;
			pwrOut.V_phase = BLDC_STEP_PLUS;
			pwrOut.W_phase = BLDC_STEP_NEG;
			break;

		case 4:	// Section #4
			pwrOut.U_phase = BLDC_STEP_NEG;
			pwrOut.V_phase = BLDC_STEP_PLUS;
			pwrOut.W_phase = BLDC_STEP_PLUS;
			break;

		case 5:	// Section #5
			pwrOut.U_phase = BLDC_STEP_NEG;
			pwrOut.V_phase = BLDC_STEP_NEG;
			pwrOut.W_phase = BLDC_STEP_PLUS;
			break;

		case 6:	// Section #6
			pwrOut.U_phase = BLDC_STEP_PLUS;
			pwrOut.V_phase = BLDC_STEP_NEG;
			pwrOut.W_phase = BLDC_STEP_PLUS;
			break;


		default:
			pwrOut.U_phase = BLDC_STEP_HiZ;
			pwrOut.V_phase = BLDC_STEP_HiZ;
			pwrOut.W_phase = BLDC_STEP_HiZ;
			break;
	}

	return pwrOut;
}




void ThreePhasePWMGen_1stSucceed(BldcPWM_Ctx_t* pxPwmCtx, BldcPwrOut_t* pxPwrOut, uint16_t usDuty){

	switch(pxPwrOut->U_phase){
			case BLDC_STEP_HiZ:
				PWM_Generate(pxPwmCtx, 0, ePWM_POLE_U_POS);
				PWM_Generate(pxPwmCtx, 0, ePWM_POLE_U_NEG);
				break;
			case BLDC_STEP_PLUS:
				PWM_Generate(pxPwmCtx, usDuty, 	ePWM_POLE_U_POS);
				PWM_Generate(pxPwmCtx, 0, 		ePWM_POLE_U_NEG);
				break;
			case BLDC_STEP_NEG:
				PWM_Generate(pxPwmCtx, 0, ePWM_POLE_U_POS);
				PWM_GenerateMax(pxPwmCtx, ePWM_POLE_U_NEG);
				break;
			default:
				break;
		}

		switch(pxPwrOut->V_phase){
			case BLDC_STEP_HiZ:
				PWM_Generate(pxPwmCtx, 0, ePWM_POLE_V_POS);
				PWM_Generate(pxPwmCtx, 0, ePWM_POLE_V_NEG);
				break;
			case BLDC_STEP_PLUS:
				PWM_Generate(pxPwmCtx, usDuty, 	ePWM_POLE_V_POS);
				PWM_Generate(pxPwmCtx, 0, 		ePWM_POLE_V_NEG);
				break;
			case BLDC_STEP_NEG:
				PWM_Generate(pxPwmCtx, 0, ePWM_POLE_V_POS);
				PWM_GenerateMax(pxPwmCtx, ePWM_POLE_V_NEG);
				break;
			default:
				break;
		}

		switch(pxPwrOut->W_phase){
			case BLDC_STEP_HiZ:
				PWM_Generate(pxPwmCtx, 0, ePWM_POLE_W_POS);
				PWM_Generate(pxPwmCtx, 0, ePWM_POLE_W_NEG);
				break;
			case BLDC_STEP_PLUS:
				PWM_Generate(pxPwmCtx, usDuty, 	ePWM_POLE_W_POS);
				PWM_Generate(pxPwmCtx, 0, 		ePWM_POLE_W_NEG);
				break;
			case BLDC_STEP_NEG:
				PWM_Generate(pxPwmCtx, 0, ePWM_POLE_W_POS);
				PWM_GenerateMax(pxPwmCtx, ePWM_POLE_W_NEG);
				break;
			default:
				break;
		}
}



uint32_t g_uiOverFlowCnt = 0;
uint32_t g_uiElectricPeriod = 0;
float g_fElectricRPM = 0.0f;
uint8_t g_ucMeasRpmHall = 5;


void CalcPeriod_OverflowCnt(void* args){
	g_uiOverFlowCnt++;
}

// Unit 1usec
uint32_t GetRotatePerPeriod(TimerCounter_t* pxCntTimer){

  uint32_t l_uiCurTimeCnt;
  uint32_t uiPeriod = 0;


//   l_uiCurTimeCnt = __HAL_TIM_GET_COUNTER(&htim6);
//   __HAL_TIM_SET_COUNTER(&htim6, 0);

  l_uiCurTimeCnt = GetTimerCount(pxCntTimer);
  ResetTimerCount(pxCntTimer);

  uiPeriod = l_uiCurTimeCnt + (g_uiOverFlowCnt * 1000);


  g_uiOverFlowCnt = 0;
  

  return uiPeriod;
}


float GetPRM_fromPeriod(float uiPeriod){

  float fRotPerSec = 0.0f;
  float fRPM = 0.0f;

  if(uiPeriod > 0 ){

      fRotPerSec = 1000.0f / (0.001f * uiPeriod);

      fRPM = fRotPerSec * 60.0f;
  }
  else {
      fRPM = 0.0f;
  }
  

  return fRPM;
}





void HallEdgeDetected(void* args){
	uint8_t ucHall_u = 0, ucHall_v = 0, ucHall_w = 0;
	uint8_t ucHallCombi = 0;

	ucHall_u = ReadGpio(g_xBldcCtlCtx.xHallPin.pxU);
	ucHall_v = ReadGpio(g_xBldcCtlCtx.xHallPin.pxV);
	ucHall_w = ReadGpio(g_xBldcCtlCtx.xHallPin.pxW);

	ucHallCombi = (ucHall_u) + (ucHall_v << 1) + (ucHall_w << 2);

	if(ucHallCombi == 5){
		g_uiElectricPeriod = GetRotatePerPeriod(g_xBldcCtlCtx.pxTmCounter);
		g_fElectricRPM = GetPRM_fromPeriod(g_uiElectricPeriod);
	}
}
