#include "boardBCM.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim15;

extern ADC_HandleTypeDef hadc1;

MedianFilter_t g_xMedFilter[ADC_MAX_CHANNEL];
AVG_FILTER_VAR g_xAvgFilter[ADC_MAX_CHANNEL];

u16 g_ausAdcRawData[ADC_MAX_CHANNEL];
u16 g_ausAdcFilterData[ADC_MAX_CHANNEL];

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


void BSPConfig_HallSens(HallSensePin_t* _pxHallPin, GpioNode_t* pxHallU, GpioNode_t* pxHallV, GpioNode_t* pxHallW, EdgeCallback cb){

  static Gpio_Pin_t portHw_HallU = {GPIOA, GPE3_BLDC_HU_Pin };
  static Gpio_Pin_t portHw_HallV = {GPIOA, GPE4_BLDC_HV_Pin };
  static Gpio_Pin_t portHw_HallW = {GPIOA, GPE5_BLDC_HW_Pin };


  GpioPin_Def(eHALL_U, GPIO_PIN_EDGE, GPI_FILTER_OFF, pxHallU, (void*)&portHw_HallU);
  GpioPin_Def(eHALL_V, GPIO_PIN_EDGE, GPI_FILTER_OFF, pxHallV, (void*)&portHw_HallV);
  GpioPin_Def(eHALL_W, GPIO_PIN_EDGE, GPI_FILTER_OFF, pxHallW, (void*)&portHw_HallW);

  //HallEdgeDetected
  GpioIsr_RegisterCallback(pxHallU, cb, NULL);
  GpioIsr_RegisterCallback(pxHallV, cb, NULL);
  GpioIsr_RegisterCallback(pxHallW, cb, NULL);


  CheckDuplicate_N_makeList(pxHallU);
  CheckDuplicate_N_makeList(pxHallV);
  CheckDuplicate_N_makeList(pxHallW);

  _pxHallPin->pxU = pxHallU;
  _pxHallPin->pxV = pxHallV;
  _pxHallPin->pxW = pxHallW;


}


void BSPConfig_Analog(AdcModule_t* pxMod, TimerContainer_t* tmContainer){

  static HwAdcWrapper_t xAdcWrapper;

  xAdcWrapper.pxHwAdc = &hadc1;

  InitAdcDrive(pxMod, &xAdcWrapper, g_ausAdcRawData);

  InitAdcDataFilter(pxMod, g_ausAdcFilterData, g_xMedFilter, g_xAvgFilter);

  StartStopAdcDataFilter(pxMod, tmContainer, 1);

  StartStopAdcWithDMA(pxMod, 1);

}