/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                      Includes Section
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "derivative.h" 
#include "ADC.h"
#include "PWM.h"
#include "PIT.h"
#include "MISCELANEO.h"
#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Defines & Macros Section
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                       Typedef Section
///////////////////////////////////////////////////////////////////////////////////////////////////
ADCConfigInit_t InitAdcParameters = /*Inicializamos los valores de la estructura*/
{
		DIVIDE_RATIO, /*Se utilizará (bus clk)/8*/ 
		1, /*Tiempo de muestreo largo*/
		2, /*Resolución de 10 bits*/
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

void vfnBuzzerPulse(void);

void vfnBuzzerAlarm(void);

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Global Constants Section
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Static Constants Section
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Global Variables Section
///////////////////////////////////////////////////////////////////////////////////////////////////
static volatile uint8_t gbPitCounterADC = 0; /*Contador para el timer del pit para ADC*/

static volatile uint16_t gwPitCounterNoPulse = 0; /*Contador para el timer del pit para contar el tiempo sin detectar un pulso*/

static volatile uint8_t gbPitCounterBeep = 0; /*Contador para el timer del pit para mantener el buzzer encendido durante cierto tiempo*/

static volatile uint16_t gwCounterTrenParo = 0; /*Contador para poner el modo tren hacia abajo hasta su tope*/

static volatile uint16_t gwCounterAlturaParo = 0; /*Contador para poner el modo altura hacia abajo hasta su tope*/

static uint16_t gwValorLeido; /*Valor leído desde el registro de resultado del ADC*/

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Static Variables Section
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
//                                      Functions Section
///////////////////////////////////////////////////////////////////////////////////////////////////

int main(void)
                                                                                                                                        {
	vfnPitInit(TARGET_TIME_20MS,&vfnPitCallback); /*Inicialización del PIT*/

	vfnPitStart(); /*Comienza el contador del PIT*/

	vfnADCInit(&InitAdcParameters); /*Inicialización del ADC*/
	
	vfnPWMInit(); /*Inicialización del modulo PWM*/
	
	vfnGPIOInit(); /*Inicialización del GPIO para buzzer externo*/
	
	for(;;) 
	{
		if(gbPitCounterADC) /*Cada 20ms se tomará una muestra de ADC*/
		{
			gwValorLeido = wfnADCLectura(0); /*Se obtiene el resultado de una conversión ADC, desde el canal DADP0*/
		}
		if(gwValorLeido > 650 && gwValorLeido < 700) /*Si se detectó un pulso*/
		{
			vfnBuzzerPulse();
			gwPitCounterNoPulse = 0; /*Se reinicia el cronómetro de no detección de pulso*/
			gwCounterTrenParo = 0; /*Se reinician los índices de activación de modo de paro para permitir que se vuelva a caer en modo de paro*/
			gwCounterAlturaParo = 0;
		}
		if(gwPitCounterNoPulse >= 500) /*Si ya transcurrieron 10 segundos sin pulso*/
		{
			vfnBuzzerAlarm(); /*Se activa la alarma*/
			/*Se abate la cama al colocar el modo tren paralelo al suelo y se eleva al paciente al máximo para facilitar CPR*/
			if(gwCounterTrenParo < 800)
			{
				vfnPWMTren(); /*Se pone el select para mandar la señal al motor del tren por medio del demultiplexor*/
				vfnPWMMotores(0); /*Motor clockwise*/
				gwCounterTrenParo++;
			}
			if(gwCounterAlturaParo < 800 && gwCounterTrenParo == 800)
			{
				vfnPWMAltura(); /*Se pone el select para mandar la señal al motor del tren por medio del demultiplexor*/
				vfnPWMMotores(0); /*Motor clockwise*/
				gwCounterAlturaParo++;
			}
		}
		else if (GPIOC_PDIR == 1) /*Si se presiona el modo tren hacia abajo*/
		{
				vfnPWMTren(); /*Se pone el select para mandar la señal al motor del tren por medio del demultiplexor*/
				vfnPWMMotores(0); /*Motor clockwise*/
		}
		else if (GPIOC_PDIR == 2) /*Si se presiona el modo tren hacia arriba*/
		{
				vfnPWMTren();/*Se pone el select para mandar la señal al motor del tren por medio del demultiplexor*/
				vfnPWMMotores(1);/*Motor counterclockwise*/
		}
		else if(GPIOC_PDIR == 4) /*Si se presiona el modo rotacion hacia la izquierda*/
		{
				vfnPWMRotacion();/*Se pone el select para mandar la señal al motor de rotación por medio del demultiplexor*/
				vfnPWMMotores(0);/*Motor clockwise*/
		}
		else if (GPIOC_PDIR == 8) /*Si se presiona el modo rotacion hacia la derecha*/
		{
				vfnPWMRotacion(); /*Se pone el select para mandar la señal al motor de rotación por medio del demultiplexor*/
				vfnPWMMotores(1);/*Motor counterclockwise*/
		}
		else if(GPIOC_PDIR == 32) /*Si se presiona el modo altura hacia arriba*/
		{
				vfnPWMAltura();/*Se pone el select para mandar la señal al motor de altura por medio del demultiplexor*/
				vfnPWMMotores(1);/*Motor counterclockwise*/
		}
		else if (GPIOC_PDIR == 16) /*Si se presiona el modo altura hacia abajo*/
		{
				vfnPWMAltura();/*Se pone el select para mandar la señal al motor de altura por medio del demultiplexor*/
				vfnPWMMotores(0);/*Motor clockwise*/
		}
	}
	
	return 0;
}

void vfnBuzzerPulse(void)
{
	gbPitCounterBeep = 0; /*El contador comienza en cero*/
	
	while(gbPitCounterBeep < 2)/*Se enciende el buzzer durante 40MS*/
	{
		GPIOB_PDOR |= 2; 
	}
	gbPitCounterBeep = 0;
	
	while(gbPitCounterBeep < 1)
	{
		GPIOB_PDOR &= ~2; /*Y luego se apaga*/
	}
}

void vfnBuzzerAlarm(void)
{
	GPIOB_PDOR |= 2; /*Se mantiene constantemente activado el buzzer*/
}

void vfnPitCallback(void)
{
	gbPitCounterADC++;
	gwPitCounterNoPulse++;
	gbPitCounterBeep++;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////////////////////////////////////

