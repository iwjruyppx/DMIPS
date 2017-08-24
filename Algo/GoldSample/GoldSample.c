#include "GoldSample.h"
#include "GoldSampleData.h"

static int current_count = 0;

pGoldSample_t getGoldSample(void){
    pGoldSample_t pdata = NULL;
    if(current_count >= NUMBER_OF_DATA){
        return pdata;
    }

    pdata = (pGoldSample_t)&GoldSample_DATA[current_count];
    current_count ++;
    return pdata;
}
int getGoldSampleCount(void){
  
    return current_count;
}
int getMAXGoldSampleCount(void){
  
    return NUMBER_OF_DATA;
}
int resetGoldSampleIntex(void){
    current_count = 0;
    return 0;
}
