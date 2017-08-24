#ifndef __DMPS_H__
#define __DMPS_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

typedef struct {
    int64_t StartTime;    //nanosec
    int64_t StopTime;     //nanosec
    int64_t processAmount;
    float chipDmps;
    float Dmps;    //result
}Dmps_t, *pDmps_t;

float DmpsCalculate(pDmps_t data);

#endif /* __DMPS_H__ */
