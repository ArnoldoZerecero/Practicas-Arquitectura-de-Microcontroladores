/*
 * PWM.h
 *
 *  Created on: Aug 7, 2017
 *      Author: Alumnos
 */

#ifndef PWM_H_
#define PWM_H_
#include <stdint.h>

#define PERIODO (20) /*A menor periodo, mayor velocidad de giro*/

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus
void vfnPWMInit(void);

void vfnPWMMotores(uint8_t bDireccion);

void vfnPWMTren(void);

void vfnPWMRotacion(void);

void vfnPWMAltura(void);

void vfnPWMLedInit(void);

void vfnPWMLedDutyCycle(uint8_t bRGB, uint32_t dwDutyCycle);


#if defined(__cplusplus)
}
#endif // __cplusplus

#endif /* PWM_H_ */
