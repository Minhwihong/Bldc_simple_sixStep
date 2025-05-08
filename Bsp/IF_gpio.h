#ifndef __IF_GPIO_H__
#define __IF_GPIO_H__
#include "typeSimple.h"
#include "IF_timer.h"

#define MONO_PIN_HIGH       1
#define MONO_PIN_LOW        0

#define GPIO_PIN_IN 	0
#define GPIO_PIN_OUT 	1
#define GPIO_PIN_EDGE   2

#define GPI_FILTER_ON 		1
#define GPI_FILTER_OFF  	0


typedef void (*EdgeCallback)(void*);

typedef struct _GPIO_T_{
    struct _GPIO_T_ *m_pstNext;

	void* pxGpioPin;
	u8 ucFilter;
	u8 ucValue;
    u8 ucUseFilter;
	u16 usId;
    u8 ucMode;

    EdgeCallback fpEdgeCb;
    void* vxCbArgs;
}GpioNode_t;


typedef struct _GPIO_DRIVER_HEADER_
{
	u16 usTotalNrOfGpio;
	GpioNode_t* pxListHead;
}GpioPinList_Header_t;




typedef struct {
	GpioNode_t* pxU;
	GpioNode_t* pxV;
	GpioNode_t* pxW;
}HallSensePin_t;


void InitGpioList(TimerContainer_t* timSrc) ;
void GpioPin_Def(u16 _usId, u8 _ucMode, u8 _ucUseFilter, GpioNode_t* pxPinNode, void* pxPin);
GpioNode_t *CheckDuplicate_N_makeList(GpioNode_t* pxPin);



uint8_t ReadGpio(GpioNode_t *pxGpioNode);
void WriteGpio(GpioNode_t *pxGpioNode, u8 l_ucPinState);
void ToggleGpio(GpioNode_t *pxGpioNode);


void OnGpio_EdgeIsr_Callback(u16 usPin);
void GpioIsr_RegisterCallback(GpioNode_t* pxPinNode, EdgeCallback fpCb, void* _args);



void DigitalFilterCallback(void *l_pParam);

#endif