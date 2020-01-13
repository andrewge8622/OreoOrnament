/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "animations.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#ifndef NUMBER_LEDS
#define NUMBER_LEDS 10
#endif

#ifndef MAX_global_brightness
#define MAX_global_brightness 31
#endif

#ifndef MIN_global_brightness
#define MIN_global_brightness 10
#endif
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
uint8_t global_brightness = 0x0;
uint8_t mode = 0;
uint8_t empty_spi_buf[] = {0, 0, 0, 0};
uint8_t full_spi_buf[] = {0xFF, 0xFF, 0xFF, 0xFF};
uint8_t counter = 0;
uint8_t change_flag = 0;
uint8_t next_frame[NUMBER_LEDS][4];
int delay = 1000;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);

/* USER CODE BEGIN PFP */
void APA102_START_FRAME(void);
void APA102_END_FRAME(void);
void APA102_SET_SINGLE_COLOR(uint8_t, uint32_t);
void APA102_SET_ARRAY(uint8_t[][4]);
void GENERATE_FRAME(uint8_t, uint8_t, uint8_t[][4]);
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
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
	APA102_SET_SINGLE_COLOR(31, 0x0);
	HAL_Delay(500);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
		/*
		HAL_Delay(delay);
		// HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
		APA102_SET_SINGLE_COLOR(5, 0x010000);
		HAL_Delay(delay);
		APA102_SET_SINGLE_COLOR(5, 0x0100);
		HAL_Delay(delay);
		APA102_SET_SINGLE_COLOR(5, 0x01);
		*/
		
		//if (!(counter%5)) {
			GENERATE_FRAME(change_flag, global_brightness, next_frame);
			APA102_SET_ARRAY(next_frame);
			change_flag = 0;
		//}
		HAL_Delay(100); // timing will likely have to be adjusted later
		counter++;
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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	/* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);

}

/* USER CODE BEGIN 4 */
void APA102_START_FRAME(void) {
	HAL_SPI_Transmit(&hspi1, empty_spi_buf, 1, 50);
	HAL_SPI_Transmit(&hspi1, empty_spi_buf, 1, 50);
	HAL_SPI_Transmit(&hspi1, empty_spi_buf, 1, 50);
	HAL_SPI_Transmit(&hspi1, empty_spi_buf, 1, 50);
}

void APA102_END_FRAME(void) {
	HAL_SPI_Transmit(&hspi1, full_spi_buf, 1, 50);
	HAL_SPI_Transmit(&hspi1, full_spi_buf, 1, 50);
	HAL_SPI_Transmit(&hspi1, full_spi_buf, 1, 50);
	HAL_SPI_Transmit(&hspi1, full_spi_buf, 1, 50);
}

void APA102_SET_SINGLE_COLOR(uint8_t brightness, uint32_t color) {
	uint8_t frame_bright = (brightness & 0x1F) | 0xE0; // set first 3 bits to 1
	uint8_t b = (color >> 16) & 0xFF;
	uint8_t g = (color >> 8) & 0xFF;
	uint8_t r = color & 0xFF;
	
	APA102_START_FRAME();
	
	for (int i = 0; i < NUMBER_LEDS; i++) {
		HAL_SPI_Transmit(&hspi1, &frame_bright, 1, 50);
		HAL_SPI_Transmit(&hspi1, &b, 1, 50);
		HAL_SPI_Transmit(&hspi1, &g, 1, 50);
		HAL_SPI_Transmit(&hspi1, &r, 1, 50);
	}
	
	APA102_END_FRAME();
}

void APA102_SET_ARRAY(uint8_t frame[][4]) {
	APA102_START_FRAME();
	
	for (int i = 0; i < NUMBER_LEDS; i++) {
		HAL_SPI_Transmit(&hspi1, frame[i], 1, 50);
		HAL_SPI_Transmit(&hspi1, frame[i]+1, 1, 50);
		HAL_SPI_Transmit(&hspi1, frame[i]+2, 1, 50);
		HAL_SPI_Transmit(&hspi1, frame[i]+3, 1, 50);
	}
	
	APA102_END_FRAME();
}

void GENERATE_FRAME(uint8_t change, uint8_t brightness, uint8_t next_frame[][4]) {
	// TURN OFF INTERRUPTS
	switch (mode) {
		case 1: // red breathing
			advance_mode_1(change, brightness, next_frame);
			break;
		case 2: // gold breathing
			advance_mode_2(change, brightness, next_frame);
			break;
		case 3: // red and gold breathing
			advance_mode_3(change, brightness, next_frame);
			break;
		case 4: // RGB alternating
			advance_mode_4(change, brightness, next_frame);
			break;
		case 5: // HSV traversal
			advance_mode_5(change, brightness, next_frame);
			break;
		default: // static red and gold
			advance_mode_0(change, brightness, next_frame);
			;
	}
	// TURN ON INTERRUPTS
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(GPIO_Pin);
  if (GPIO_Pin == GPIO_PIN_0) {
		mode = (mode + 1) % 6;
		change_flag = 1;
	}
	else if (GPIO_Pin == GPIO_PIN_1) {
		global_brightness = (global_brightness >= 12) ? 0 : global_brightness + 3;
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
