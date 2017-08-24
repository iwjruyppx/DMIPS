/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "ALGO_LIST.h"
#include "CWM_AlgoApi.h"
#include "cwm_pick_up.h"
#include "CwmUtil.h"


static pCwmAlgoInfoType    pMem = NULL;
static pCwmAlgoStandardAPI    pApiMem = NULL;


#define ALGO_PICKUP "PickUp"


static void PickUpVersion(int *version)
{
    version_cwm_pick_up(version);
}

static void PickUpInit(pCwmAlgoStandardAPI pCallBack)
{
    pApiMem = pCallBack;

    init_cwm_pick_up();
}
    
static void PickUpSetConfig(void *config)
{
    char cPickupCfgParmData[] = {5, 5, 5, 5, 5};
    
    set_config_cwm_pick_up(cPickupCfgParmData, sizeof(cPickupCfgParmData));
    
}

static void PickUpSetEnable(void)
{
    pMem->Enabled = 1;
    pMem->Amount = 0;
    enable_cwm_pick_up();
    pApiMem->SensorEnableAPI(pMem->Handle, ACC);
    printf("%s\n",__FUNCTION__);
}

static void PickUpSetDisable(void)
{    
    pMem->Enabled = 0;
    pMem->Rate = 0;
    pMem->Latency = ULONG_LONG_MAX;
    pApiMem->SensorDisableAPI(pMem->Handle, ACC);
    disable_cwm_pick_up();
    printf("%s\n",__FUNCTION__);
}

static void PickUpSetRate(uint32_t rate, uint64_t latency)
{
    pMem->Rate = ACCEL_MIN_RATE;
    pMem->Latency = 0; 
    pApiMem->SensorSetRateAPI(pMem->Handle, ACC, pMem->Rate, pMem->Latency);    
}
    
static int PickUpMain(uint32_t SensorHandle, float *raw_data, float dt, uint64_t time)
{
    int rtn = 0;
    float algo_output[6] = { 0 };

    /*Sensor is disable*/
    if(pMem->Enabled == 0)
        return rtn;
    
    switch(SensorHandle)
    {
        case HW_ACC:
            rtn = cwm_pick_up(raw_data, algo_output, dt);
            pMem->Amount++;
            if(rtn>0)
            {
                pApiMem->AlgoUpdateAPI(pMem->Handle, algo_output, time);
            }
            break;
        default:
            break;
    }

    return rtn;
}

const CwmAlgoInfoCallback pickupInfoCallback = 
{
    .AlgoVersion            = PickUpVersion,
    .AlgoInit               = PickUpInit,
    .AlgoSetConfig          = PickUpSetConfig,  
    .AlgoEnable             = PickUpSetEnable,
    .AlgoSetRate            = PickUpSetRate,
    .AlgoDisable            = PickUpSetDisable,
    .AlgoMain               = PickUpMain
};

#ifdef USE_CWM_PICK_UP
void PickUpCBInit( pCwmAlgoInfoType pAlgoInfo )
{
    pAlgoInfo->Enabled = 0;
    pAlgoInfo->Handle = SENS_TYPE_GESTURE;
    pAlgoInfo->pAlgoCallback = &pickupInfoCallback;
    pMem = pAlgoInfo;
}
#endif

