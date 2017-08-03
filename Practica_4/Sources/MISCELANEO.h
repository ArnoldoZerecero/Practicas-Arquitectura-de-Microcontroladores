/*
 * MISCELANEO.h
 *
 *  Created on: Aug 2, 2017
 *      Author: Alumnos
 */

#ifndef MISCELANEO_H_
#define MISCELANEO_H_

#include <stdint.h>

#define DELAY_TIME 3000

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

uint16_t vfnBCD(uint16_t wResultado);


void vfnDelay (uint32_t dwDelay);

#if defined(__cplusplus)
}
#endif // __cplusplus


#endif /* MISCELANEO_H_ */
