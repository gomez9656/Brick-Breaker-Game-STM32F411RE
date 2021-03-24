/*
 * Paddle.c

 *
 *  Created on: 23/03/2021
 *      Author: juanp
 */


#include "Paddle.h"



void move_paddle(uint8_t direction){

	//Pointer to last row
	uint8_t *last_row = (uint8_t*)0x20000056;

	if(direction == RIGHT){

		*last_row = *last_row << 1;
	}
	else{

		*last_row = *last_row >> 1;
	}
}
