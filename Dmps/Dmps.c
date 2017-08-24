#include "Dmps.h"

float DmpsCalculate(pDmps_t data){
    int64_t avarge_process_time;
    float avarge_process_time_ms;
    
    avarge_process_time =   (data->StopTime-data->StartTime)/(data->processAmount);
    avarge_process_time_ms = (float)avarge_process_time/1000000.0f;

    data->Dmps =  (data->chipDmps * avarge_process_time_ms)/1000.0f;

    return 0;
}