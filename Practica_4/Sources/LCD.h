/*
 * LCD.h
 *
 *  Created on: Jul 30, 2017
 *      Author: Windows 8.1
 */

#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>

#define ENABLE_ON     GPIOB_PDOR |= 1 
#define ENABLE_OFF    GPIOB_PDOR &= ~(1)
#define REGISTER_SELECT_ON    GPIOB_PDOR |= (1 << 1)
#define REGISTER_SELECT_OFF  GPIOB_PDOR &= ~(1 << 1)
#define DATA_CLEAR   (GPIOC_PDOR = 0 )
#define DISPLAY_ON   (0x0F)
#define CLEAR_DISPLAY    (0x01)
#define EIGHT_BIT_TWO_LINES    (0x38)
#define SHIFT_RIGHT   (0x14)
#define SHIFT_LEFT   (0x10)
#define COMIENZO_PRIMERA_LINEA (0x80)
#define SALTO_DE_LINEA (0xC0)
#define DELAY (3000)

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus
void vfnLCDInit (void);

void vfnLCDComandoOCaracter(uint8_t bEnableOrRS, uint8_t bCommandOrCharacter); /*Comando = 0 Dato = 1*/

void vfnLCDEnviarPalabra(int8_t *bpPalabra, uint8_t bDataSize); /*Para mandar toda una palabra utilizando la función de comandos*/

void vfnLCDCoordenadas(uint8_t bLinea, uint8_t bOffset);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif /* LCD_H_ */
