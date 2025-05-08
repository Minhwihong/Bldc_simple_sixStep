#include "portStm32_Timer.h"

void StartHWTimer(TimerContainer_t* pxTmContainer){

    TIM_HandleTypeDef* pxSTTimer = (TIM_HandleTypeDef*)pxTmContainer->vxHwTimer;

    HAL_TIM_Base_Start_IT(pxSTTimer);
}


void StopHWTimer(TimerContainer_t* pxTmContainer){

    TIM_HandleTypeDef* pxSTTimer = (TIM_HandleTypeDef*)pxTmContainer->vxHwTimer;

    HAL_TIM_Base_Stop_IT(pxSTTimer);
}



void OnTimerPeriodExpired(TimerContainer_t* pxTmContainer){

    HWTimerCallback(pxTmContainer);

}



void portSTM32_InitCountingTimer(TimerCounter_t* pxTimer){

    TIM_HandleTypeDef* pxSTTimer = (TIM_HandleTypeDef*)pxTimer->vxHwTimer;

}


u32 portSTM32_GetTimerCount(TimerCounter_t* pxTimer){

    TIM_HandleTypeDef* pxSTTimer = (TIM_HandleTypeDef*)pxTimer->vxHwTimer;

    return __HAL_TIM_GET_COUNTER(pxSTTimer);
}


void portSTM32_ResetTimerCount(TimerCounter_t* pxTimer){

    TIM_HandleTypeDef* pxSTTimer = (TIM_HandleTypeDef*)pxTimer->vxHwTimer;
    __HAL_TIM_SET_COUNTER(pxSTTimer, 0);
}
