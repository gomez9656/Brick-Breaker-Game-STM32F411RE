/*
 * Ball.c
 *
 *  Created on: 23/03/2021
 *      Author: juanp
 */
#include <stdint.h>
#include "Ball.h"
#include "GPIO.h"

//Ball states
#define UP					0
#define DOWN				1
#define UP_LEFT				2
#define UP_RIGHT			3
#define DOWN_LEFT			4
#define DOWN_RIGHT			5

//Collision states
#define MOVING				0
#define COLLISION_UP		1
#define COLLISION_DOWN		2
#define COLLISION_UP_LEFT 	3
#define COLLISION_UP_RIGHT	4



//The ball start in row #6, but for timer things use 7. Ball start in column #4
uint8_t pos_x = 4;
uint8_t pos_y = 6;

uint8_t limit_x = 8;
uint8_t limit_y = 8;

uint8_t *matrix[8];

uint8_t ball_state;
uint8_t collision_state = MOVING;

uint8_t count_left = 1;
uint8_t count_right = 1;

//Initialize the ball to go up
void start_ball(){

	ball_state = UP;
}


void move_ball(uint8_t first_move){

	matrix[0] = (uint8_t*)0x20000000;
	matrix[1] = (uint8_t*)0x20000008;
	matrix[2] = (uint8_t*)0x20000016;
	matrix[3] = (uint8_t*)0x20000024;
	matrix[4] = (uint8_t*)0x20000032;
	matrix[5] = (uint8_t*)0x20000040;
	matrix[6] = (uint8_t*)0x20000048;
	matrix[7] = (uint8_t*)0x20000056;



	switch(ball_state){

	case UP:

		collision(pos_x, pos_y, matrix);

		if(first_move == 0){
			//Do nothing
		}else{

			if(collision_state != COLLISION_UP){

				*matrix[pos_y] &= ~(1 << (pos_x - 1));//turn off the actual ball position
				*matrix[pos_y - 1] = *matrix[pos_y - 1] | (1 << (pos_x - 1)); //turn on the next ball position
				pos_y--;

			}else if(collision_state == COLLISION_UP){

				*matrix[pos_y - 1] &= ~(1 << (pos_x - 1));//Turn off the brick you hit
			}
		}
		break;

	case DOWN:

		collision(pos_x, pos_y, matrix);

		if(collision_state != COLLISION_DOWN){

			*matrix[pos_y] &= ~(1 << (pos_x - 1));
			*matrix[pos_y + 1] = *matrix[pos_y + 1] | (1 << (pos_x - 1));
			pos_y++;

		}else if(collision_state == COLLISION_DOWN){
			//collision with paddle
		}

		break;

	case UP_LEFT:

		collision(pos_x, pos_y, matrix);

		if(collision_state != COLLISION_UP_LEFT){

				*matrix[pos_y] &= ~(1 << (pos_x - 1));//turn off the actual ball position
				pos_x--;
				*matrix[pos_y - 1] = *matrix[pos_y - 1] | (1 << (pos_x - 1)); //turn on the next ball position
				pos_y--;


		}else if(collision_state == COLLISION_UP_LEFT){

			*matrix[pos_y - 1] &= ~(1 << (pos_x - 1));//Turn off the brick you hit
		}

		break;

	case UP_RIGHT:

		collision(pos_x, pos_y, matrix);

		if(collision_state != COLLISION_UP_RIGHT){

			*matrix[pos_y] &= ~(1 << (pos_x - 1));//turn off the actual ball position
			pos_x++;
			*matrix[pos_y - 1] = *matrix[pos_y -1] | (1 << (pos_x + 1)); //turn on the next ball position
			pos_y--;

			}else if(collision_state == COLLISION_UP_RIGHT){

				*matrix[pos_y - 1] &= ~(1 << (pos_x + 1));//Turn off the brick you hit
			}

		break;
	case DOWN_LEFT:
		break;
	case DOWN_RIGHT:
		break;
	default:
		break;
	}
}

void collision(uint8_t x, uint8_t y, uint8_t **matrix){

	//int r = rand() % 3;
	int r = 1;

	switch(ball_state){

	case UP:

		if(*matrix[y - 1] & (1 << (x - 1))){

			collision_state = COLLISION_UP;
			ball_state = DOWN;
		}
		break;

	case DOWN:

		if(*matrix[y + 1] & (1 << (x - 1))){

			collision_state = COLLISION_DOWN;

			if(r == 0){

				ball_state = UP;
			}
			else if(r == 1){

				ball_state = UP_LEFT;
			}

			else if(r == 2){

				ball_state = UP_RIGHT;
			}
		}
		break;

		break;

	case UP_LEFT:

		if(*matrix[y - 1] & (1 << (x - 1))){

			collision_state = COLLISION_UP_LEFT;
			if( r == 0){

				ball_state = DOWN;
			}
			else if( r == 1){

				ball_state = DOWN_RIGHT;
			}
			else if( r == 2){

			ball_state = DOWN_LEFT;
			}
		}

		break;
	case UP_RIGHT:

		if(*matrix[y - 1] & (1 << (x - 1))){

			collision_state = COLLISION_UP_LEFT;
			if( r == 0){

				ball_state = DOWN;
			}
			else if( r == 1){

				ball_state = DOWN_RIGHT;
			}
			else if( r == 2){

				ball_state = DOWN_LEFT;
			}
		}


		break;
	case DOWN_LEFT:
		break;
	case DOWN_RIGHT:
		break;
	default:
		break;
	}
}
