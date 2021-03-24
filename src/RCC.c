/*
 * RCC.c
 *
 *  Created on: 20/03/2021
 *      Author: juanp
 */

#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"

/*
 * Enable clocks
 */
void setup_RCC(void){

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_TIM3_CLK_ENABLE();
	__HAL_RCC_TIM4_CLK_ENABLE();
}
