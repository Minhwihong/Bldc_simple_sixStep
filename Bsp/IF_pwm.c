#include "IF_pwm.h"


void PWM_StartStop(BldcPWM_Ctx_t* pxCtx, u8 ucOnOff, u8 ucCh){

    portSTM32_PWM_StartStop(pxCtx->pxPwmSrc[ucCh], ucOnOff);
}



void PWM_ChannelMatching(BldcPWM_Ctx_t* pxBldcCtx, Pwm1Ch_HwWrapper* pxHw, u8 ucBldcCh){

    pxBldcCtx->pxPwmSrc[ucBldcCh] = pxHw;
    pxBldcCtx->ucChId[ucBldcCh] = ucBldcCh;
    pxBldcCtx->uiMaxDuty[ucBldcCh] = pxHw->uiMaxDuty;
    //pxBldcCtx->ucChId = 
}


void PWM_Generate(BldcPWM_Ctx_t* pxCtx, u32 uiDuty, u8 ucCh){

    portSTM32_PWM_Generate(pxCtx->pxPwmSrc[ucCh] , uiDuty);
}


void PWM_GenerateMax(BldcPWM_Ctx_t* pxCtx, u8 ucCh){

    portSTM32_PWM_Generate(pxCtx->pxPwmSrc[ucCh] , pxCtx->pxPwmSrc[ucCh]->uiMaxDuty);

}





void PWMDual_Init(){


}

void PWMDual_StartStop(Bldc_DualPWM_Ctx_t* pxCtx, u8 ucOnOff, u8 ucCh){

    portSTM32_PWMDual_StartStop(pxCtx->pxPwmSrc[ucCh], ucOnOff);
}

void PWMDual_Generate(Bldc_DualPWM_Ctx_t* pxCtx, u8 ucCh, u32 uiDuty){

    portSTM32_PWMDual_Generate(pxCtx->pxPwmSrc[ucCh], uiDuty);
}

void PWMDual_NChannelHigh(Bldc_DualPWM_Ctx_t* pxCtx, u8 ucCh ){

    portSTM32_PWMDual_NChannelHigh(pxCtx->pxPwmSrc[ucCh]);
}

void PWMDual_NChannelLow(Bldc_DualPWM_Ctx_t* pxCtx, u8 ucCh){

    portSTM32_PWMDual_NChannelLow(pxCtx->pxPwmSrc[ucCh]);
}

void PWMDual_Complementary(Bldc_DualPWM_Ctx_t* pxCtx, PWM_Complementary_t* xCh, u8 ucMode){


}
