#include "portStm32_Pwm.h"


void portSTM32_PWM_StartStop(BldcPWM_Ctx_t* pxCtx, u8 ucBldcCh, u8 ucOnOff){

    TIM_HandleTypeDef* pxHwTimer = (TIM_HandleTypeDef*)pxCtx->pxPwmSrc[ucBldcCh];
    u32 uiTmChannel = pxCtx->uiLookupChTb[ucBldcCh];

    if(ucOnOff != 0){
        HAL_TIM_PWM_Start(pxHwTimer, uiTmChannel);
    }
    else {
        HAL_TIM_PWM_Stop(pxHwTimer, uiTmChannel);
    }
}



void portSTM32_ChannelMatching(BldcPWM_Ctx_t* pxCtx, TIM_HandleTypeDef* pxHwTimer, u8 ucBldcCh, u32 uiHwCh, u32 uiMaxDuty){

    pxCtx->uiLookupChTb[ucBldcCh] = uiHwCh;
    pxCtx->pxPwmSrc[ucBldcCh] = (void*)pxHwTimer;
    pxCtx->uiMaxDuty[ucBldcCh] = uiMaxDuty;
}



void portSTM32_PWM_Generate(void* vxHwTimer, u32 uiDuty, u32 uiCh){
    
    TIM_HandleTypeDef* pxHwTimer = (TIM_HandleTypeDef*)vxHwTimer;
    
    __HAL_TIM_SET_COMPARE(pxHwTimer, uiCh, uiDuty) ;
}


