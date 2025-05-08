#include "IF_pwm.h"
#include "portStm32_Pwm.h"


void PWM_StartStop(BldcPWM_Ctx_t* pxCtx, u8 ucOnOff, u8 ucCh){

    portSTM32_PWM_StartStop(pxCtx, ucCh, ucOnOff);
}


void PWM_Generate(BldcPWM_Ctx_t* pxCtx, u32 uiDuty, u8 ucCh){

    portSTM32_PWM_Generate(pxCtx->pxPwmSrc[ucCh] , uiDuty, pxCtx->uiLookupChTb[ucCh]);
}


void PWM_GenerateMax(BldcPWM_Ctx_t* pxCtx, u8 ucCh){

    portSTM32_PWM_Generate(pxCtx->pxPwmSrc[ucCh] , pxCtx->uiMaxDuty[ucCh], pxCtx->uiLookupChTb[ucCh]);

}



void PWM_Generate_Complementary(BldcPWM_Ctx_t* pxCtx, u32 uiDuty, u8 ucChP, u8 ucChN){


    
}