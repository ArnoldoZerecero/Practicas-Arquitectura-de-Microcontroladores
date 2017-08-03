/*
 * MISCELANEO.c
 *
 *  Created on: Aug 2, 2017
 *      Author: Alumnos
 */

#include <stdint.h>
#include "derivative.h"
#include "MISCELANEO.h"


uint16_t vfnBCD(uint16_t wResultado) /*Se obtiene una variable de 16 bits con cada valor (M C D U) en paquetes de 4 bits*/
{
	uint16_t wMillares = wResultado/1000;
	uint16_t wCentenas = (wResultado%1000)/100;
	uint16_t wDecenas = ((wResultado%1000)%100)/10;
	uint16_t wUnidades = ((wResultado%1000)%100)%10;

	uint16_t wBCD = ((wMillares << 12) | (wCentenas << 8) | (wDecenas << 4) | (wUnidades));
	return wBCD;
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
