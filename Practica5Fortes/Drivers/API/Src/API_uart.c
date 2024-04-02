/*
 * API_uart.c
 *
 *  Created on: Nov 20, 2023
 *      Author: facuf23
 */

#include <string.h>
#include "API_delay.h"
#include "stm32f4xx_hal.h"
#include "API_uart.h"

#define TO 2000


UART_HandleTypeDef uartHandler;

bool_t uartInit(){

	bool_t initFlag = false;

	uartHandler.Instance = USART2;
	uartHandler.Init.BaudRate = 115200;
	uartHandler.Init.WordLength = UART_WORDLENGTH_8B;
	uartHandler.Init.StopBits = UART_STOPBITS_1;
	uartHandler.Init.Parity = UART_PARITY_NONE;
	uartHandler.Init.Mode = UART_MODE_TX_RX;
	uartHandler.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uartHandler.Init.OverSampling = UART_OVERSAMPLING_16;

	  if (HAL_UART_Init(&uartHandler) == HAL_OK)
	  {

		  initFlag = true;

	  	  uint8_t setMsg[] = "Uart init";

	  	  uartSendString(setMsg);


	  }

	  	  return initFlag;

}


void uartSendString(uint8_t * pstring){

	HAL_UART_Transmit(&uartHandler, pstring, sizeof(pstring), TO);


}



void uartSendStringSize(uint8_t * pstring, uint16_t size){

	HAL_UART_Transmit(&uartHandler, pstring, size, TO);

}


void uartReceiveStringSize(uint8_t * pstring, uint16_t size){

	HAL_UART_Receive(&uartHandler, pstring, size, TO);

}
