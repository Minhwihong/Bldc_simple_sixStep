#include "boardBCM.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim15;

void BSPConfig_TimPwm(BldcPWM_Ctx_t* pxPwmCtx,  TimerContainer_t* pxTmContainer, TimerCounter_t* pxTmCounter){

  portSTM32_ChannelMatching(pxPwmCtx, &htim1, ePWM_POLE_U_POS, TIM_CHANNEL_1, 3199);
  portSTM32_ChannelMatching(pxPwmCtx, &htim1, ePWM_POLE_U_NEG, TIM_CHANNEL_2, 3199);

  portSTM32_ChannelMatching(pxPwmCtx, &htim1, ePWM_POLE_V_POS, TIM_CHANNEL_3, 3199);
  portSTM32_ChannelMatching(pxPwmCtx, &htim1, ePWM_POLE_V_NEG, TIM_CHANNEL_4, 3199);

  portSTM32_ChannelMatching(pxPwmCtx, &htim15, ePWM_POLE_W_POS, TIM_CHANNEL_1, 3199);
  portSTM32_ChannelMatching(pxPwmCtx, &htim15, ePWM_POLE_W_NEG, TIM_CHANNEL_2, 3199);

  InitTimer(pxTmContainer, (void*)&htim6);

  pxTmCounter->vxHwTimer = (void*)&htim6;
}