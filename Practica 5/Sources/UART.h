/*
 * UART.h
 *
 *  Created on: Jul 24, 2017
 *      Author: Alumnos
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include <stddef.h>
#include <stdint.h>

typedef void(* UartUserCallback_t)(uint8_t); /*Función de Callback, para la cual se creará un apuntador*/


typedef struct 
{
	uint8_t bStopBitNumber; /*Elige entre usar 1 o 2 stop bits*/ 
	uint16_t wBaudRate; /*Concatenación de 13 bits de high y low*/ /*High -> Bit 4 - 0 UARTx_BDH*/ /* Low -> Bit 7 - 0 UARTx_BDL*/
	uint8_t bTamanoTrama; /*Elegir entre tramas de 8 y 9 bits de longitud*/ /*Bit 4 de UARTx_C1*/
	uint8_t bParityEnable; /*Bit 1 del UARTx_C1*/
	uint8_t bParityType; /*Bit 0 del UARTx_C1*/
	uint8_t bOSR; /*Elegir valor de 5 bits de over sampling ratio*/
	UartUserCallback_t pfnCallback; /*Apuntador a función Callback*/
}UartConfigInit_t;

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

void vfnUARTCallback(uint8_t bDatosReceptor);

void vfnUartTransmision(uint8_t * DataToSend, uint16_t DataSize);

void vfnUartInit (UartConfigInit_t * pUartUserConfig);

#if defined(__cplusplus)
}
#endif // __cplusplus




#endif /* UART_H_ */
