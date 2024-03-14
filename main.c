/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gpio.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "LCD.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define RCC_CR_SET                  (RCC_BASE + 0x00)
#define RCC_PLLCFGR_SET             (RCC_BASE + 0X04)
#define RCC_CFGR_SET                (RCC_BASE + 0x08)

#define RCC_AHB1LPENR_SET           (RCC_BASE + 0x50)
#define RCC_AHB1ENR_SET             (RCC_BASE + 0x30)   //peripheral clock enable, gpio
#define RCC_APB1ENR_SET             (RCC_BASE + 0x40)   //peripheral clock enable, pwr or communication
#define RCC_APB1LPENR_SET           (RCC_BASE + 0x60)

#define RCC_APB2LPENR_SET           (RCC_BASE + 0x64)
#define RCC_APB2ENR_SET             (RCC_BASE + 0x44)

#define RCC_AHB3ENR_SET             (RCC_BASE + 0x38)

#define RCC_CSR_SET                 (RCC_BASE + 0x74)
#define RCC_PLLI2SCFGR_SET          (RCC_BASE + 0x84)
#define RCC_PLLSAICFGR_SET          (RCC_BASE + 0x88)
#define FLASH_ACR_SET               0x40023c00

//#define RCC_PLLCFGR     (RCC_OFFSET + 0x04UL)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
static char ALWOX[]  = "RCC FLASH ADDED";
static char MYNAME[] = "SET WITHOUT MX";
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void SystemClock_Init()
{

  *((uint32_t *) RCC_CR_SET) |= 0x03037b83;
  *((uint32_t *) RCC_PLLCFGR_SET) |= 0x22412d04;        // SET PLLR, PLLQ,  PLLSRT, PLLP, PLLN, PLLM
  *((uint32_t *) RCC_CFGR_SET) |= 0x0000140f;           // SET AHB clock divided by 4. PLL_R USED, SELECTED 
  *((uint32_t *) RCC_CSR_SET) |= 0x1e000000;            // SET SOFTWARE RESET, (PORT, PIN, BOR) RESET FLAG
  
  *((uint32_t *) RCC_PLLI2SCFGR_SET) |= 0x24002D10;    // SET PRESCALE VALUE and Output 180Hz frequency
  *((uint32_t *) RCC_PLLSAICFGR_SET) |= 0x04002D10;     //SET PRESCALE VALUE and Output 180Hz frequency
  //AxB1-------------------------------------------------------------------------------
  *((uint32_t *) RCC_AHB1ENR_SET) |=0x00000017;         // SET GPIO A,B,C,H H>>OSCILATOR ENABLE
  *((uint32_t *) RCC_AHB1LPENR_SET) |= 0x60079007;      // SET GPIO FLASH interface clock, GPIO A~C; DURING Sleep mode; 
  
  *((uint32_t *) RCC_APB1ENR_SET) |= 0x10000000;        // SET pwr clock enable
  *((uint32_t *) RCC_APB1LPENR_SET) |= 0x18000000;      // set PWR, CECLP ENABLE
  //AxB2-------------------------------------------------------------------------------
  *((uint32_t *) RCC_APB2ENR_SET) |= 0x00004000;        // SET system clock configuration enable
  *((uint32_t *) RCC_APB2LPENR_SET) |= 0x00004000;      // set systemconfig controller clock enable during sleep mode
 
  //AxB3-------------------------------------------------------------------------------
  *((uint32_t *) RCC_AHB3ENR_SET) |= 0x00000003;        // SET memory controller module clock, Flexible memory controller module clock enable
  
  //Flash set
  *((uint32_t *) FLASH_ACR_SET) |= 0x00000705;          //set 5 Latency, cache reset, data cach reset func==0
  
} 

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  //SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  SystemClock_Init();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  LcdInit();
  //SET D0~D7 MODER
  GPIOA->MODER |= ( 1 << 0 );	// SET PA0 OUTPUT MODE
  GPIOA->MODER |= ( 1 << 2 );	// SET PA1 OUTPUT MODE
  GPIOA->MODER |= ( 1 << 8 );	// SET PA4 OUTPUT MODE
  GPIOA->MODER |= ( 1 << 12 );  // SET PA6 OUTPUT MODE
  GPIOA->MODER |= ( 1 << 14 );	// SET PA7 OUTPUT MODE
  GPIOA->MODER |= ( 1 << 16 );	// SET PA8 OUTPUT MODE
  GPIOA->MODER |= ( 1 << 18 );	// SET PA9 OUTPUT MODE
  GPIOA->MODER |= ( 1 << 20 );	// SET PA10 OUTPUT MODE

  //SET RW,RS,E MODER
  GPIOB->MODER |= ( 1 << 8 );	//SET PB4 OUTPUT MODE
  GPIOB->MODER |= ( 1 << 10 );	//SET PB5 OUTPUT MODE
  GPIOB->MODER |= ( 1 << 12 );	//SET PB6 OUTPUT MODE
  
  //SET BUTTON PIN MODER
  //LCD_BUTTON_PORT -> MODER |= ( 1 << 26 );	//SET PC13 OUTPUT MODE
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      //CURSOR
      LcdMove(0,0);
      //PRINT STRING
      LcdPuts(ALWOX);
      //CURSOR
      LcdMove(1,0);
      //PRINT STRING
      LcdPuts(MYNAME);
      /*for (int i=0; i<10; i++ )
      {
          HAL_Delay(1000);
          LcdCommand(DISP_RSHIFT);
      }  
      for (int i=0; i<10; i++ )
      {
          HAL_Delay(1000);
          LcdCommand(DISP_LSHIFT);
      }*/  

 
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLRCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
