/*
 * shell.h
 *
 *  Created on: Aug 7, 2017
 *      Author: Alumnos
 */

#ifndef SHELL_H_
#define SHELL_H_

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

void vfnClearScreen(int8_t * bpParametro1, int8_t * bpParametro2);

void vfnPeriodidPotRead(int8_t * bpStartStop, int8_t * bpPeriodo);

void vfnPrintScreen(int8_t * bpParametro1, int8_t * bpParametro2);

void vfnColorFuente(int8_t * bpColor, int8_t * bpParametro2);

void vfnCommandList(int8_t * bpParametro1, int8_t * bpParametro2);

void vfnLM35Read(int8_t * bpParametro1, int8_t * bpParametro2);

void vfnMensajeError(void);

void vfnRGBPWMColorSet(int8_t * bpColor, int8_t * bpParametro2);

void vfnPWMLEDOnOffToggle(int8_t * bpColor, int8_t *bpAccion);

#if defined(__cplusplus)
}

#endif // __cplusplus

#endif /* SHELL_H_ */
