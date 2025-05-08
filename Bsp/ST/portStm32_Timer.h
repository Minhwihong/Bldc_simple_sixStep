#ifndef __PORT_STM32_TIMER_H__
#define __PORT_STM32_TIMER_H__

#include "typeSimple.h"


#include "stm32l4xx_hal.h"

#include "IF_timer.h"




void StopHWTimer(TimerContainer_t* pxTmContainer);
void StartHWTimer(TimerContainer_t* pxTmContainer);
void OnTimerPeriodExpired(TimerContainer_t* xInterface);


void portSTM32_InitCountingTimer(TimerCounter_t* pxTimer);
u32 portSTM32_GetTimerCount(TimerCounter_t* pxTimer);
void portSTM32_ResetTimerCount(TimerCounter_t* pxTimer);


#endif