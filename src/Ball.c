/*
 * Ball.c
 *
 *  Created on: 23/03/2021
 *      Author: juanp
 */
#include <stdint.h>

#define UP						0
#define DOWN					1
#define UP_LEFT					2
#define UP_RIGHT				3
#define DOWN_LEFT				4
#define DOWN_RIGHT				5


uint8_t pos_x = 4;
uint8_t pos_y = 6;

uint8_t limit_x = 8;
uint8_t limit_y = 8;


uint8_t ball_state;

//Initialize the ball to go up
void start_ball(){

	ball_state = UP;
}


void move_ball(uint8_t **matrix){

	switch(ball_state){

	case UP:

		for(int i = pos_y; i > 0; i--){

			*matrix[i - 1] |=  (1 << (pos_x - 1));

			print_display(matrix);
		}
		break;

	case DOWN:
		break;
	case UP_LEFT:
		break;
	case UP_RIGHT:
		break;
	case DOWN_LEFT:
		break;
	case DOWN_RIGHT:
		break;
	default:
		break;
	}
}

