/*
 * SystemConfig.c
 *
 *  Created on: 2024. 3. 20.
 *      Author: 강태의
 */

#include "SystemConfig.h"
/*previos code
 * void SystemClock_Init()
{

  *((uint32_t *) RCC_CR_SET) = 0x03037b83;      
  *((uint32_t *) RCC_PLLCFGR_SET) = 0x22412d04;        // SET PLLR, PLLQ,  PLLSRT, PLLP, PLLN, PLLM
  *((uint32_t *) RCC_CFGR_SET) = 0x0000140f;           // SET AHB clock divided by 4. PLL_R USED, SELECTED
  *((uint32_t *) RCC_CSR_SET) = 0x1e000000;            // SET SOFTWARE RESET, (PORT, PIN, BOR) RESET FLAG

  *((uint32_t *) RCC_PLLI2SCFGR_SET) = 0x24002D10;    // SET PRESCALE VALUE and Output 180Hz frequency
  *((uint32_t *) RCC_PLLSAICFGR_SET) = 0x04002D10;     //SET PRESCALE VALUE and Output 180Hz frequency
  //AxB1-------------------------------------------------------------------------------
  *((uint32_t *) RCC_AHB1ENR_SET) = 0x00000017;         // SET GPIO A,B,C,H H>>OSCILATOR ENABLE
  *((uint32_t *) RCC_AHB1LPENR_SET) = 0x60079007;      // SET GPIO FLASH interface clock, GPIO A~C; DURING Sleep mode;

  *((uint32_t *) RCC_APB1ENR_SET) = 0x10000000;        // SET pwr clock enable
  *((uint32_t *) RCC_APB1LPENR_SET) = 0x18000000;      // set PWR, CECLP ENABLE
  //AxB2-------------------------------------------------------------------------------
  *((uint32_t *) RCC_APB2ENR_SET) = 0x00004000;        // SET system clock configuration enable
  *((uint32_t *) RCC_APB2LPENR_SET) = 0x00004000;      // set systemconfig controller clock enable during sleep mode

  //AxB3-------------------------------------------------------------------------------
  *((uint32_t *) RCC_AHB3ENR_SET) = 0x00000003;        // SET memory controller module clock, Flexible memory controller module clock enable

  //Flash set
  *((uint32_t *) FLASH_ACR_SET) = 0x00000705;          //set 5 Latency, cache reset, data cach reset func==0

}
 *
 */


//change
void SystemClock_Init()
{
	//HSE ON
	RCC->CR |= RCC_CR_HSEON;
	//WAIT
        while (! (RCC->CR |= RCC_CR_HSERDY));

        //PLL ON
	RCC->CR |= RCC_CR_PLLON;
        //WAIT 
	while (!(RCC->CR |= RCC_CR_PLLRDY));
        
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_4;
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_7;
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLR_1;

	//180MHz Setting and clock enable
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;	//power enable
	PWR->CR |= PWR_CR_VOS_3 ;		//regulator
	PWR->CR |= PWR_CR_ODEN_Msk;		//LOW VOLATAGE MODE == OVERDRIVE ON
	FLASH->ACR |= FLASH_ACR_LATENCY_5WS;


	//PLLR SELECT
	RCC->CFGR |= RCC_CFGR_SWS_R;
	RCC->CFGR |= RCC_CFGR_SW_R;
	//SYSCLK/1
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	//APB1 SCALER 4
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;

	//GPIO ENABLE
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
}
