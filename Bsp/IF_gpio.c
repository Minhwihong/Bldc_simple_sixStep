#include "portStm32_Gpio.h"
#include "IF_gpio.h"


GpioPinList_Header_t g_stGpioDriverHeader;




void InitGpioList(TimerContainer_t* timSrc) {

	g_stGpioDriverHeader.pxListHead = NULL;
    g_stGpioDriverHeader.usTotalNrOfGpio = 0;

    // static TimerTask_t xTmTask_digitFilt;

	// xTmTask_digitFilt = CreateTimerTask(DigitalFilterCallback, (void*)0, 1, HARD_TIMER_STARTED);
    // RegisterTimer(timSrc, &xTmTask_digitFilt);

}


void GpioPin_Def(u16 _usId, u8 _ucMode, u8 _ucUseFilter, GpioNode_t* pxPinNode, void* _pxPin){

    Gpio_Pin_t* pxPin = ( Gpio_Pin_t*)_pxPin;

    pxPinNode->pxGpioPin = (void*)pxPin;
    pxPinNode->usId = _usId;
    pxPinNode->ucMode = _ucMode;
    pxPinNode->ucUseFilter = _ucUseFilter;
    

    pxPinNode->ucValue = 0;
    pxPinNode->ucFilter = 0;
    pxPinNode->m_pstNext = NULL;
}


void GpioIsr_RegisterCallback(GpioNode_t* pxPinNode, EdgeCallback fpCb, void* _args){

    if(pxPinNode->ucMode == GPIO_PIN_EDGE){
        pxPinNode->fpEdgeCb = fpCb;
        pxPinNode->vxCbArgs = _args;
    }
}



GpioNode_t *CheckDuplicate_N_makeList(GpioNode_t* pxNode)
{
	GpioNode_t *l_pstCurNode = NULL;

    if(g_stGpioDriverHeader.pxListHead == NULL){

        g_stGpioDriverHeader.pxListHead = pxNode;
        g_stGpioDriverHeader.usTotalNrOfGpio++;
        return pxNode;
    }

	l_pstCurNode = g_stGpioDriverHeader.pxListHead;

	if(l_pstCurNode->usId == pxNode->usId){
		return NULL;
	}


//	do{
//		if(l_pstCurNode->usId == pxNode->usId){
//            return NULL;
//        }
//
//		l_pstCurNode = l_pstCurNode->m_pstNext;
//
//	}while( l_pstCurNode->m_pstNext != NULL );

	while( l_pstCurNode->m_pstNext != NULL ){

		l_pstCurNode = l_pstCurNode->m_pstNext;

		if(l_pstCurNode->usId == pxNode->usId){
			return NULL;
		}

	}

    l_pstCurNode->m_pstNext = pxNode;
    g_stGpioDriverHeader.usTotalNrOfGpio++;

	return pxNode;
}




void DigitalFilterCallback(void *l_pParam)
{
	int i;
	uint8_t l_ucDiTemp;
	GpioNode_t *l_pstCurNode;


	l_pstCurNode = g_stGpioDriverHeader.pxListHead;

	for( i= 0; i<g_stGpioDriverHeader.usTotalNrOfGpio ; i++ ){

		if( l_pstCurNode->ucMode == GPIO_PIN_IN ) {

			l_ucDiTemp = ReadGpio(l_pstCurNode);

			if( l_pstCurNode->ucUseFilter ==  GPI_FILTER_ON) {

				l_pstCurNode->ucFilter <<= 1;
                l_pstCurNode->ucFilter= l_pstCurNode->ucFilter | l_ucDiTemp;

                if(l_pstCurNode->ucFilter == 0x00 ) {

                    l_pstCurNode->ucValue = 0;
                }
                else if(l_pstCurNode->ucFilter == 0xFF) {

                    l_pstCurNode->ucValue = 1;
                }
			}
			else {

				l_pstCurNode->ucValue = l_ucDiTemp;
			}
		}

		l_pstCurNode = l_pstCurNode->m_pstNext;
	}
}



uint8_t ReadGpio(GpioNode_t *pxGpioNode)
{
	return portStm32_readPin((Gpio_Pin_t*)pxGpioNode->pxGpioPin);
}

void WriteGpio(GpioNode_t *pxGpioNode, u8 l_ucPinState)
{
	pxGpioNode->ucValue = l_ucPinState;

    portStm32_writePin((Gpio_Pin_t*)pxGpioNode->pxGpioPin, pxGpioNode->ucValue);
}

void ToggleGpio(GpioNode_t *pxGpioNode)
{
    portStm32_togglePin((Gpio_Pin_t*)pxGpioNode->pxGpioPin);

}


void OnGpio_EdgeIsr_Callback(u16 _usPin){

    GpioNode_t *l_pstCurNode;
    

	l_pstCurNode = g_stGpioDriverHeader.pxListHead;

    for(u16 i= 0; i<g_stGpioDriverHeader.usTotalNrOfGpio ; i++ ){

        Gpio_Pin_t* pxPin = (Gpio_Pin_t*)l_pstCurNode->pxGpioPin;

        if(pxPin->usPin == _usPin && l_pstCurNode->ucMode == GPIO_PIN_EDGE && l_pstCurNode->fpEdgeCb != NULL ) {

            l_pstCurNode->fpEdgeCb(l_pstCurNode->vxCbArgs);
        }

        l_pstCurNode = l_pstCurNode->m_pstNext;

    }
}
