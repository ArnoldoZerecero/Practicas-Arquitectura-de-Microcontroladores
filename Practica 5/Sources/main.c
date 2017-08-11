#include <stdint.h>
#include <string.h>
#include "derivative.h"
#include "UART.h"
#include "ADC.h"
#include "shell.h"
#include "PWM.h"
#include "MISCELANEO.h"


#define BAUD_RATE (7) /*SBR = Baud Clock / ((OSR+1)*Baud Rate Deseado)*/ /*Si Baud Clock = 20.97Mhz y Baud Rate Deseado = 115200, SBR = 7*/

#define OSR (25) /*Over Sampling Ratio*/

#define COMMAND_NUMBER (10) /*Numero de comandos de la estructura*/

typedef struct /*Typedef para el arreglo de estructuras (una estructura por comando y su respectiva función)*/
{
	int8_t bpComando[20];
	void (*vfnLeerComando)(int8_t * bpParametro1, int8_t * bpParametro2);
}Comandos_t;

void vfnReadCommand(void);

ADCConfigInit_t InitAdcParameters = /*Inicializamos los valores de la estructura*/
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


UartConfigInit_t InitUartParameters = /*Inicializamos los valores de la estructura*/
{
	0, /*Solo 1 stop bit*/
	BAUD_RATE, /*7*/
	0, /*0 = 8 bits de longitud, 1 = 9 bits de longitud*/ 
	0, /*0 = paridad desactivada, 1 = paridad activada*/
	0, /*0 = paridad par, 1 = paridad impar*/
	OSR, /*25*/
	&vfnUARTCallback /*Apuntador a función Callback*/
};

int8_t gbaComando[20]; /*Arreglo para leer el comando con la función Callback*/

int8_t gbaParametro1[20]; /*Primer parámetro del comando*/

int8_t gbaParametro2[20]; /*Segundo parámetro del comando*/

static int8_t gbIndex = 0; /*Indice para recorrer el arreglo de estructuras*/

static uint8_t gbIndexComando = 0; /*Índices para leer el comando y sus parámetros*/

static uint8_t gbIndexParametro1 = 0;

static uint8_t gbIndexParametro2 = 0;

static uint8_t gbParametro1Enable = 0;

static uint8_t gbParametro2Enable = 0;

volatile uint8_t gbCharacterReceivedFlag = 0; /*Índice para cuando se tecleó algo en la terminal*/

volatile uint8_t gbNewCharacterReceived; /*Variable para guardar el caracter tecleado en la terminal*/

static uint8_t gbPitFinished  = 0; /*Indice para saber cuando el PIT haya finalizado su conteo*/

static uint16_t gwVoltaje; /*Variable para el voltaje del pot*/

static uint16_t gwBCD; /*Variable para el BCD del voltaje del pot*/

static uint16_t gwCentenas; /*Variable para las centenas del voltaje del pot*/

static uint16_t gwDecenas; /*Variable para las decenas del voltaje del pot*/

static uint16_t gwUnidades; /*Variable para las unidades del voltaje del pot*/


const Comandos_t saTabla[COMMAND_NUMBER] =  /*Arreglo de estructuras*/
{
		{
				"rgb", /*Comando para el rgb*/
				&vfnRGBPWMColorSet
		},
		{
				"led", /*Comando para el led*/
				&vfnPWMLEDOnOffToggle
		},
		{
				"cls",/*Comando para el limpiar pantalla*/
				&vfnClearScreen
		},
		{
				"print", /*Comando para imprimir el texto de la terminal*/
				&vfnPrintScreen
		},
		{
				"color", /*Comando para cambiar el color del texto de la terminal*/
				&vfnColorFuente
		},
		{
				"pot", /*Comando para comenzar o detener el registro del potenciómetro*/
				&vfnPeriodidPotRead
		},
		{
				"help", /*Comando para mostrar la lista de comandos*/
				&vfnCommandList
		},
		{
				"temperatura", /*Comando para mostrar la temperatura actual que da el LM35*/
				&vfnLM35Read
		},
		{
				"ledexterno", /*Comando para encender o apagar el led externo*/
				&vfnLED
		},
		{
				"buzzer", /*Comando para encender o apagar el buzzer externo*/
				&vfnBuzzer
		},
};
 
static const uint8_t gbaPalabraComando[11] = /*Lo que vamos a mandar antes de cada comando*/
{
		"\r\nComando>"
}; 


int main(void)
{	
	vfnPWMLedInit(); /*Inicialización del PWM para los LEDs*/

	vfnUartInit(&InitUartParameters); /*Inicialización del UART*/

	vfnADCInit(&InitAdcParameters); /*Inicialización del ADC para pot y LM35*/

	vfnGPIOInit(); /*Inicialización del GPIO para LED y buzzer externo*/

	vfnUartTransmision((uint8_t *)&gbaPalabraComando[0], (sizeof(gbaPalabraComando) - 1U)); /*Se escribe "Comando>"*/

	for(;;)
	{
		if(gbCharacterReceivedFlag) /*Si se recibió un caracter*/
		{
			gbCharacterReceivedFlag = 0; /*Se reinicia bandera*/
			if (gbNewCharacterReceived == '\r')  /*Cuando se mande un enter*/
			{
				vfnReadCommand();
				
				vfnUartTransmision((uint8_t *)&gbaPalabraComando[0], (sizeof(gbaPalabraComando) - 1U)); /*Se escribe "Comando>*/

				gbIndexComando = 0; /*Se reinician los indices e enables*/
				gbIndexParametro1 = 0;
				gbIndexParametro2 = 0;
				
				gbParametro1Enable = 0;
				gbParametro2Enable = 0;
				
				memset(gbaComando,0,sizeof(gbaComando)); /*Se limpian arreglos*/ 
				memset(gbaParametro1,0,sizeof(gbaParametro1));
				memset(gbaParametro2,0,sizeof(gbaParametro2));
			}
			else if (gbNewCharacterReceived == ' ')  /*Cuando se mande un espacio*/
			{
				if (gbParametro1Enable) /*Si se estaba escribiendo en el primer parámetro, ahora se escribirá en el segundo*/
				{
					gbParametro2Enable = 1;
					gbParametro1Enable = 0;
				}
				else if (!gbParametro2Enable) /*Si no se estaba escribiendo en ningún parámetro*/
				{
					gbParametro1Enable = 1;
				}
				vfnUartTransmision((uint8_t *)&gbNewCharacterReceived, 1);  /*Se manda el eco de los caracteres que se están escribiendo en la terminal*/
			}
			else if (gbParametro1Enable) /*Se escribe en el arreglo del primer parámetro*/
			{
				gbaParametro1[gbIndexParametro1] = gbNewCharacterReceived;
				gbIndexParametro1++; /*Se incrementa el índice*/
				vfnUartTransmision((uint8_t *)&gbNewCharacterReceived, 1);  /*Se manda el eco de los caracteres que se están escribiendo en la terminal*/			}
			else if (gbParametro2Enable) /*Se escribe en el arreglo del segundo parámetro*/
			{
				gbaParametro2[gbIndexParametro2] = gbNewCharacterReceived;
				gbIndexParametro2++; /*Se incrementa el índice*/
				vfnUartTransmision((uint8_t *)&gbNewCharacterReceived, 1);  /*Se manda el eco de los caracteres que se están escribiendo en la terminal*/			}
			else /*Se escribe en el arreglo del comando*/
			{
				gbaComando[gbIndexComando] = gbNewCharacterReceived; /*Se escribe el dato que llegó en un Buffer para poder leerlo*/
				gbIndexComando++; /*Se incrementa el índice*/
				vfnUartTransmision((uint8_t *)&gbNewCharacterReceived, 1);  /*Se manda el eco de los caracteres que se están escribiendo en la terminal*/			}
		}
		if(gbPitFinished) /*Cuando el conteo del pit para el pot haya finalizado*/
		{
			gwVoltaje = (bfnADCLectura(0)*330/256); /*Se adquiere el valor del ADC y se convierte a unidades de voltaje*/
			gwBCD = wfnBCD(gwVoltaje); /*Se debe mandar caracter por caracter, por lo que el valor se convierte a BCD*/
			gwCentenas = ((gwBCD & CLEAR_ALL_BUT_HUNDREDS) >> 8) + 48; /*Se dejan solo las centenas y se convierte a ASCII*/
			gwDecenas = ((gwBCD & CLEAR_ALL_BUT_TENS) >> 4) + 48; /*Se dejan solo las decenas y se convierte a ASCII*/
			gwUnidades = ((gwBCD & CLEAR_ALL_BUT_UNITS)) + 48; /*Se dejan solo las unidades y se convierte a ASCII*/
			
			uint8_t gbaValorPot[6]= /*Se imprimirá el valor del pot en la terminal en el mismo lugar continuamente*/
			{			
					gwCentenas, gwDecenas, gwUnidades, BACKSPACE_CARACTER, BACKSPACE_CARACTER, BACKSPACE_CARACTER 
			};
						
			gbPitFinished = 0; /*Se reinicia bandera*/
			vfnUartTransmision((uint8_t *)&gbaValorPot[0], (sizeof(gbaValorPot)));/*Se escribe el valor del pot en la terminal*/
		}
	}
	return 0;
}


void vfnReadCommand(void) /*Ciclo de lectura de comandos*/
{
	do
	{
		if(!(strcmp((char *)gbaComando,(char *)saTabla[gbIndex].bpComando))) /*Se compara con cada comando del arreglo de estrucutras*/
		{
			saTabla[gbIndex].vfnLeerComando(gbaParametro1, gbaParametro2); /*Cuando se encuentre, se llama la función de esa estructura y se le mandan los parámetros*/
			gbIndex = 0;
			return;
		}
		gbIndex++;
	}while(gbIndex != COMMAND_NUMBER); /*Si se llegó al fin y no se encontró un comando correspondiente*/
	
	vfnMensajeError(); /*Se escribe en la terminal mensaje de error*/
	
	gbIndex = 0;
}


void vfnUARTCallback(uint8_t bDatosReceptor)
{
	gbNewCharacterReceived = bDatosReceptor;
	gbCharacterReceivedFlag = 1;
}

void vfnPitCallback(void) /*Cada que el periodo de ms termine, se imprime la medición del pot desde el ADC*/
{
	gbPitFinished = 1;
}


	
