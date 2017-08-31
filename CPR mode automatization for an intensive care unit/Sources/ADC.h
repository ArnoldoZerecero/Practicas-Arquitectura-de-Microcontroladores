/*
 * ADC.h
 *
 *  Created on: Jul 29, 2017
 *      Author: Windows 8.1
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

#define DIVIDE_RATIO 3
#define MUESTRAS_PROMEDIADAS 0
#define OFFSET 0
#define MUESTRAS 20 /*Número de muestras deseadas por conversión*/

typedef void(* ADCUserCallback_t)(uint8_t); /*Función de Callback, para la cual se creará un apuntador*/

typedef struct /*Parámetros para la función de inicialización*/
{
	uint8_t bClkDivision; 
	uint8_t bSampleTime; 
	uint8_t bResolucion;
	uint8_t bLongSampleTime;
	uint8_t bConversionesContinuas;
	uint8_t bEnablePromediado;
	uint8_t bMuestrasPromediadas;
	uint16_t wOffset;
}ADCConfigInit_t;

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus
void vfnADCInit (ADCConfigInit_t * pADCUserConfig);

void vfnADCCalibration(void);

uint16_t wfnADCLectura(uint8_t bChannelToUse);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif /* ADC_H_ */
