#ifndef __ST_BOARD_BCM_H__
#define __ST_BOARD_BCM_H__

#include "portStm32_Pwm.h"
#include "portStm32_Timer.h"

#include "IF_pwm.h"
#include "IF_timer.h"
#include "IF_uart.h"

void BSPConfig_TimPwm(BldcPWM_Ctx_t* pxPwmCtx, TimerContainer_t* pxTmContainer,TimerCounter_t* pxTmCounter);


#endif