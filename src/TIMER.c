/*
 * TIMER.c

 *
 *  Created on: 24/03/2021
 *      Author: juanp
 */

#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"
#include "USART.h"
#include "Ball.h"

TIM_HandleTypeDef htimer3;
uint8_t first_move = 0;

void TIMER3_Init(void){

	//High level initialization of the TIMER 3 for 10ms if using HSI
	htimer3.Instance = TIM3;
	htimer3.Init.Period = 53000;
	htimer3.Init.Prescaler = 300;

	HAL_TIM_Base_Init(&htimer3);
	HAL_TIM_Base_Start_IT(&htimer3);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htimer){

	//1. Enable the clock for timer 3
	__HAL_RCC_TIM3_CLK_ENABLE();

	//2. Enable the IRQ of TIM3
	HAL_NVIC_EnableIRQ(TIM3_IRQn);

	//3. NVIC settings
	HAL_NVIC_SetPriority(TIM3_IRQn, 15, 0);
}

void TIM3_IRQHandler(){

	HAL_TIM_IRQHandler(&htimer3);
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

	move_ball(first_move);
	first_move++;
	//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}
