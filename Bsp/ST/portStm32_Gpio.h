#ifndef __PORT_STM32_GPIO_H__
#define __PORT_STM32_GPIO_H__

#include "typeSimple.h"
#include "stm32l4xx_hal.h"
#include "IF_gpio.h"

typedef struct {
	GPIO_TypeDef* uiPort;
	u16 usPin;
}Gpio_Pin_t;


void portStm32_GpioDef( GPIO_TypeDef* uiPort, u16 usPin, u8 ucMode, u8 ucUseFilter);
u8 portStm32_readPin(Gpio_Pin_t* pxPin);
void portStm32_writePin(Gpio_Pin_t* pxPin, u8 l_ucPinState);
void portStm32_togglePin(Gpio_Pin_t* pxPin);
void portStm32_OnGpio_EdgeIsr_Callback(u16 usPin);
#endif