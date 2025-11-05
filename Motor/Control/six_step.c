#include "six_step.h"
#include "main.h"
#include "L6398.h"
#include "boardNuclG431.h"

// IGpio_t g_xGpe_HallU ;
// IGpio_t g_xGpe_HallV ;
// IGpio_t g_xGpe_HallW ;


void Init_6Step_Unipolar(_6StepCtlCtx_t* ctx, void* pvDriver){


	ctx->fpCommTb_unipolar = Apply_L6398_CommutationUnipolar;
	ctx->fSetDuty = 0;
	ctx->pvDriver = pvDriver;

	PlatformConfig_HallSens_ISR(&ctx->xGpe_HallU, &ctx->xGpe_HallV, &ctx->xGpe_HallW, 
		OnEdge_Commutation_withHallSens, (void*)&ctx);
}







void OnEdge_Commutation_withHallSens(void* args)
{
    uint8_t state = 0;
	uint8_t read = 0;
	_6StepCtlCtx_t* px6Step = (_6StepCtlCtx_t*)args;

	

	read = ReadGpio(&px6Step->xGpe_HallU);
	
    if (read != 0){
    	state |= 0x01;
    }

	read = ReadGpio(&px6Step->xGpe_HallV);

	if (read != 0){
		state |= 0x02;
	}


	read = ReadGpio(&px6Step->xGpe_HallW);

	if (read != 0){
		state |= 0x04;
	}



	px6Step->fpCommTb_unipolar(px6Step->pvDriver, state,  px6Step->fSetDuty );
}





void CliControl(cli_args_t *args, void* param){

	_6StepCtlCtx_t* px6Step = (_6StepCtlCtx_t*)param;


	if(args->argc >= 1 ){

		if(args->isStr(0, "rpm") == 1){
			int rpm;
			rpm = args->getData(1);

			if(0 < rpm < 9000){
				px6Step->uiSetRpm = rpm;
			}

		}
		else if(args->isStr(0, "duty") == 1){
			float duty;

			duty = args->getFloat(1);

			if(0 < duty < 90){
				px6Step->fSetDuty = duty;
			}
		}
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
