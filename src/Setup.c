/*
 * Setup.c
 *
 *  Created on: 23/03/2021
 *      Author: juanp
 */

#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"

uint8_t *rows_gpio[8];
uint8_t *columns_gpio[8];

//Initialize the array for rows_gpio
void setup_rows_gpio(){

	//Initialize the address
	rows_gpio[0] = (uint8_t*)0x20000090;
	rows_gpio[1] = (uint8_t*)0x20000098;
	rows_gpio[2] = (uint8_t*)0x20000106;
	rows_gpio[3] = (uint8_t*)0x20000114;
	rows_gpio[4] = (uint8_t*)0x20000120;
	rows_gpio[5] = (uint8_t*)0x20000128;
	rows_gpio[6] = (uint8_t*)0x20000136;
	rows_gpio[7] = (uint8_t*)0x20000142;

	//Initialize the values
	*rows_gpio[0] = GPIO_PIN_0;
	*rows_gpio[1] = GPIO_PIN_1;
	*rows_gpio[2] = GPIO_PIN_2;
	*rows_gpio[3] = GPIO_PIN_3;
	*rows_gpio[4] = GPIO_PIN_4;
	*rows_gpio[5] = GPIO_PIN_5;
	*rows_gpio[6] = GPIO_PIN_6;
	*rows_gpio[7] = GPIO_PIN_7;
}

void setup_columns_gpio(){

	//Initialize the address
	columns_gpio[0] = (uint8_t*)0x20000200;
	columns_gpio[1] = (uint8_t*)0x20000208;
	columns_gpio[2] = (uint8_t*)0x20000216;
	columns_gpio[3] = (uint8_t*)0x20000232;
	columns_gpio[4] = (uint8_t*)0x20000240;
	columns_gpio[5] = (uint8_t*)0x20000248;
	columns_gpio[6] = (uint8_t*)0x20000256;
	columns_gpio[7] = (uint8_t*)0x20000264;

	//Initialize the values
	*columns_gpio[0] = GPIO_PIN_0;
	*columns_gpio[1] = GPIO_PIN_1;
	*columns_gpio[2] = GPIO_PIN_2;
	*columns_gpio[3] = GPIO_PIN_3;
	*columns_gpio[4] = GPIO_PIN_4;
	*columns_gpio[5] = GPIO_PIN_5;
	*columns_gpio[6] = GPIO_PIN_6;
	*columns_gpio[7] = GPIO_PIN_7;
}

void setup_matrix_address(uint8_t **matrix){

	//Initialize pointers to the beginning of SRAM
	matrix[0] = (uint8_t*)0x20000000;
	matrix[1] = (uint8_t*)0x20000008;
	matrix[2] = (uint8_t*)0x20000016;
	matrix[3] = (uint8_t*)0x20000024;
	matrix[4] = (uint8_t*)0x20000032;
	matrix[5] = (uint8_t*)0x20000040;
	matrix[6] = (uint8_t*)0x20000048;
	matrix[7] = (uint8_t*)0x20000056;

	//Fill the address value with the default game screen
	*matrix[0] = 0b11111111;
	*matrix[1] = 0b11111111;
	*matrix[2] = 0b11111111;
	*matrix[3] = 0b00000000;
	*matrix[4] = 0b00000000;
	*matrix[5] = 0b00000000;
	*matrix[6] = 0b00001000;
	*matrix[7] = 0b00011100;
}
