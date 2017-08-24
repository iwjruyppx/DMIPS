#ifndef __GoldSample_H__
#define __GoldSample_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define INDEX_ACC 0
#define INDEX_MAG 1
#define INDEX_GYRO 2
#define INDEX_LIGHT 3
#define INDEX_PROXIMITY 4
#define INDEX_PRESSURE 5

typedef struct {
    int type;
	int64_t time;
    float data[3];
}GoldSample_t, *pGoldSample_t;

pGoldSample_t getGoldSample(void);
int getGoldSampleCount(void);
int getMAXGoldSampleCount(void);
int resetGoldSampleIntex(void);


#endif /* __GoldSample_H__ */
