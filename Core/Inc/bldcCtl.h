#ifndef __BLDC_CTL_H__
#define __BLDC_CTL_H__


#include "IF_Hal.h"

#include "sensHall.h"



enum SIX_STEP_STS{
	BLDC_STEP_HiZ = 0,
	BLDC_STEP_PLUS,
	BLDC_STEP_NEG,
};

enum SIX_STEP_POS_IDX{
	eSECTION_EXCEP1 = 0,
	eSECTION_1 = 1,
	eSECTION_2 = 2,
	eSECTION_3 = 3,
	eSECTION_4 = 4,
	eSECTION_5 = 5,
	eSECTION_6 = 6,
	eSECTION_EXCEP2 = 7,
	eSECTION_MAX = 8
};





typedef struct BldcPwrOut_tage{
	uint8_t U_phase;
	uint8_t V_phase;
	uint8_t W_phase;

}BldcPwrOut_t;


typedef struct BldcHallSection_tag{
	uint8_t ucSection;
	uint8_t ucHallCode;
}BldcHallSect_t;






typedef struct BldcSixStepCtlCtx_tag{
	HallSensePin_t xHallPin;
	BldcHallTb_t xHallTb[eSECTION_MAX]; 
	BldcHallSect_t xHallMatchTb[eSECTION_MAX]; 
	BldcPwrOut_t xPwrOutPattern;
	uint8_t ucHallCombi;
	uint8_t ucIsHallLocFind;
	uint8_t ucDir;
	uint16_t usDuty;
	BldcPWM_Ctx_t* pxPwmCtx;
	TimerCounter_t* pxTmCounter;

}BldcSixStep_CtlCtx_t;


//void BldcPwrOut_t PhaseFind(uint8_t step);


extern BldcSixStep_CtlCtx_t g_xBldcCtlCtx;


void InitBldcPwmCtl(BldcSixStep_CtlCtx_t* pxBldcCtx, BldcPWM_Ctx_t* pxPwmCtx);
void InitBldcMeasRPM(TimerContainer_t* pxTmContainer);



uint8_t Bldc_HallPattern_Set(BldcSixStep_CtlCtx_t* pxCtx, BldcHallSect_t predefinePatt[]);
BldcPwrOut_t HallLocationFind_PwrPattern(uint8_t step);
void ThreePhasePWMGen_1stSucceed(BldcPWM_Ctx_t* pxPwmCtx, BldcPwrOut_t* pxPwrOut, uint16_t usDuty);

BldcPwrOut_t Bldc_Ctl_PhaseCtl_CW(uint8_t ucCurrSection);
BldcPwrOut_t Bldc_Ctl_PhaseCtl_CCW(uint8_t ucCurrSection);

uint8_t Bldc_findHallPattern(BldcSixStep_CtlCtx_t* pxCtx);
void Bldc_CtlMain(BldcSixStep_CtlCtx_t* pxCtx, uint32_t uiDuty);

void HallEdgeDetected(void* args);

#endif
