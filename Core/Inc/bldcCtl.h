#ifndef __BLDC_CTL_H__
#define __BLDC_CTL_H__

#include "main.h"
enum SIX_STEP_STS{
	BLDC_STEP_HiZ = 0,
	BLDC_STEP_PLUS,
	BLDC_STEP_NEG,
};

typedef struct BldcCommTb_tag{
	uint8_t Hall;
	int32_t Rotator_angle;
	uint8_t U_sts;
	uint8_t V_sts;
	uint8_t W_sts;
}BldcCommTb_t;

typedef struct BldcHallTb_tage{
	uint8_t _U;
	uint8_t _V;
	uint8_t _W;

}BldcHallTb_t;

typedef struct BldcPwrOut_tage{
	uint8_t U_phase;
	uint8_t V_phase;
	uint8_t W_phase;

}BldcPwrOut_t;


//void BldcPwrOut_t PhaseFind(uint8_t step);


uint8_t Bldc_findHallPattern();

void Bldc_PhaseCtl();
void Bldc_Phase90Ctl();

uint8_t Bldc_GetHallCode();


#endif
