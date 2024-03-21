/*
 * SystemConfig.h
 *
 *  Created on: 2024. 3. 20.
 *      Author: 강태의
 */

#ifndef CORE_INC_SYSTEMCONFIG_H_
#define CORE_INC_SYSTEMCONFIG_H_

#include "stm32f4xx_hal.h"

//need value
#define PWR_CR_VOS_3           0x0000D000U		//use scale 1, because frequency is 180MHz
#define RCC_PLLCFGR_PLLN_15		(0xB4 << RCC_PLLCFGR_PLLM_Pos)		//180MHz, 1011 0100 << 6
#define RCC_CFGR_SWS_R                     (0x3UL << RCC_CFGR_SWS_Pos)          /*!< 0x0000000C */
#define RCC_CFGR_SW_R                      (0x3UL << RCC_CFGR_SW_Pos)           /*!< 0x00000003 */

void SystemClock_Init();

#endif /* CORE_INC_SYSTEMCONFIG_H_ */
