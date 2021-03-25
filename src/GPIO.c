/*
 * GPIO.c
 *
 *  Created on: 23/03/2021
 *      Author: juanp
 */

#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"
#include "GPIO.h"
#include "Paddle.h"

GPIO_InitTypeDef led, left_button, right_button, rows, columns;
uint8_t *paddle_position = (uint8_t*)0x20000300;

void setup_GPIO(){

	*paddle_position = 3;

	setup_led();
	setup_left_button();
	setup_right_button();
	setup_rows();
	setup_columns();
}

void setup_led(){

	GPIO_InitTypeDef led;
	led.Pin = GPIO_PIN_5;
	led.Mode = GPIO_MODE_OUTPUT_PP;
	led.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &led);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
}

void setup_left_button(){

	left_button.Pin = GPIO_PIN_0;
	left_button.Mode = GPIO_MODE_IT_FALLING;
	left_button.Pull = GPIO_PULLDOWN;

	HAL_GPIO_Init(GPIOA, &left_button);
	HAL_NVIC_SetPriority(EXTI0_IRQn, 15, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

void setup_right_button(){

	right_button.Pin = GPIO_PIN_1;
	right_button.Mode = GPIO_MODE_IT_FALLING;
	right_button.Pull = GPIO_PULLDOWN;

	HAL_GPIO_Init(GPIOA, &right_button);
	HAL_NVIC_SetPriority(EXTI1_IRQn, 15, 0);
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);
}

void setup_rows(){

	//Initialize GPIO for rows. 1 to turn on the LED. 0 to turn off the LED
	rows.Mode = GPIO_MODE_OUTPUT_PP;
	rows.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4
					| GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
	rows.Pull = GPIO_PULLUP;

	HAL_GPIO_Init(GPIOB, &rows);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);

}

void setup_columns(){

	//Make columns as output mode. 0(BIT_SET) to turn on the LED,
	//1(BIT_RESET) to turn off the LED
	columns.Mode = GPIO_MODE_OUTPUT_PP;
	columns.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4
						| GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
	columns.Pull = GPIO_PULLUP;

	HAL_GPIO_Init(GPIOC, &columns);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
}


void EXTI0_IRQHandler(void){

	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);

	move_paddle(LEFT);
	*paddle_position = *paddle_position - 1;

}

void EXTI1_IRQHandler(void){

	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);

	move_paddle(RIGHT);
	*paddle_position = *paddle_position + 1;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN){

	//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}

