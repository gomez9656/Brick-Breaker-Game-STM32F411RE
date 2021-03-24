/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"
#include "Setup.h"
#include "RCC.h"
#include "GPIO.h"
#include "USART.h"
#include "Ball.h"
#include "Display.h"
#include "TIMER.h"

//Array of pointers to 8x8 bit address
uint8_t *game_matrix[8];


int main(void)
{
	HAL_Init();

	//Initialize pointers
	setup_matrix_address(game_matrix);
	setup_rows_gpio();
	setup_columns_gpio();

	setup_RCC();
	setup_GPIO();
	TIMER3_Init();
	setup_USART();

	start_ball();

	while(1){

		print_display(game_matrix);
	}
}


void Error_handler(void){
	while(1);
}

void HAL_MspInit(void){
	//Low level initializations

	//1. Set up priority grouping
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	//2. Enable the required system exceptions
	SCB->SHCSR |= 0x7 << 16; //usage fault, memory fault and bus fault system exception

	//3. Configure the priority for the system exception
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
}

