/**
 ******************************************************************************
 * @file    Templates/Src/main.c
 * @author  MCD Application Team
 * @brief   Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2017 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "led.h"

/** @addtogroup STM32F4xx_HAL_Examples
 * @{
 */

/** @addtogroup Templates
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void)
{
	/* STM32F4xx HAL library initialization:
		 - Configure the Flash prefetch, Flash preread and Buffer caches
		 - Systick timer is configured by default as source of time base, but user
			   can eventually implement his proper time base source (a general purpose
			   timer for example or other time source), keeping in mind that Time base
			   duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
			   handled in milliseconds basis.
		 - Low Level Initialization
	   */
	HAL_Init();

	/* Configure the System clock to 180 MHz */
	SystemClock_Config();

	/* Add your application code here
	 */

	LED_Init();

	/* Infinite loop */
	while (1)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
		HAL_Delay(10000);									   // ��ʱ500ms
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);	   // LED0��Ӧ����PB1���ߣ��𣬵�ͬ��LED0(1)
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);  // LED1��Ӧ����PB0���ͣ�������ͬ��LED1(0)
		HAL_Delay(10000);
	}
}

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 180000000
 *            HCLK(Hz)                       = 180000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 4
 *            APB2 Prescaler                 = 2
 *            HSE Frequency(Hz)              = 8000000
 *            PLL_M                          = 8
 *            PLL_N                          = 360
 *            PLL_P                          = 2
 *            PLL_Q                          = 7
 *            VDD(V)                         = 3.3
 *            Main regulator output voltage  = Scale1 mode
 *            Flash Latency(WS)              = 5
 * @param  None
 * @retval None
 */
static void SystemClock_Config(void)
{
	HAL_StatusTypeDef ret = HAL_OK;
	RCC_OscInitTypeDef RCC_OscInitStructure;
	RCC_ClkInitTypeDef RCC_ClkInitStructure;

	__HAL_RCC_PWR_CLK_ENABLE();	 // ʹ��PWRʱ��

	// ������������������õ�ѹ�������ѹ�����Ա�������δ�����Ƶ�ʹ���
	// ʱʹ�����빦��ʵ��ƽ�⣬�˹���ֻ��STM32F42xx��STM32F43xx�����У�
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);	// ���õ�ѹ�������ѹ����1

	RCC_OscInitStructure.OscillatorType = RCC_OSCILLATORTYPE_HSE;	// ʱ��ԴΪHSE
	RCC_OscInitStructure.HSEState = RCC_HSE_ON;						// ��HSE
	RCC_OscInitStructure.PLL.PLLState = RCC_PLL_ON;					// ��PLL
	RCC_OscInitStructure.PLL.PLLSource = RCC_PLLSOURCE_HSE;			// PLLʱ��Դѡ��HSE
	RCC_OscInitStructure.PLL.PLLM = 25;	  // ��PLL����ƵPLL��Ƶϵ��(PLL֮ǰ�ķ�Ƶ),ȡֵ��Χ:2~63.
	RCC_OscInitStructure.PLL.PLLN = 360;  // ��PLL��Ƶϵ��(PLL��Ƶ),ȡֵ��Χ:64~432.
	RCC_OscInitStructure.PLL.PLLP = 2;	// ϵͳʱ�ӵ���PLL��Ƶϵ��(PLL֮��ķ�Ƶ),ȡֵ��Χ:2,4,6,8.(������4��ֵ!)
	RCC_OscInitStructure.PLL.PLLQ = 8;	// USB/SDIO/������������ȵ���PLL��Ƶϵ��(PLL֮��ķ�Ƶ),ȡֵ��Χ:2~15.
	ret = HAL_RCC_OscConfig(&RCC_OscInitStructure);	 // ��ʼ��

	if (ret != HAL_OK)
		while (1)
			;

	ret = HAL_PWREx_EnableOverDrive();	// ����Over-Driver����
	if (ret != HAL_OK)
		while (1)
			;

	// ѡ��PLL��Ϊϵͳʱ��Դ��������HCLK,PCLK1��PCLK2
	RCC_ClkInitStructure.ClockType =
		(RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStructure.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;  // ����ϵͳʱ��ʱ��ԴΪPLL
	RCC_ClkInitStructure.AHBCLKDivider = RCC_SYSCLK_DIV1;		  // AHB��Ƶϵ��Ϊ1
	RCC_ClkInitStructure.APB1CLKDivider = RCC_HCLK_DIV4;		  // APB1��Ƶϵ��Ϊ4
	RCC_ClkInitStructure.APB2CLKDivider = RCC_HCLK_DIV2;		  // APB2��Ƶϵ��Ϊ2
	ret = HAL_RCC_ClockConfig(&RCC_ClkInitStructure,
							  FLASH_LATENCY_5);	 // ͬʱ����FLASH��ʱ����Ϊ5WS��Ҳ����6��CPU���ڡ�

	if (ret != HAL_OK)
		while (1)
			;
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
static void Error_Handler(void)
{
	/* User may add here some code to deal with this error */
	while (1)
	{
	}
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	   ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif

/**
 * @}
 */

/**
 * @}
 */
