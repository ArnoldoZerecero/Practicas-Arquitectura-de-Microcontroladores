/*
 * MISCELANEO.c
 *
 *  Created on: Aug 2, 2017
 *      Author: Alumnos
 */

#include <stdint.h>
#include <string.h>
#include "derivative.h"
#include "MISCELANEO.h"
#include "shell.h"


void vfnGPIOInit(void)
{
	SIM_SCGC5  |= SIM_SCGC5_PORTB_MASK; /*Se activa el clk para el puerto B*/

	PORTB_PCR0 |= PORT_PCR_MUX(1); /*Se activa el pin 0 del puerto B como GPIO para el LED*/
	PORTB_PCR1 |= PORT_PCR_MUX(1); /*Se activa el pin 1 del puerto B como GPIO para el buzzer*/
	GPIOB_PDDR |= 3; /*Se utilizaran los pines 0 y 1 del puerto B como salida (11)*/
}

void vfnLED(int8_t * bpEncendido, int8_t * bpParametro2)
{
	if(!(strcmp((char *)bpEncendido, "on"))) /*Se prende el LED*/
	{
		GPIOB_PDOR |= 1; 
	}
	else if(!(strcmp((char *)bpEncendido, "off"))) /*Se apaga el LED*/
	{
		GPIOB_PDOR &= ~1;
	}
	else
	{
		vfnMensajeError();
	}
}

void vfnBuzzer(int8_t * bpEncendido, int8_t * bpParametro2)
{
	if(!(strcmp((char *)bpEncendido, "on"))) /*Se prende el buzzer*/
	{
		GPIOB_PDOR |= 2; 
	}
	else if(!(strcmp((char *)bpEncendido, "off"))) /*Se apaga el buzzer*/
	{
		GPIOB_PDOR &= ~2;
	}
	else
	{
		vfnMensajeError();
	}
}

uint16_t wfnBCD(uint16_t wResultado) /*Se obtiene una variable de 16 bits con cada valor (M C D U) en paquetes de 4 bits*/
{
	uint16_t wMillares = wResultado/1000;
	uint16_t wCentenas = (wResultado%1000)/100;
	uint16_t wDecenas = ((wResultado%1000)%100)/10;
	uint16_t wUnidades = ((wResultado%1000)%100)%10;

	uint16_t wBCD = ((wMillares << 12) | (wCentenas << 8) | (wDecenas << 4) | (wUnidades));
	return wBCD;
}

uint32_t dwfnBCDADecimal(uint8_t bUnidades, uint8_t bDecenas, uint8_t bCentenas, uint8_t bMillares) /*Operación inversa a BCD*/
{
	uint32_t dwResultado = ((bMillares*1000) + (bCentenas*100) + (bDecenas*100) + bUnidades);

	return dwResultado;
}


void vfnDelay (uint32_t dwDelay)
{
	uint32_t dwIndex = 0;
	do
	{
		dwIndex++;
	}while (dwIndex != dwDelay);
	dwIndex = 0;
}
