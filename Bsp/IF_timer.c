#include "IF_timer.h"
#include "portStm32_Timer.h"





u8 InitTimer(TimerContainer_t* pxTmContainer, void* vxHwTimer){

    pxTmContainer->vxHwTimer = vxHwTimer;

    return 0;
}




TimerTask_t CreateTimerTask(tmCallback vxCb, void* args, u32 period, u8 StartCondition){

    TimerTask_t xTmTask;

    xTmTask.fpTmTask = vxCb;
    xTmTask.args = args;

    xTmTask.ucTimerStatus = StartCondition;
    xTmTask.uiPeriod = period;

    return xTmTask;
}



u8 RegisterTimer(TimerContainer_t* pxTmContainer, TimerTask_t* pxTimer){

    u8 rtn = 0; 

    if(pxTimer == NULL || pxTimer->fpTmTask == NULL){
        return 1;
    }

    if(pxTmContainer->vxHwTimer == NULL){
        return 2;
    }

    if(pxTmContainer->ucRegisterCount >= MAX_TIMER_TASK){
        return 3;
    }


    pxTmContainer->apxTasks[pxTmContainer->ucRegisterCount++] = pxTimer;

    return rtn;
}


void TimerContainerCtl(TimerContainer_t* pxTmContainer, u8 OnOff){
    
    if(OnOff != 0){
        StartHWTimer(pxTmContainer);
    }
    else {
        StopHWTimer(pxTmContainer);
    }
}



void HWTimerCallback(TimerContainer_t* genericTimer){



    for(u8 idx=0; idx<genericTimer->ucRegisterCount; ++idx){

        TimerTask_t* pxTmTask = genericTimer->apxTasks[idx];

        if(pxTmTask->ucTimerStatus == HARD_TIMER_STARTED){
            
            pxTmTask->uiCount++;

            if(pxTmTask->uiCount >= pxTmTask->uiPeriod){
                pxTmTask->uiCount = 0;
                pxTmTask->fpTmTask(pxTmTask->args);
            }
        }
        else {
            pxTmTask->uiCount = 0;
        }
        
    }
}
