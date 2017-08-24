/**
  ******************************************************************************
  * @file    stm32xxx.h 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32XXX_H
#define __STM32XXX_H

/* Includes ------------------------------------------------------------------*/


#ifdef STM32F4XX
#include "stm32f4xx.h"
#elif STM32F401X
#include "stm32f4xx.h"
#elif defined (STM32F2XX)
#include "stm32f2xx.h"
#elif defined (STM32F0XX)
#include "stm32f0xx.h"
#elif defined (STM32L1XX)
#include "stm32l1xx.h"
#elif defined (STM32F37X)
#include "stm32f37x.h"
#elif defined (STM32F30X)
#include "stm32f30x.h"
#else
#include "stm32f10x.h"
#endif

#endif /* __STM32XXX_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
