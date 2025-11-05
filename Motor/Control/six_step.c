#include "six_step.h"
#include "main.h"
#include "L6398.h"
#include "boardNuclG431.h"

IGpio_t g_xGpe_HallU ;
IGpio_t g_xGpe_HallV ;
IGpio_t g_xGpe_HallW ;




static float g_fDuty = 0.0f;

static L6398_Unipolar_t g_xDriverUniPolar;
static _6StepCtlCtx_t g_xCtlUniPolar;



//static void OnEdge_Commutation_withHallSens(void* args);




void Init_6Step_L6398_Unipolar(void* args){


	InitDriver_Unipolar(&g_xDriverUniPolar);

	g_xCtlUniPolar.cb = Apply_L6398_CommutationUnipolar;
	g_xCtlUniPolar.pfDuty = &g_fDuty;


	PlatformConfig_HallSens_ISR(&g_xGpe_HallU, &g_xGpe_HallU, &g_xGpe_HallU, 
		OnEdge_Commutation_withHallSens, (void*)&g_xCtlUniPolar);
}







void OnEdge_Commutation_withHallSens(void* args)
{
    uint8_t state = 0;
	uint8_t read = 0;
	_6StepCtlCtx_t* fCtl = (_6StepCtlCtx_t*)args;

	read = ReadGpio(&g_xGpe_HallU);
	
    if (read != 0){
    	state |= 0x01;
    }

	read = ReadGpio(&g_xGpe_HallV);

	if (read != 0){
		state |= 0x02;
	}


	read = ReadGpio(&g_xGpe_HallW);

	if (read != 0){
		state |= 0x04;
	}



	fCtl->cb( state,  *(fCtl->pfDuty) );
}





void Apply_L6398_CommutationUnipolar(uint8_t state, float pwmVal)
{
	switch (state)
	{
		case 4:  // Hall: 001 -> B-PWM, C-Low
			//DrvL6398_6Step_UniPolar_GateCtl(L6398_Unipolar_t* pxDrv, u8 phase, u8 ctl, float duty)
			DrvL6398_6Step_UniPolar_GateCtl(&g_xDriverUniPolar, POLE_U, _6STEP_PWM_IN, (float)pwmVal);
			DrvL6398_6Step_UniPolar_GateCtl(&g_xDriverUniPolar, POLE_V, _6STEP_HiZ, (float)0);
			DrvL6398_6Step_UniPolar_GateCtl(&g_xDriverUniPolar, POLE_W, _6STEP_LOWSIDE_ON, (float)0);
			break;

		case 2:  // Hall: 010 -> A-PWM, C-Low  -----
            DrvL6398_6Step_UniPolar_GateCtl(&g_xDriverUniPolar, POLE_U, _6STEP_LOWSIDE_ON, 0);  // A: Low
			DrvL6398_6Step_UniPolar_GateCtl(&g_xDriverUniPolar, POLE_V, _6STEP_PWM_IN, pwmVal); // B: PWM
			DrvL6398_6Step_UniPolar_GateCtl(&g_xDriverUniPolar, POLE_W, _6STEP_HiZ, 0);  		// C: Off
			break;

		case 6:  // Hall: 011 -> A-PWM, B-Low
			DrvL6398_6Step_UniPolar_GateCtl(&g_xDriverUniPolar, POLE_U, _6STEP_HiZ, 0);  		// A: Off
			DrvL6398_6Step_UniPolar_GateCtl(&g_xDriverUniPolar, POLE_V, _6STEP_PWM_IN, pwmVal); // B: PWM
			DrvL6398_6Step_UniPolar_GateCtl(&g_xDriverUniPolar, POLE_W, _6STEP_LOWSIDE_ON, 0);  // C: Low
			break;

		case 1:  // Hall: 100 -> C-PWM, A-Low
			DrvL6398_6Step_UniPolar_GateCtl(&g_xDriverUniPolar, POLE_U, _6STEP_HiZ, 0);  		// A: Off
			DrvL6398_6Step_UniPolar_GateCtl(&g_xDriverUniPolar, POLE_V, _6STEP_LOWSIDE_ON, 0);  // B: Low
			DrvL6398_6Step_UniPolar_GateCtl(&g_xDriverUniPolar, POLE_W, _6STEP_PWM_IN, pwmVal); // C: PWM
			break;

		case 5:  // Hall: 101 -> C-PWM, B-Low
			DrvL6398_6Step_UniPolar_GateCtl(&g_xDriverUniPolar, POLE_U, _6STEP_PWM_IN, pwmVal); // A: PWM
			DrvL6398_6Step_UniPolar_GateCtl(&g_xDriverUniPolar, POLE_V, _6STEP_LOWSIDE_ON, 0);  // B: Low
			DrvL6398_6Step_UniPolar_GateCtl(&g_xDriverUniPolar, POLE_W, _6STEP_HiZ, 0);  		// C: Off
			break;

		case 3:  // Hall: 110 -> B-PWM, A-Low
			DrvL6398_6Step_UniPolar_GateCtl(&g_xDriverUniPolar, POLE_U, _6STEP_LOWSIDE_ON, 0);  // A: Low
			DrvL6398_6Step_UniPolar_GateCtl(&g_xDriverUniPolar, POLE_V, _6STEP_HiZ, 0);  		// B: Off
			DrvL6398_6Step_UniPolar_GateCtl(&g_xDriverUniPolar, POLE_W, _6STEP_PWM_IN, pwmVal); // C: PWM
			break;

        case 7:  // align
			DrvL6398_6Step_UniPolar_GateCtl(&g_xDriverUniPolar,POLE_U, _6STEP_PWM_IN, pwmVal);  
			DrvL6398_6Step_UniPolar_GateCtl(&g_xDriverUniPolar,POLE_V, _6STEP_LOWSIDE_ON, 0);  	
			DrvL6398_6Step_UniPolar_GateCtl(&g_xDriverUniPolar,POLE_W, _6STEP_LOWSIDE_ON, 0);  	
			break;

		default:  // Invalid states (0, 7)
			DrvL6398_6Step_UniPolar_GateCtl(&g_xDriverUniPolar, POLE_U, _6STEP_HiZ, 0);  // A: Off
			DrvL6398_6Step_UniPolar_GateCtl(&g_xDriverUniPolar, POLE_V, _6STEP_HiZ, 0);  // B: Off
			DrvL6398_6Step_UniPolar_GateCtl(&g_xDriverUniPolar, POLE_W, _6STEP_HiZ, 0);  // C: Off
			break;
	}
}








#if 0
uint16_t g_usMaxPowerTm = 0;
uint32_t g_uiOverFlowCnt = 0;
uint32_t g_uiElectricPeriod = 0;
float g_fElectricRPM = 0.0f;
uint8_t g_ucMeasRpmHall = 5;
void CalcPeriod_OverflowCnt(void* args);


void InitBldcMeasRPM(TimerContainer_t* pxTmContainer){
	static TimerTask_t xTmTask1;

	xTmTask1 = CreateTimerTask(CalcPeriod_OverflowCnt, (void*)0, 1, HARD_TIMER_STARTED);
	RegisterTimer(pxTmContainer, &xTmTask1);
}

void CalcPeriod_OverflowCnt(void* args){
	g_uiOverFlowCnt++;

	if(g_usMaxPowerTm != 0){
		g_usMaxPowerTm--;
	}
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

	// ucHall_u = ReadGpio(g_xBldcCtlCtx.xHallPin.pxU);
	// ucHall_v = ReadGpio(g_xBldcCtlCtx.xHallPin.pxV);
	// ucHall_w = ReadGpio(g_xBldcCtlCtx.xHallPin.pxW);

	ucHallCombi = (ucHall_u) + (ucHall_v << 1) + (ucHall_w << 2);

	if(ucHallCombi == 5){
		// g_uiElectricPeriod = GetRotatePerPeriod(g_xBldcCtlCtx.pxTmCounter);
		// g_fElectricRPM = GetPRM_fromPeriod(g_uiElectricPeriod);
	}
}
#endif
