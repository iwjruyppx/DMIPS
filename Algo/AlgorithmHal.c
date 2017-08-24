#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "ALGO_LIST.h"
#include "AlgorithmHal.h"
#include "GoldSample.h"
#include "Dmps.h"
#include "stm32xxx_it.h"
#include "CwmUtil.h"

#define MAX_TEST_LOOP 10

CwmAlgoInfoType AlgoMem[NUMBER_OF_ALGO];
static int64_t lastTime[10] = {0};
Dmps_t dmps;

#define ALGO_VERSION(x,y)  AlgoMem[x].pAlgoCallback->AlgoVersion(y);
#define ALGO_ENABLE(x)  AlgoMem[x].pAlgoCallback->AlgoEnable();
#define ALGO_DISABLE(x)  AlgoMem[x].pAlgoCallback->AlgoDisable();
#define ALGO_MAIN(x,y,z,w,u)  AlgoMem[x].pAlgoCallback->AlgoMain(y,z,w,u);
#define ALGO_CalculateAmount(x)  AlgoMem[x].Amount;


static void sensorEnableAPI(uint32_t AlgoHandle, uint32_t SensorHandle)
{
}

static void sensorDisableAPI(uint32_t AlgoHandle, uint32_t SensorHandle)
{
}

static void sensorSetRateAPI(uint32_t AlgoHandle, uint32_t SensorHandle, uint32_t rate, uint64_t latency)
{
}

static void algoUpdateAPI(uint32_t algoHandle, float *output_data, uint64_t time)
{
}

static void algoUpdateThreeAPI(uint32_t algoHandle, float *output_data, uint64_t time)
{
}

const static CwmAlgoStandardAPI AlgoStandardAPI = {sensorEnableAPI,sensorDisableAPI,sensorSetRateAPI,algoUpdateAPI,algoUpdateThreeAPI};

float getDtFloat(int index, int64_t time){
    int64_t temp;
    temp = lastTime[index] - time;
    lastTime[index] = time;
    
    if(llabs(temp) > 50000000){ //50ms
        temp = 10000000;  //10ms
    }
    return ((float)temp)/1000;
}

void AlgoHalInit(void){
    int i;
    int setConfig[6] = { 0 };
    for( i = 0; i < NUMBER_OF_ALGO; i++){
        AlgoSupportList[i](&AlgoMem[i]);
        AlgoMem[i].pAlgoCallback->AlgoInit((pCwmAlgoStandardAPI)&AlgoStandardAPI);    
        AlgoMem[i].pAlgoCallback->AlgoSetConfig(setConfig);        
    }
}

void AlgoTest(int index){
    int version[10] = {0};
    pGoldSample_t pdata = NULL;
    float dt;
    int test_loop = 0;
    
    ALGO_VERSION(index, version);
    printf("Version:%d,%d,%d,%d,%d,%d\n",version[0],version[1],version[2],version[3],version[4],version[5]);
    
    ALGO_ENABLE(index);
    dmps.StartTime= GetCurrentTimeNs();
    
    while(1){
        pdata = getGoldSample();
        if(pdata == NULL ){
            if(MAX_TEST_LOOP > test_loop){
                test_loop ++;
                resetGoldSampleIntex();
                pdata = getGoldSample();
            }else{            
                break;
            }
        }
        dt = getDtFloat(pdata->type, pdata->time);
        ALGO_MAIN(index, pdata->type, pdata->data, dt, pdata->time);
    }

    dmps.StopTime= GetCurrentTimeNs();
    dmps.processAmount = ALGO_CalculateAmount(index);
    dmps.chipDmps = 1.25*16;    // 1.25 DMPS/MHz   Current run in 16MHz
    ALGO_DISABLE(index);
    
    DmpsCalculate(&dmps);
    printf("DMPS:%f, ProcessTimes:%lld, ProcessTime:%lld, \n", dmps.Dmps, dmps.processAmount, (dmps.StopTime-dmps.StartTime));    
}

void AlgoProcess(void)
{
    int i;
    for( i = 0; i < NUMBER_OF_ALGO; i++){
        AlgoTest(i);
    }
}


