#include "main.h"
#include "GoldSample.h"
#include "AlgorithmHal.h"
#include "CwmUtil.h"
#include "stm32xxx_it.h"

int main_loop = 1;

static void platform_init(void){
    SysTick_Config(SystemCoreClock/1000);
}

int main( void ){
    platform_init();
    AlgoHalInit();
    AlgoProcess();
    
    while(main_loop){
    }
    return 0;
}
/*-----------------------------------------------------------*/



/*
    while(GetCurrentTimeNs() <= 1000000000ll );
    

        pdata = getGoldSample();
        if(pdata != NULL ){
            //   printf("I:%d,T:%lld,%f,%f,%f \n", pdata->type, pdata->time, pdata->data[0], pdata->data[1], pdata->data[2]);
        }
        */