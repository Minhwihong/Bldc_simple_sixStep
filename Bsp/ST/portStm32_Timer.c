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