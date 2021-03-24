/*
 * Display.c
 *
 *  Created on: 23/03/2021
 *      Author: juanp
 */
#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"
#include "Display.h"

uint8_t print_mask = 0b11111111;
uint8_t mask_result = 0;

uint8_t *rows_gpio[8];
uint8_t *columns_gpio[8];

/*
 * Receive the matrix(display). Use the print_mask to test the rows that are ON.
 * If the result is !0 then, turn on that row.
 */
void print_display(uint8_t **matrix){

	//CHeck the rows with print_mask
	for( int i = 0; i < 8; i++){

		mask_result = *matrix[i] & print_mask;

		if( mask_result != 0){

			//Turn on the respective row
			HAL_GPIO_WritePin(GPIOB, *rows_gpio[7 - i], GPIO_PIN_SET);

			//Check the columns
			for( int j = 0; j < 8; j++){

				if( (mask_result & (1 << j)) != 0 ){

					HAL_GPIO_WritePin(GPIOC, *columns_gpio[7 - j], GPIO_PIN_RESET);
				}
				else{

					HAL_GPIO_WritePin(GPIOC, *columns_gpio[7 - j], GPIO_PIN_SET);
				}
			}

			//This delay is for the eyes, Without it, you can´t see the display as it should be
			delay_for_eyes();

			//After each row, turn it off. This also helps your eyes to see the display as it should be
			turn_off_for_eyes(i);

		}else{

			//Turn off the respective row
			HAL_GPIO_WritePin(GPIOB, *rows_gpio[7 - i], GPIO_PIN_RESET);
		}
	}
}

void delay_for_eyes(){

	for( int m = 0; m < 5000; m++){
			continue;
	}
}

void turn_off_for_eyes(int i){

	HAL_GPIO_WritePin(GPIOB, *rows_gpio[7 - i], GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
}
