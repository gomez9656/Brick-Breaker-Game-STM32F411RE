/*
 * USART.c
 *
 *  Created on: 23/03/2021
 *      Author: juanp
 */

#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"
#include "USART.h"
#include "GPIO.h"
#include <string.h>

UART_HandleTypeDef huart2; //Handle of UART 2
uint8_t some_data[] = " Testing game\r\n";



void USART2_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart2);
}

void setup_USART(){

	USART2_Init();
	HAL_UART_Transmit(&huart2, (uint8_t*)some_data, (uint16_t)strlen((char*)some_data), HAL_MAX_DELAY);
}

void USART2_Init(void){

	//1. Linking handle struct to base address
	huart2.Instance = USART2;

	//2. Init the handle variable
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;

	//3. Use the API to initialize
	HAL_UART_Init(&huart2);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart){

	GPIO_InitTypeDef gpio_uart;

	//1. Enable the clock for USART2 and GPIOA peripheral
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	//2. Pin muxing configuration
	gpio_uart.Pin = GPIO_PIN_2;
	gpio_uart.Mode = GPIO_MODE_AF_PP;
	gpio_uart.Pull = GPIO_PULLUP;
	gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
	gpio_uart.Alternate = GPIO_AF7_USART2; //USART2_TX

	HAL_GPIO_Init(GPIOA, &gpio_uart); //Initialize GPIOA2 with gpio_uart configuration

	gpio_uart.Pin = GPIO_PIN_3;	//USART2_RX
	HAL_GPIO_Init(GPIOA, &gpio_uart); //Initialize GPIOA3 with gpio_uart configuration

	//3. Enable the IRQ in the NVIC and set up priority
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn, 15, 0);
}


