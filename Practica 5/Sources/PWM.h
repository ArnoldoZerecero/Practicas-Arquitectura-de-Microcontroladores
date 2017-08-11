/*
 * PWM.h
 *
 *  Created on: Aug 7, 2017
 *      Author: Alumnos
 */

#ifndef PWM_H_
#define PWM_H_
#include <stdint.h>

#define PERIODO (175350) /*60 Hz, o 16.7ms*/

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus
void vfnPWMLedInit(void);

void vfnPWMLedDutyCycle(uint8_t bRGB, uint32_t dwDutyCycle);


#if defined(__cplusplus)
}
#endif // __cplusplus

#endif /* PWM_H_ */
