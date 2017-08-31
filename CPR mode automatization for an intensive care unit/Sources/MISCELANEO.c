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
#include "PIT.h"

void vfnGPIOInit(void)
{
	SIM_SCGC5  |= SIM_SCGC5_PORTB_MASK; /*Se activa el clk para el puerto B*/
	SIM_SCGC5  |= SIM_SCGC5_PORTC_MASK; /*Se activa el clk para el puerto C*/

	PORTB_PCR1 |= PORT_PCR_MUX(1); /*Se activa el pin 1 del puerto B como GPIO para el buzzer*/
	PORTB_PCR2 |= PORT_PCR_MUX(1); /*Se activa el pin 2 del puerto B como GPIO para el Select 0 de los demux*/
	PORTB_PCR3 |= PORT_PCR_MUX(1); /*Se activa el pin 3 del puerto B como GPIO para el Select 1 de los demux*/
	GPIOB_PDDR |= 14; /*Se utilizaran los pines 1-3  del puerto B como salida (1110)*/
	GPIOC_PDIR = 0; /*Se comienza limpiando las entradas del puerto C*/
	PORTC_PCR0 |= PORT_PCR_MUX(1); /*Se activa el pin 0 del puerto C como GPIO para entrada del modo tren hacia arriba*/
	PORTC_PCR1 |= PORT_PCR_MUX(1); /*Se activa el pin 1 del puerto C como GPIO para entrada del modo tren hacia abajo*/
	PORTC_PCR2 |= PORT_PCR_MUX(1); /*Se activa el pin 2 del puerto C como GPIO para entrada del modo rotacion hacia la derecha*/
	PORTC_PCR3 |= PORT_PCR_MUX(1); /*Se activa el pin 3 del puerto C como GPIO para entrada del modo rotacion hacia la izquierda*/
	PORTC_PCR4 |= PORT_PCR_MUX(1); /*Se activa el pin 4 del puerto C como GPIO para entrada del modo altura hacia arriba*/
	PORTC_PCR5 |= PORT_PCR_MUX(1); /*Se activa el pin 5 del puerto C como GPIO para entrada del modo altura hacia abajo*/
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
