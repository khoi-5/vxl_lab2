/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
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
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "software_timer.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

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

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
GPIO_TypeDef *SEG_PORTS[12] = { SEG0_GPIO_Port, SEG1_GPIO_Port,
SEG2_GPIO_Port, SEG3_GPIO_Port, SEG4_GPIO_Port, SEG5_GPIO_Port,
SEG6_GPIO_Port };
uint16_t SEG_PINS[12] = { SEG0_Pin, SEG1_Pin, SEG2_Pin, SEG3_Pin,
SEG4_Pin, SEG5_Pin, SEG6_Pin };
GPIO_PinState LEDS_state[10][7] = {
		// a, b, c, d, e, f, g
		{0, 0, 0, 0, 0, 0, 1}, // 0
		{1, 0, 0, 1, 1, 1, 1}, // 1
		{0, 0, 1, 0, 0, 1, 0}, // 2
		{0, 0, 0, 0, 1, 1, 0}, // 3
		{1, 0, 0, 1, 1, 0, 0}, // 4
		{0, 1, 0, 0, 1, 0, 0}, // 5
		{0, 1, 0, 0, 0, 0, 0}, // 6
		{0, 0, 0, 1, 1, 1, 1}, // 7
		{0, 0, 0, 0, 0, 0, 0}, // 8
		{0, 0, 0, 0, 1, 0, 0}  // 9
};
void set_LEDS(GPIO_PinState *L_LEDS_state) {
	for (int i = 0; i < 7; i++) {
		HAL_GPIO_WritePin(SEG_PORTS[i], SEG_PINS[i], L_LEDS_state[i]);
	}
}
void display7SEG(int num) {
	if (num >= 0 && num <= 9) {
	        set_LEDS(LEDS_state[num]);
	    }
}
void set_state(GPIO_PinState EN0_state, GPIO_PinState EN1_state,
		GPIO_PinState EN2_state, GPIO_PinState EN3_state) {
	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, EN0_state);
	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, EN1_state);
	HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, EN2_state);
	HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, EN3_state);
}

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

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  	setTimer(0, 500);
  	HAL_GPIO_WritePin(DOT_GPIO_Port, DOT_Pin, 0);
  	int counter = 0;

  while (1){
	  if (timer_flag[0] == 1) {
		switch (counter) {
		case 0:
			set_state(0, 1, 1, 1);
			display7SEG(1);
			break;
		case 1:
			set_state(1, 0, 1, 1);
			display7SEG(2);
			HAL_GPIO_WritePin(DOT_GPIO_Port, DOT_Pin, 1);
			break;
		case 2:
			set_state(1, 1, 0, 1);
			display7SEG(3);
			break;
		case 3:
			set_state(1, 1, 1, 0);
			display7SEG(0);
			HAL_GPIO_WritePin(DOT_GPIO_Port, DOT_Pin, 0);
			counter = -1;
			break;
		}
		counter++;
		setTimer(0, 500);
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	timerRun();
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
