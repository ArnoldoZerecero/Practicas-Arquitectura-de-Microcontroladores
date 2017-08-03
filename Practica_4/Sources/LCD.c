/*
 * LCD.c
 *
 *  Created on: Jul 30, 2017
 *      Author: Windows 8.1
 */

#include <stdint.h>
#include "derivative.h"
#include "LCD.h"
#include "MISCELANEO.h"

void vfnLCDInit (void) /*Inicialización*/
{
	SIM_SCGC5  |= SIM_SCGC5_PORTB_MASK; /*Se activa el clk para el puerto B*/
	SIM_SCGC5  |= SIM_SCGC5_PORTC_MASK; /*Se activa el clk para el puerto C*/

	PORTB_PCR0 |= PORT_PCR_MUX(1); /*Se activa el pin 0 del puerto B para ENABLE*/
	PORTB_PCR1 |= PORT_PCR_MUX(1); /*Se activa el pin 1 del puerto B para el RS*/
	GPIOB_PDDR |= 3; /*Se utilizaran los pines 0 y 1 del puerto B como salida (11)*/

	PORTC_PCR0 |= PORT_PCR_MUX(1); /*Se activan pines 0 - 7 del puerto C*/
	PORTC_PCR1 |= PORT_PCR_MUX(1);
	PORTC_PCR2 |= PORT_PCR_MUX(1);
	PORTC_PCR3 |= PORT_PCR_MUX(1);
	PORTC_PCR4 |= PORT_PCR_MUX(1);
	PORTC_PCR5 |= PORT_PCR_MUX(1);
	PORTC_PCR6 |= PORT_PCR_MUX(1);
	PORTC_PCR7 |= PORT_PCR_MUX(1);	
	GPIOC_PDDR |= 0xFF; /*Se utilizaran los pines 0 - 7 del puerto C como salida (11111111)*/


	vfnLCDComandoOCaracter(0, EIGHT_BIT_TWO_LINES); /*Se le asigna el comando de modo 8 bits de 2 lineas 3 veces para que el LCD capte bien el comando*/
	vfnLCDComandoOCaracter(0, EIGHT_BIT_TWO_LINES);
	vfnLCDComandoOCaracter(0, EIGHT_BIT_TWO_LINES);
	vfnLCDComandoOCaracter(0, DISPLAY_ON); /*Se enciende el display, con el cursos intermitente*/
	vfnLCDComandoOCaracter(0, CLEAR_DISPLAY); /*Se limpia el display*/
}

void vfnLCDComandoOCaracter(uint8_t bEnableOrRS, uint8_t bCommandOrCharacter)
{
	if(bEnableOrRS) /*Si se eligió escribir un dato*/
	{
		REGISTER_SELECT_ON; /*Se activa el modo de escritura de caracteres*/
	}
	else /*Si se eligió escribir un comando*/
	{
		REGISTER_SELECT_OFF; /*Se apaga la escritura de caracteres*/
	}
	
	DATA_CLEAR; /*Se limpia el dato anterior*/
	GPIOC_PDOR |= bCommandOrCharacter; /*Se escribe el dato en el puerto C*/
	ENABLE_ON; /*Se prende el enable*/
	vfnDelay(DELAY_TIME); /*Se debe asignar un delay entre cada asignación de data/comandos*/
	ENABLE_OFF; /*Se apaga el enable, finalizando el paso del comando*/
}

void vfnLCDEnviarPalabra(int8_t *bpPalabra, uint8_t bDataSize)
{
	uint8_t bIndexPalabra = 0;

	do
	{
		vfnLCDComandoOCaracter(1, bpPalabra[bIndexPalabra]);
		bIndexPalabra++;
	}while(bIndexPalabra != bDataSize);

	bIndexPalabra = 0;
}


void vfnLCDCoordenadas(uint8_t bLinea, uint8_t bOffset) /*Función para comenzar a escribir desde cierto punto*/
{
	uint8_t bComando = 0; /*El comando en sí para la función de comandos*/
	
	if(bLinea) /*Si se encuentra en la segunda linea*/
	{
		bComando = bComando + 64;
	}
	bComando = bComando + 128 + bOffset; /*Se le agrega el MSB y el Offset*/
	vfnLCDComandoOCaracter(0, bComando);
	bComando = 0;
}

