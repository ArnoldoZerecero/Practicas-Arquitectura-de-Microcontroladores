///////////////////////////////////////////////////////////////////////////////////////////////////
//                                      Includes Section
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "derivative.h" /* include peripheral declarations */
#include "PIT.h"
#include <stdint.h>
#include "ADC.h"
#include "LCD.h"
#include "MISCELANEO.h"


///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Defines & Macros Section
///////////////////////////////////////////////////////////////////////////////////////////////////

#define CLEAR_ALL_BUT_UNITS ~(0xFFF0)
#define CLEAR_ALL_BUT_TENS ~(0xFF0F)
#define CLEAR_ALL_BUT_HUNDREDS ~(0xF0FF)
#define DEGREE_SYMBOL (223) /*Simbolo de grados (°)*/

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                       Typedef Section
///////////////////////////////////////////////////////////////////////////////////////////////////

ADCConfigInit_t InitParameters = /*Inicializamos los valores de la estructura*/
{
		DIVIDE_RATIO, /*Se utilizará (bus clk)/8*/ 
		1, /*Tiempo de muestreo largo*/
		0, /*Resolución de 8 bits*/
		0, /*24 ADCK cycles por muestreo*/
		1, /*Conversiones continuas*/
		0, /*Promediado por hardware desactivado*/
		MUESTRAS_PROMEDIADAS, /*No se promedian muestras*/
		0, /*Offset*/
};

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                  Function Prototypes Section
///////////////////////////////////////////////////////////////////////////////////////////////////

void vfnPitCallback(void);

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Global Constants Section
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Static Constants Section
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Global Variables Section
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Static Variables Section
///////////////////////////////////////////////////////////////////////////////////////////////////

static volatile uint8_t gbPitCounterADC = 0; /*Contador para el timer del pit para ADC*/

static volatile uint8_t gbPitCounterLED = 0; /*Contador para el timer del pit para LED*/

static uint8_t gbValorLeido; /*Valor leído desde el registro de resultado del ADC*/

static uint8_t bChannel = 0; /*Canal que utilizará el ADC*/

static uint32_t gdwAcumuladorADC = 0; /*Acumulador para el muestreo y promediado del ADC*/

static uint8_t gbIndexADC = 0; /*Indice para promediado del ADC*/

static uint16_t gwPromediado; /*Resultado del promedio*/

static uint16_t gwConversion; /*Resultado del ajuste al valor real*/

uint16_t gwUnidades; /*Unidades de temperatura qué mandar al LCD*/

uint16_t gwDecenas; /*Decenas de temperatura qué mandar al LCD*/

uint16_t gwCentenas; /*Centenas de temperatura qué mandar al LCD*/

static const int8_t gbaPalabraAEnviar[11] = 
{
		"Temperatura" 
};




///////////////////////////////////////////////////////////////////////////////////////////////////
//                                      Functions Section
///////////////////////////////////////////////////////////////////////////////////////////////////



int main(void)
{

	vfnPitInit(TARGET_TIME_100MS,&vfnPitCallback); /*Inicialización del PIT*/

	vfnPitStart(); /*Comienza el contador del PIT*/

	vfnADCInit(&InitParameters); /*Inicialización del ADC*/

	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK; /*Se activa clk para puerto D*/
	PORTD_PCR1 |= PORT_PCR_MUX(1); /*Se utilizará el pin 1 del puerto D para togglear el LED*/
	GPIOD_PDDR |= 2; /*Se utilizará el pin 1 como salida*/

	vfnLCDInit(); /*Inicialización del LCD*/

	vfnLCDCoordenadas (0, 2); /*Y = 0, X= 2*/ 
	vfnLCDEnviarPalabra((int8_t *)gbaPalabraAEnviar, (sizeof(gbaPalabraAEnviar) - 1U)); /*Se escribe la palabra temperatura en la linea superior, centrado, en el LCD. Se manda el apuntador al arreglo y el tamaño del mismo )(-1 para no contar nulo)*/
	
	vfnLCDCoordenadas (1, 8); /*Y = 1, X = 8*/
	vfnLCDComandoOCaracter(1, DEGREE_SYMBOL); 
	vfnLCDComandoOCaracter(1, 'C');

	for(;;) 
	{	 

		if(gbPitCounterADC >= 2) /*ADC, se requiere una muestra cada 200ms*/
		{

			gbValorLeido = bfnADCLectura(bChannel); /*Se obtiene el resultado de una conversión ADC*/

			gdwAcumuladorADC = gdwAcumuladorADC + gbValorLeido; /*Se almacena cada resultado en el acumulador*/

			gbIndexADC++;

			if(gbIndexADC == MUESTRAS) /*Cuando se hayan tomado 10 muestras*/
			{
				gwPromediado = (gdwAcumuladorADC / MUESTRAS); /*Se toma un promedio*/
				gbIndexADC = 0;
				gdwAcumuladorADC = 0;
				gwConversion =  ((gwPromediado)*330)/256;/*Se ajusta el valor al real*/

				gwUnidades = (vfnBCD(gwConversion) & CLEAR_ALL_BUT_UNITS); 
				gwDecenas = ((vfnBCD(gwConversion)  & CLEAR_ALL_BUT_TENS) >> 4);
				gwCentenas = ((vfnBCD(gwConversion)  & CLEAR_ALL_BUT_HUNDREDS) >> 8);
				
				
				if(gwCentenas != 0) /*Se escriben centenas, decenas y unidades uno por uno*/
				{
					vfnLCDCoordenadas (1, 5); /*Y = 1, X = 5, para escribir desde ahí las centenas*/
					vfnLCDComandoOCaracter(1, gwCentenas + 48); /*Se le agrega 48 para mandarlo en ASCII*/
				}
				

				if(gwDecenas != 0 || gwCentenas != 0) /*Si existen decenas o si existen centenas*/
				{
					vfnLCDCoordenadas (1, 6); /*Y = 1, X = 6 para escribir desde ahí las decenas*/
					vfnLCDComandoOCaracter(1, gwDecenas + 48);
				}
				vfnLCDCoordenadas (1, 7); /*Y = 1, X = 6 para escribir desde ahí las unidades*/
				vfnLCDComandoOCaracter(1, gwUnidades + 48);

			}

			gbPitCounterADC = 0;

		}

		if(gbPitCounterLED >= 10) /*LED, se requiere mandar un pulso cada segundo*/
		{
			BLUE_LED_TOGGLE; /*Se togglea el LED azul*/

			gbPitCounterLED = 0;
		}
	}				
	return 0;
}

void vfnPitCallback(void)
{
	gbPitCounterADC++;
	gbPitCounterLED++;
}



