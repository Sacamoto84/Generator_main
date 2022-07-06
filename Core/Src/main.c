/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "crc.h"
#include "dac.h"
#include "dma.h"
#include "fatfs.h"
#include "i2c.h"
#include "sdio.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "SEGGER.h"
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"
//#include "SEGGER_SYSVIEW.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern void main_cpp(void);
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint16_t res;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	__disable_irq(); //????????? ??????????
	//SCB->VTOR = 0x8060000;
	SCB->VTOR = 0x80C0000;

	uint32_t *p;
	p = (uint32_t *)(0x10000000);
	int count = 16384;
	while(count--)
		*p++ = 0;

	__enable_irq(); //????????? ??????????
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
	MX_DMA_Init();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CRC_Init();
  MX_DAC_Init();
  MX_I2C1_Init();
  MX_SDIO_SD_Init();
  MX_SPI1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM6_Init();
  //MX_USART3_UART_Init();
  MX_TIM3_Init();
  MX_FATFS_Init();
  MX_TIM5_Init();
  /* USER CODE BEGIN 2 */
  MX_TIM7_Init();
  BSP_SD_Init();

	//Encoder
	TIM2->SR &= ~TIM_SR_UIF; // clear UIF flag
	HAL_TIM_Base_Start(&htim2);
	HAL_TIM_Base_Start_IT(&htim2);
	TIM2->DIER |= TIM_DIER_UIE;
	//HAL_TIM_Base_Start(&htim2);
	//HAL_TIM_Base_Start_IT(&htim2);

	TIM1->CCR1 = 75;
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

	SEGGER_RTT_Init();
	//SEGGER_SYSVIEW_Conf();
	//SEGGER_SYSVIEW_Start();
	//SEGGER_SYSVIEW_Print("Start");

	res = f_mount(&SDFatFS, SDPath, 1);       //Mount MicroSd

	SEGGER_RTT_WriteString(0, "\r\n\033[01;03;38;05;226;48;05;24m");
	SEGGER_RTT_WriteString(0, "Start\x1B[0m\r\n");

	SEGGER_RTT_WriteString(0, "\r\n\033[01;38;05;226;48;05;24m");
	SEGGER_RTT_WriteString(0, "Start\x1B[0m\r\n");

	SEGGER_RTT_WriteString(0, "\r\n\033[03;38;05;226;48;05;24m");
	SEGGER_RTT_WriteString(0, "Start\x1B[0m\r\n");

	SEGGER_RTT_WriteString(0, "\r\n\033[04;38;05;226;48;05;24m");
	SEGGER_RTT_WriteString(0, "Start\x1B[0m\r\n");

	SEGGER_RTT_WriteString(0, "\r\n\033[03;38;05;226;48;05;24m");
	SEGGER_RTT_WriteString(0, "Start\x1B[0m\r\n");

	SEGGER_RTT_WriteString(0, "\r\n\033[03;07;38;05;226;48;05;24m");
	SEGGER_RTT_WriteString(0, "Start\x1B[0m\r\n");

	SEGGER_RTT_WriteString(0, "\r\n\033[03;07;08;38;05;226;48;05;24m");
	SEGGER_RTT_WriteString(0, "Start\x1B[0m\r\n");


	if (f_open(&SDFile, "b1.bmp", FA_OPEN_EXISTING | FA_READ)
			== FR_OK) {
		SEGGER_RTT_WriteString(0, "Тест f_open == OK\r\n");
		f_close(&SDFile);

	} else {
		SEGGER_RTT_WriteString(0, "Тест f_open == ERROR\r\n");
	}

	//ESP_ON;
	main_cpp();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
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
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
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
	while (1) {
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
