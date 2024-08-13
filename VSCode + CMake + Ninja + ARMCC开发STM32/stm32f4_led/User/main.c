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
		HAL_Delay(10000);									   // 延时500ms
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);	   // LED0对应引脚PB1拉高，灭，等同于LED0(1)
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);  // LED1对应引脚PB0拉低，亮，等同于LED1(0)
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

	__HAL_RCC_PWR_CLK_ENABLE();	 // 使能PWR时钟

	// 下面这个设置用来设置调压器输出电压级别，以便在器件未以最大频率工作
	// 时使性能与功耗实现平衡，此功能只有STM32F42xx和STM32F43xx器件有，
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);	// 设置调压器输出电压级别1

	RCC_OscInitStructure.OscillatorType = RCC_OSCILLATORTYPE_HSE;	// 时钟源为HSE
	RCC_OscInitStructure.HSEState = RCC_HSE_ON;						// 打开HSE
	RCC_OscInitStructure.PLL.PLLState = RCC_PLL_ON;					// 打开PLL
	RCC_OscInitStructure.PLL.PLLSource = RCC_PLLSOURCE_HSE;			// PLL时钟源选择HSE
	RCC_OscInitStructure.PLL.PLLM = 25;	  // 主PLL和音频PLL分频系数(PLL之前的分频),取值范围:2~63.
	RCC_OscInitStructure.PLL.PLLN = 360;  // 主PLL倍频系数(PLL倍频),取值范围:64~432.
	RCC_OscInitStructure.PLL.PLLP = 2;	// 系统时钟的主PLL分频系数(PLL之后的分频),取值范围:2,4,6,8.(仅限这4个值!)
	RCC_OscInitStructure.PLL.PLLQ = 8;	// USB/SDIO/随机数产生器等的主PLL分频系数(PLL之后的分频),取值范围:2~15.
	ret = HAL_RCC_OscConfig(&RCC_OscInitStructure);	 // 初始化

	if (ret != HAL_OK)
		while (1)
			;

	ret = HAL_PWREx_EnableOverDrive();	// 开启Over-Driver功能
	if (ret != HAL_OK)
		while (1)
			;

	// 选中PLL作为系统时钟源并且配置HCLK,PCLK1和PCLK2
	RCC_ClkInitStructure.ClockType =
		(RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStructure.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;  // 设置系统时钟时钟源为PLL
	RCC_ClkInitStructure.AHBCLKDivider = RCC_SYSCLK_DIV1;		  // AHB分频系数为1
	RCC_ClkInitStructure.APB1CLKDivider = RCC_HCLK_DIV4;		  // APB1分频系数为4
	RCC_ClkInitStructure.APB2CLKDivider = RCC_HCLK_DIV2;		  // APB2分频系数为2
	ret = HAL_RCC_ClockConfig(&RCC_ClkInitStructure,
							  FLASH_LATENCY_5);	 // 同时设置FLASH延时周期为5WS，也就是6个CPU周期。

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
