#ifndef __SENS_HALL_H__
#define __SENS_HALL_H__
#include "IF_Hal.h"


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
    // uint8_t ucHallCombi;

    // GpioNode_t* pxU;
	// GpioNode_t* pxV;
	// GpioNode_t* pxW;

}BldcHallTb_t;



#endif