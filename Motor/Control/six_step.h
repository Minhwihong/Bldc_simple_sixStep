#ifndef __BLDC_SIX_STEP_CTL_H__
#define __BLDC_SIX_STEP_CTL_H__


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


#if 0
BldcHallSect_t g_xBCMMotorHallLoc[eSECTION_MAX] = {
	{0, 0},		// {ucSection, ucHallCode}
	{6, 1},		// section #6 - Hall #1
	{2, 2},		// section #2 - Hall #2
	{1, 3},		// section #1 - Hall #3
	{4, 4},		// section #4 - Hall #4
	{5, 5},		// section #5 - Hall #5
	{3, 6},		// section #3 - Hall #6
	{7, 7},		//
};


BldcHallSect_t g_xJK42MotorHallLoc[eSECTION_MAX] = {
	{0, 0},		//
	{3, 1},		// section #3 - Hall #1
	{5, 2},		// section #5 - Hall #2
	{4, 3},		// section #4 - Hall #3
	{1, 4},		// section #1 - Hall #4
	{2, 5},		// section #2 - Hall #5
	{6, 6},		// section #6 - Hall #6
	{7, 7},		//
};
#endif


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
