#include "L6398.h"
#include "boardNuclG431.h"

IPwm_t g_xPwm_phaseU_highside;
IPwm_t g_xPwm_phaseV_highside;
IPwm_t g_xPwm_phaseW_highside;

IGpio_t g_xGpo_phaseU_lowside;
IGpio_t g_xGpo_phaseV_lowside;
IGpio_t g_xGpo_phaseW_lowside;

void InitDriver_Unipolar(L6398_Unipolar_t* pxDrive){

    PlatformConfig_6stepUniPolar(&g_xPwm_phaseU_highside, &g_xPwm_phaseV_highside, &g_xPwm_phaseW_highside,
		&g_xGpo_phaseU_lowside, &g_xGpo_phaseU_lowside, &g_xGpo_phaseU_lowside);



	pxDrive->pxPwmU_highSide = &g_xPwm_phaseU_highside;
	pxDrive->pxPinU_lowSide = &g_xGpo_phaseU_lowside;

	pxDrive->pxPwmV_highSide = &g_xPwm_phaseV_highside;
	pxDrive->pxPinV_lowSide = &g_xGpo_phaseV_lowside;

	pxDrive->pxPwmW_highSide = &g_xPwm_phaseW_highside;
	pxDrive->pxPinW_lowSide = &g_xGpo_phaseW_lowside;


// 	g_xDriverUniPolar.pxPwmU_highSide = &g_xPwm_phaseU_highside;
// 	g_xDriverUniPolar.pxPinU_lowSide = &g_xGpo_phaseU_lowside;

// 	g_xDriverUniPolar.pxPwmV_highSide = &g_xPwm_phaseV_highside;
// 	g_xDriverUniPolar.pxPinV_lowSide = &g_xGpo_phaseV_lowside;

// 	g_xDriverUniPolar.pxPwmW_highSide = &g_xPwm_phaseW_highside;
// 	g_xDriverUniPolar.pxPinW_lowSide = &g_xGpo_phaseW_lowside;
}







void DrvL6398_6Step_UniPolar_GateCtl(L6398_Unipolar_t* pxDrv, u8 phase, u8 ctl, float duty){


    switch (phase)
    {
        case POLE_U:  // Phase A
            switch(ctl){
                case _6STEP_HiZ:
                    Pwm1_Generate(pxDrv->pxPwmU_highSide, 0.0f);
                    WriteGpio(pxDrv->pxPinU_lowSide, MONO_PIN_HIGH);
                    break;

                case _6STEP_PWM_IN:
                    Pwm1_Generate(pxDrv->pxPwmU_highSide, duty);
                    WriteGpio(pxDrv->pxPinU_lowSide, MONO_PIN_HIGH);
                    break;

                case _6STEP_LOWSIDE_ON:
                    Pwm1_Generate(pxDrv->pxPwmU_highSide, 0.0f);
                    WriteGpio(pxDrv->pxPinU_lowSide, MONO_PIN_LOW);
                    break;
            }
            break;

        case POLE_V:  // Phase B
            switch(ctl){
                case _6STEP_HiZ:
                    Pwm1_Generate(pxDrv->pxPwmV_highSide, 0.0f);
                    WriteGpio(pxDrv->pxPinV_lowSide, MONO_PIN_HIGH);
                    break;

                case _6STEP_PWM_IN:
                    Pwm1_Generate(pxDrv->pxPwmV_highSide, duty);
                    WriteGpio(pxDrv->pxPinV_lowSide, MONO_PIN_HIGH);
                    break;

                case _6STEP_LOWSIDE_ON:
                    Pwm1_Generate(pxDrv->pxPwmV_highSide, 0.0f);
                    WriteGpio(pxDrv->pxPinV_lowSide, MONO_PIN_LOW);
                    break;
            }
            break;

        case POLE_W:  // Phase C
            switch(ctl){
                case _6STEP_HiZ:
                    Pwm1_Generate(pxDrv->pxPwmW_highSide, 0.0f);
                    WriteGpio(pxDrv->pxPinW_lowSide, MONO_PIN_HIGH);
                    break;

                case _6STEP_PWM_IN:
                    Pwm1_Generate(pxDrv->pxPwmW_highSide, duty);
                    WriteGpio(pxDrv->pxPinW_lowSide, MONO_PIN_HIGH);
                    break;

                case _6STEP_LOWSIDE_ON:
                    Pwm1_Generate(pxDrv->pxPwmW_highSide, 0.0f);
                    WriteGpio(pxDrv->pxPinW_lowSide, MONO_PIN_LOW);
                    break;
            }
            break;
    }



    

}


