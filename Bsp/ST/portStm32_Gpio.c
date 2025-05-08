#include "portStm32_Gpio.h"


void portStm32_GpioDef( GPIO_TypeDef* uiPort, u16 usPin, u8 ucMode, u8 ucUseFilter){


}


u8 portStm32_readPin(Gpio_Pin_t* pxPin){

    return HAL_GPIO_ReadPin(pxPin->uiPort, pxPin->usPin);
}


void portStm32_writePin(Gpio_Pin_t* pxPin, u8 l_ucPinState){

    HAL_GPIO_WritePin(pxPin->uiPort, pxPin->usPin, l_ucPinState );
}


void portStm32_togglePin(Gpio_Pin_t* pxPin){

    HAL_GPIO_TogglePin(pxPin->uiPort, pxPin->usPin);
    

}


void portStm32_OnGpio_EdgeIsr_Callback(u16 usPin){

    OnGpio_EdgeIsr_Callback(usPin);
    
}
