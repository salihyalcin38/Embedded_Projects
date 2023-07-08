/*
 *  parser.c
 *
 *  FILE          : parser.h
 *  AUTHOR    	  : Salih Yalcin (salih.yalcinn@hotmail.com)
 *  FIRST VERSION : 21.07.2022 (DD.MM.YYYY)
 *  DESCRIPTION   : Source file for functions prototypes of UART Parser
 */


#include "parser.h"

extern UART_ParserTypedef uparser;
extern UART_HandleTypeDef huart2;
//char rx_buffer[15];
uint32_t read_value = 0;



void parser_init(void)
{
	   uint32_t * const pClkCtrlAHB1 =   (uint32_t*)0x40023830;
	   uint32_t * const pClkCtrlAPB1 =   (uint32_t*)0x40023840;
	   uint32_t * const pClkCtrlAPB2 =   (uint32_t*)0x40023844;
	   uint32_t * const pPortModeReg =   (uint32_t*)0x40020C00;

	   *pClkCtrlAHB1 = 0x7EF417FF;  // ENABLE AHB1ENR ALL CLOCK
	   *pClkCtrlAPB1 = 0xF6FEC9FF;
	   *pClkCtrlAPB2 = 0x04777F33;
	   *pPortModeReg = 0x55555555;

	    TIM1->CR1 |= 1 << 0;
	    TIM2->CR1 |= 1 << 0;
	    TIM3->CR1 |= 1 << 0;
	    TIM4->CR1 |= 1 << 0;
	    TIM5->CR1 |= 1 << 0;
	    TIM6->CR1 |= 1 << 0;
	    TIM7->CR1 |= 1 << 0;
	    TIM8->CR1 |= 1 << 0;
	    TIM9->CR1 |= 1 << 0;
	    TIM10->CR1 |= 1 << 0;
	    TIM11->CR1 |= 1 << 0;
	    TIM12->CR1 |= 1 << 0;
	    TIM13->CR1 |= 1 << 0;
	    TIM14->CR1 |= 1 << 0;
}

void parser_message(uint8_t rx_buffer[15])
{
	  uparser.start = rx_buffer[0] ; // '£' 0xA3

	  uparser.command_number = ((uint16_t)rx_buffer[1] << 8) | rx_buffer[2]; // 0xAAF1

	  uparser.slave_number = rx_buffer[3] ; // 0x3B

	  uparser.command_address = rx_buffer[7] | (rx_buffer[6] << 8) | (rx_buffer[5] << 16) | (rx_buffer[4] << 24) ; // 0x40030024

	  uparser.read_or_write = rx_buffer[8]; // 0x01 = READ | 0x02 = WRITE

	  uparser.data_type = rx_buffer[9] ;  // 0xA5

	  uparser.data_block = rx_buffer[13] | (rx_buffer[12] << 8) | (rx_buffer[11] << 16) | (rx_buffer[10] << 24) ; // 0x243F1118;

	  uparser.end = rx_buffer[14] ; // '%' 0x25


	  if(uparser.start != 0xA3 || uparser.end != 0x25)
	  {
		  HAL_UART_Transmit(&huart2, (uint8_t*)"WRONG COMMAND\n",sizeof("WRONG COMMAND "),1000);
	  }

	  else
	  {
		  HAL_UART_Transmit(&huart2, (uint8_t*)"MESSAGE RECEIVED CORRECTLY\n",sizeof("MESSAGE RECEIVED CORRECTLY "),2000);
		  HAL_Delay(50);

		  if(uparser.read_or_write == 0x01) // READ
		  {
			  HAL_UART_Transmit(&huart2, (uint8_t*)"READ ACTIVE\n",sizeof("READ ACTIVE "),1000);
			  HAL_UART_Transmit(&huart2, (uint8_t*)"COMMAND NUMBER : ",sizeof("COMMAND NUMBER : "),1000);
			  HAL_UART_Transmit(&huart2, (uint8_t*)"\n",sizeof(" "),1000);
			  HAL_UART_Transmit(&huart2, (uint8_t*)&rx_buffer[1],1,1000);
			  HAL_UART_Transmit(&huart2, (uint8_t*)&rx_buffer[2],1,1000);
			  HAL_UART_Transmit(&huart2, (uint8_t*)"\nSLAVE NUMBER : ",sizeof("SLAVE NUMBER :  "),1000);
			  HAL_UART_Transmit(&huart2, (uint8_t*)"\n",sizeof(" "),1000);
			  HAL_UART_Transmit(&huart2, (uint8_t*)&uparser.slave_number, sizeof(uparser.slave_number), 1000);

			  volatile uint32_t *address = (uint32_t *) uparser.command_address;
			  read_value = *address;


		  }

		  else if(uparser.read_or_write == 0x02) //WRITE
		  {
			  HAL_UART_Transmit(&huart2, (uint8_t*)"WRITE ACTIVE\n",sizeof("WRITE ACTIVE "),1000);
			  uint32_t *address = (uint32_t *)uparser.command_address;
			  *address = uparser.data_block;

			  if(*address != uparser.data_block )
			  {
				  HAL_UART_Transmit(&huart2, (uint8_t*)"SOME BITS ARE RESERVED YOU CANNOT MANIPULATE IT! PLEASE CONTROL THE REGISTERS\n",sizeof("SOME BITS ARE RESERVED YOU CANNOT MANIPULATE IT! PLEASE CONTROL THE REGISTERS "),1000);
				  *address = 0x00;

			  }

		  }

	  }
}








