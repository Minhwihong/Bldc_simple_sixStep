#ifndef __BLDC_SIX_STEP_CTL_H__
#define __BLDC_SIX_STEP_CTL_H__


#include "IF_Hal.h"
#include "motor_term_def.h"
#include "sensHall.h"


enum e6STEP_CTL{
	e6STEP_CTL_UNIPOLAR = 0,
	e6STEP_CTL_BIPOLAR,
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

typedef void (*ApplyPwrCb)(uint8_t state, float pwmVal);

typedef struct _6StepCtlCtx_tag{
	ApplyPwrCb cb;
	float* pfDuty;
}_6StepCtlCtx_t;


//void BldcPwrOut_t PhaseFind(uint8_t step);



void OnEdge_Commutation_withHallSens(void* args);




void Init_6Step_L6398_Unipolar(void* args);
void Apply_L6398_CommutationUnipolar(uint8_t state, float pwmVal);

//void HallEdgeDetected(void* args);

#endif
