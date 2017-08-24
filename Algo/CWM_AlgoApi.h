#ifndef __CWM_AlgoApi_H__
#define __CWM_AlgoApi_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define SENSOR_HZ(x)   (x)
#define SENS_TYPE_GESTURE 1

#define ULONG_LONG_MAX   0xFFFFFFFFFFFFFFFF
#define ACCEL_MIN_RATE    SENSOR_HZ(100)
#define ACCEL_MAX_LATENCY 50000000ull   // 50 ms
#define GYRO_MIN_RATE    SENSOR_HZ(100)
#define GYRO_MAX_LATENCY 50000000ull   // 50 ms
#define MAG_MIN_RATE    SENSOR_HZ(50)
#define MAG_MAX_LATENCY 50000000ull   // 50 ms
#define PRESS_MIN_RATE    SENSOR_HZ(10)
#define PRESS_MAX_LATENCY (1000000000ULL / 10)

#define ALGO_MAX_DELTA_TIME     200000000ull   // 200 ms

#define NS2US(x) (x >> 10)   // convert nsec to approx usec

#define ACC_CONFIG_FLAG    65

#define TICKS_DIFF64(prev, cur) ((cur) >= (prev)) ? ((cur)-(prev)) : ((0xFFFFFFFFFFFFFFFF-(prev))+1+(cur))    /* Calculate time diff (64 byte)*/

typedef enum {
    HW_ACC = 0,
    HW_GYRO = 1,
    HW_MAG = 2,
    HW_LIGHT = 3,
    HW_PROXIMITY = 4,
    HW_PRESSURE = 5
} HW_SENSORS_ID;

enum RawSensorType
{
    ACC,
    GYR,
    MAG,
    PRESSURE,
    NUM_OF_RAW_SENSOR
};

typedef struct {
    void (*SensorEnableAPI)(uint32_t AlgoHandle, uint32_t SensorHandle);
    void (*SensorDisableAPI)(uint32_t AlgoHandle, uint32_t SensorHandle);
    void (*SensorSetRateAPI)(uint32_t AlgoHandle, uint32_t SensorHandle, uint32_t rate, uint64_t latency);
    void (*AlgoUpdateAPI)(uint32_t AlgoHandle, float *Output, uint64_t time);
    void (*AlgoUpdateThreeAPI)(uint32_t AlgoHandle, float *Output, uint64_t time);
} CwmAlgoStandardAPI, *pCwmAlgoStandardAPI;

typedef struct {
    void (*AlgoVersion)(int *version);
    void (*AlgoInit)(pCwmAlgoStandardAPI pCallBack);
    void (*AlgoSetConfig)(void *config);
    void (*AlgoEnable)(void);
    void (*AlgoSetRate)(uint32_t rate, uint64_t latency);
    void (*AlgoDisable)(void);
    int (*AlgoMain)(uint32_t SensorHandle, float *raw_data, float dt, uint64_t time);
    uint32_t NumOfHwSensorUse;
} CwmAlgoInfoCallback, *pCwmAlgoInfoCallback;


typedef struct {
    uint8_t Enabled;
    uint32_t Handle;
    uint32_t Rate;
    uint64_t Latency;
    uint64_t Amount;
    const CwmAlgoInfoCallback *pAlgoCallback;
} CwmAlgoInfoType, *pCwmAlgoInfoType;

typedef void(*FUNC_ALGOINFO_PTR)(pCwmAlgoInfoType);


#endif /* __CWM_AlgoApi_H__ */
