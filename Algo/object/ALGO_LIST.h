
#include "CWM_AlgoApi.h"

#define USE_CWM_PICK_UP

#ifndef __ALGO_LIST_H__
#define __ALGO_LIST_H__

/* Gesture 1 */
#ifdef USE_CWM_PICK_UP
void PickUpCBInit( pCwmAlgoInfoType pAlgoInfo );
#endif

static const FUNC_ALGOINFO_PTR AlgoSupportList[] = 
{
#ifdef USE_CWM_PICK_UP
     PickUpCBInit,
#endif
};

#define NUMBER_OF_ALGO \
    (sizeof(AlgoSupportList)/sizeof(AlgoSupportList[0]))

  
#endif
