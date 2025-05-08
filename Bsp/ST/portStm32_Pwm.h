#ifndef __PORT_STM32_PWM_H__
#define __PORT_STM32_PWM_H__

#include "typeSimple.h"
#include "stm32l4xx_hal.h"
#include "IF_pwm.h"



void portSTM32_PWM_StartStop(BldcPWM_Ctx_t* pxCtx, u8 ucBldcCh, u8 ucOnOff);
void portSTM32_ChannelMatching(BldcPWM_Ctx_t* pxCtx, TIM_HandleTypeDef* pxHwTimer, u8 ucBldcCh, u32 uiHwCh, u32 uiMaxDuty);

void portSTM32_PWM_Generate(void* pxHwTimer, u32 uiDuty, u32 uiCh);


void portSTM32_PWMDual_Generate(void* pxHwTimer, u32 uiDuty, u32 uiChP, u32 uiChN);
void portSTM32_PWMDual_ALLOn(void* pxHwTimer, u32 uiChP, u32 uiChN);
void portSTM32_PWMDual_ALLOff(void* pxHwTimer, u32 uiChP, u32 uiChN);
void portSTM32_PWMDual_Complementary(void* pxHwTimer, u32 uiChP, u32 uiChN, u8 ucMode);

#endif