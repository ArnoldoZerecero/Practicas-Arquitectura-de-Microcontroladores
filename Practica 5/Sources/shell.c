/*
 * shell.c
 *
 *  Created on: Aug 7, 2017
 *      Author: Alumnos
 */

#include "shell.h"
#include "derivative.h"
#include "MISCELANEO.h"
#include "ADC.h"
#include "UART.h"
#include "PIT.h"
#include "PWM.h"
#include <string.h>
#include <stdint.h>

volatile static uint8_t gbPitFinished = 0;

volatile static uint8_t gbBlueLedStatus = 1; /*Variables para saber si los RGB están encendidos o apagados*/

volatile static uint8_t gbRedLedStatus = 1;

volatile static uint8_t gbGreenLedStatus = 1;

static const uint8_t gbaMensajeError[78] =
{
		"\r\nComando no reconocido. Escriba <help> para ver lista de comandos.\r\nComando>"
}; 

static const uint8_t gbaPalabraComando[11] = /*Lo que vamos a mandar antes de cada comando*/
{
		"\r\nComando>"
}; 

void vfnMensajeError(void)
{
	vfnUartTransmision((uint8_t *)&gbaMensajeError[0], (sizeof(gbaMensajeError) - 1U)); /*Se manda el mensaje de error*/
}

void vfnClearScreen(int8_t * bpParametro1, int8_t * bpParametro2) /*Limpia la pantalla*/
{
	uint8_t baComando[2] = /*Comando para limpiar pantalla*/
	{
			ESC_CARACTER, 'c'
	}; 
	vfnUartTransmision((uint8_t *)&baComando[0],(sizeof(baComando)));
	vfnDelay(6000);

	
}

void vfnPrintScreen(int8_t * bpParametro1, int8_t * bpParametro2) /*Imprime la pantalla*/
{
	static const uint8_t baComando[3] = /*Comando para imprimir pantalla*/
	{
			ESC_CARACTER, ABRIR_CORCHETE_CARACTER, 'i'
	}; 
	vfnUartTransmision((uint8_t *)&baComando[0], (sizeof(baComando)));
	vfnUartTransmision((uint8_t *)&gbaPalabraComando[0], (sizeof(gbaPalabraComando) - 1U));
	vfnDelay(6000);
}

void vfnColorFuente(int8_t * bpColor, int8_t * bpParametro2) /*Cambia el color de la fuente*/
{
	uint8_t baComando[5] = /*Comando para imprimir pantalla*/
	{
			ESC_CARACTER, ABRIR_CORCHETE_CARACTER, NUEVE_CARACTER, bpColor[0], 'm'
	}; 
	if(bpColor[0] < '0' || bpColor[0] > '7') /*Si no es un número entre 0 y 7*/
	{
		vfnMensajeError();
	}
	else
	{
		vfnUartTransmision((uint8_t *)&baComando[0], (sizeof(baComando)));
		vfnDelay(6000);
	}
}
void vfnPeriodidPotRead(int8_t * bpStartStop, int8_t * bpPeriodo) /*Reporte periódico del potenciómetro*/
{
	static uint32_t dwPeriodo; /*Variable para mandar periodo al pot desde el segundo parámetro*/

	if(!(strcmp((char *)bpStartStop, "start")))  /*Si se decidió iniciar el reporte*/
	{
		dwPeriodo = dwfnBCDADecimal(bpPeriodo[3] - 48, bpPeriodo[2] - 48, bpPeriodo[1] - 48, bpPeriodo[0] - 48);/*Los valores tecleados en el arreglo se convierten en un valor numérico*/
		vfnPitInit(dwPeriodo*10500, &vfnPitCallback); /*Se inicializa el pit con el valor del periodo mandado en ms como parámetro*/
		vfnPitStart(); /*Comienza la cuenta del pit*/
	}
	else if (!(strcmp((char *)bpStartStop, "stop"))) 
	{
		vfnPitStop();/*Termina la cuenta del pit*/
	}
	else
	{
		vfnMensajeError();
	}
}


void vfnCommandList(int8_t * bpParametro1, int8_t * bpParametro2) /*Muestra la lista de comandos*/
{
	static const int8_t baListaComandos[1150] = /*Lista de comandos*/
	{
			"\r\n\rComandos soportados:\r\n\r1.help: Muestra la lista de comandos.\r\n\r2.cls:  Limpia la pantalla, resetea el formato de fuente.\r\n\r3.rgb (color): Enciende el LED del microcontrolador de ese color. Colores soportados: azul, rojo, verde, amarillo, rosa, blanco, aqua y naranja.\r\n\r4.led (color) (accion):  Elige que color de LED de rgb del microcontrolador utilizar y encenderlo, apagarlo o togglearlo. Colores soportados: azul, rojo y verde. Acciones posibles: on, off y toggle.\r\n\r5.pot (start/stop) (periodo(ms), en formato 0000): Comienza o detiene el reporte periodico del voltaje (de 0 a 3.3 volts) medido a traves del potenciómetro externo. La frecuencia de las muestras depende el periodo elegido.\r\n\r6.print: Abre el interfaz de impresoras para mandar a imprimir el texto de la terminal.\r\n\r7.color (numero de 0-7): Cambia el color de fuente de la terminal. Colores soportados: gris(0), rojo(1), verde(2), amarillo(3), azul(4), rosa(5), aqua(6) y blanco(7).\r\n\r8.ledexterno (on/off): Enciende o apaga el LED externo.\r\n\r9.buzzer(on/off): Enciende o apaga el buzzer externo.\r\n\r10.temperatura: Muestra los grados centigrados medidos por el LM35.\r\nComando>"
	};
	vfnUartTransmision((uint8_t *)&baListaComandos[0], (sizeof(baListaComandos) - 1U));
}

void vfnLM35Read(int8_t * bpParametro1, int8_t * bpParametro2) /*Lee la medición actual de temperatura del LM35*/
{
	uint16_t wVoltaje = (bfnADCLectura(3)*330/256); /*Se adquiere el valor del ADC y se convierte a unidades de voltaje*/
	uint16_t wBCD = wfnBCD(wVoltaje); /*Se debe mandar caracter por caracter, por lo que el valor se convierte a BCD*/
	uint16_t wCentenas = ((wBCD & CLEAR_ALL_BUT_HUNDREDS) >> 8) + 48; /*Se dejan solo las centenas y se convierte a ASCII*/
	uint16_t wDecenas = ((wBCD & CLEAR_ALL_BUT_TENS) >> 4) + 48; /*Se dejan solo las decenas y se convierte a ASCII*/
	uint16_t wUnidades = ((wBCD & CLEAR_ALL_BUT_UNITS)) + 48; /*Se dejan solo las unidades y se convierte a ASCII*/
	
	int8_t baValorLM35[9] = /*Comando para imprimir pantalla*/
	{
			'\r', '\n', wCentenas, wDecenas, wUnidades, DEGREE_SYMBOL, 'C','\r','\n' /*Se lee el resultado de ADC, lo ajusta, lo pasa al BCD, lo divide en centenas, decenas y unidades, y lo pone en ASCII para ser leido*/
	}; 
	vfnUartTransmision((uint8_t *)&baValorLM35[0], (sizeof(baValorLM35)));
	vfnDelay(6000);
}

void vfnRGBPWMColorSet(int8_t * bpColor,int8_t * bpParametro2) /*Modulación de LEDs via PWM*/
{
	if(!(strcmp((char *)bpColor, "azul"))) /*Si se desea prender el azul*/
	{
		vfnPWMLedDutyCycle(0, 0); /*0% duty cycle para azul*/
		vfnPWMLedDutyCycle(1, 175350); /*100% duty cycle para rojo*/
		vfnPWMLedDutyCycle(2, 175350); /*100% duty cycle para verde*/
		gbBlueLedStatus = 1;
		gbRedLedStatus = 0;
		gbGreenLedStatus = 0;
	}
	else if(!(strcmp((char *)bpColor, "rojo"))) /*Si se desea prender el rojo*/
	{
		vfnPWMLedDutyCycle(0, 175350); /*100% duty cycle para azul*/
		vfnPWMLedDutyCycle(1, 0); /*0% duty cycle para rojo*/
		vfnPWMLedDutyCycle(2, 175350); /*100% duty cycle para verde*/
		gbBlueLedStatus = 0;
		gbRedLedStatus = 1;
		gbGreenLedStatus = 0;

	}
	else if(!(strcmp((char *)bpColor, "verde"))) /*Si se desea prender el verde*/
	{
		vfnPWMLedDutyCycle(0, 175350); /*100% duty cycle para azul*/
		vfnPWMLedDutyCycle(1, 175350); /*100% duty cycle para rojo*/
		vfnPWMLedDutyCycle(2, 0); /*0% duty cycle para verde*/
		gbBlueLedStatus = 0;
		gbRedLedStatus = 0;
		gbGreenLedStatus = 1;
	}
	else if(!(strcmp((char *)bpColor, "amarillo"))) /*Si se desea prender el amarillo*/
	{
		vfnPWMLedDutyCycle(0, 175350); /*100% duty cycle para azul*/
		vfnPWMLedDutyCycle(1, 0); /*0% duty cycle para rojo*/
		vfnPWMLedDutyCycle(2, 0); /*0% duty cycle para verde*/
		gbBlueLedStatus = 0;
		gbRedLedStatus = 1;
		gbGreenLedStatus = 1;
	}
	else if(!(strcmp((char *)bpColor, "rosa"))) /*Si se desea prender el rosa*/
	{
		vfnPWMLedDutyCycle(0, 0); /*0% duty cycle para azul*/
		vfnPWMLedDutyCycle(1, 0); /*0% duty cycle para rojo*/
		vfnPWMLedDutyCycle(2, 175350); /*100% duty cycle para verde*/
		gbBlueLedStatus = 1;
		gbRedLedStatus = 1;
		gbGreenLedStatus = 0;
	}
	else if(!(strcmp((char *)bpColor, "blanco"))) /*Si se desea prender el blanco*/
	{
		vfnPWMLedDutyCycle(0, 0); /*0% duty cycle para azul*/
		vfnPWMLedDutyCycle(1, 0); /*0% duty cycle para rojo*/
		vfnPWMLedDutyCycle(2, 0); /*0% duty cycle para verde*/
		gbBlueLedStatus = 1;
		gbRedLedStatus = 1;
		gbGreenLedStatus = 1;
	}
	else if(!(strcmp((char *)bpColor, "aqua"))) /*Si se desea prender el aqua*/
	{
		vfnPWMLedDutyCycle(0, 0); /*0% duty cycle para azul*/
		vfnPWMLedDutyCycle(1, 175350); /*100% duty cycle para rojo*/
		vfnPWMLedDutyCycle(2, 0); /*0% duty cycle para verde*/
		gbBlueLedStatus = 1;
		gbRedLedStatus = 0;
		gbGreenLedStatus = 1;
	}
	else if(!(strcmp((char *)bpColor, "naranja")))/*Si se desea prender el naranja*/
	{
		vfnPWMLedDutyCycle(0, 175350); /*100% duty cycle para azul*/
		vfnPWMLedDutyCycle(1, 0); /*0% duty cycle para rojo*/
		vfnPWMLedDutyCycle(2, 43838); /*25% duty cycle para verde*/
		gbBlueLedStatus = 0;
		gbRedLedStatus = 1;
		gbGreenLedStatus = 1;
	}
	else
	{
		vfnMensajeError();
	}
}

void vfnPWMLEDOnOffToggle(int8_t * bpColor, int8_t *bpAccion)
{
	if(!(strcmp((char *)bpColor, "azul"))) /*Si se desea prender el azul*/
	{
		if(!(strcmp((char *)bpAccion, "on")))
		{
			vfnPWMLedDutyCycle(0, 0); /*0% duty cycle para azul*/
			gbBlueLedStatus = 1;
		}
		else if(!(strcmp((char *)bpAccion, "off")))
		{
			vfnPWMLedDutyCycle(0, 175350); /*100% duty cycle para azul*/
			gbBlueLedStatus = 0;
		}
		else if(!(strcmp((char *)bpAccion, "toggle")))
		{
			if(gbBlueLedStatus) /*Si está prendido*/
			{
				vfnPWMLedDutyCycle(0, 175350); /*Lo apago*/
				gbBlueLedStatus = 0;
			}
			else /*Si está apagado*/
			{
				vfnPWMLedDutyCycle(0, 0); /*Lo prendo*/
				gbBlueLedStatus = 1;
			}
		}
		else
		{
			vfnMensajeError();

		}
	}
	else if(!(strcmp((char *)bpColor, "rojo"))) /*Si se desea prender el rojo*/
	{
		if(!(strcmp((char *)bpAccion, "on")))
		{
			vfnPWMLedDutyCycle(1, 0); /*0% duty cycle para rojo*/
			gbRedLedStatus = 1;
		}
		else if(!(strcmp((char *)bpAccion, "off")))
		{
			vfnPWMLedDutyCycle(1, 175350); /*100% duty cycle para rojo*/
			gbRedLedStatus = 0;
		}
		else if(!(strcmp((char *)bpAccion, "toggle")))
		{
			if(gbRedLedStatus) /*Si está prendido*/
			{
				vfnPWMLedDutyCycle(1, 175350); /*Lo apago*/
				gbRedLedStatus = 0;
			}
			else /*Si está apagado*/
			{
				vfnPWMLedDutyCycle(1, 0); /*Lo prendo*/
				gbRedLedStatus = 1;
			}
		}
		else
		{
			vfnMensajeError();
		}
	}
	else if(!(strcmp((char *)bpColor, "verde"))) /*Si se desea prender el rojo*/
	{
		if(!(strcmp((char *)bpAccion, "on")))
		{
			vfnPWMLedDutyCycle(2, 0); /*0% duty cycle para verde*/
			gbGreenLedStatus = 1;
		}
		else if(!(strcmp((char *)bpAccion, "off")))
		{
			vfnPWMLedDutyCycle(2, 175350); /*100% duty cycle para verde*/
			gbGreenLedStatus = 0;
		}
		else if(!(strcmp((char *)bpAccion, "toggle")))
		{
			if(gbGreenLedStatus) /*Si está prendido*/
			{
				vfnPWMLedDutyCycle(2, 175350); /*Lo apago*/
				gbGreenLedStatus = 0;
			}
			else /*Si está apagado*/
			{
				vfnPWMLedDutyCycle(2, 0); /*Lo prendo*/
				gbGreenLedStatus = 1;
			}
		}
		else
		{
			vfnMensajeError();
		}
	}
	else
	{
		vfnMensajeError();
	}
}


