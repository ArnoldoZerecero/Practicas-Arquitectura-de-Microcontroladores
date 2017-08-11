/*
 * PWM.c
 *
 *  Created on: Aug 7, 2017
 *      Author: Alumnos
 */
#include "PWM.h"
#include "derivative.h"
#include <stdint.h>

void vfnPWMLedInit(void)
{
	SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK; /*Se activa clk para TPM0*/
	SIM_SCGC6 |= SIM_SCGC6_TPM2_MASK; /*Se activa clk para TPM2*/
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1); /*Selecciono MCGFLLCLK*/

	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK; /*Se activa clk para puerto D*/
	PORTD_PCR1 = PORT_PCR_MUX(4); /*Se activa el PTD1 como TPM0_CH1 (para led azul)*/

	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK; /*Se activa clk para puerto B*/
	PORTB_PCR18 = PORT_PCR_MUX(3); /*Se activa el PTB18 como TPM2_CH0 (para led rojo)*/
	PORTB_PCR19 = PORT_PCR_MUX(3); /*Se activa el PTB19 como TPM2_CH1 (para led verde)*/

	TPM0_SC |= TPM_SC_CPWMS_MASK; /*Contador en modo center-alligned PWM para TPM0*/
	TPM2_SC |= TPM_SC_CPWMS_MASK; /*Contador en modo center-alligned PWM para TPM2*/
	TPM0_SC |= TPM_SC_PS(3); /*Clk del contador del TPM0 dividido sobre 8*/
	TPM2_SC |= TPM_SC_PS(3); /*Clk del contador del TPM2 dividido sobre 8*/

	TPM0_C1SC |= TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK; /*High true pulses para modo center-alligned PWM para el TPM0_CH1*/ 

	TPM2_C0SC |= TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK; /*High true pulses para modo center-alligned PWM para el TPM2_CH0*/ 

	TPM2_C1SC |= TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK; /*High true pulses para modo center-alligned PWM para el TPM2_CH1*/ 

	TPM0_MOD = PERIODO; /*Periodo para TPM0*/
	TPM2_MOD = PERIODO; /*Periodo para TPM2*/

	TPM0_SC |= TPM_SC_CMOD(1); /*Counter start para TPM0*/
	TPM2_SC |= TPM_SC_CMOD(1); /*Counter start para TPM2*/
}
/*En modo CPWM, el TPM cuenta hacia arriba hasta que es igual a MOD. Luego, cuenta hacia abajo hasta que vuelva a ser cero. Al contar hacia arriba, el output es
 * 1 cuando el contador = CnV. El output es 0 al contar hacia abajo cuando contador = CnV.
 */



void vfnPWMLedDutyCycle(uint8_t bRGB, uint32_t dwDutyCycle)
{
	if (bRGB == 0)/*Si se desea modular el led azul*/
	{
		TPM0_C1V = dwDutyCycle; /*Pulse width para el TPM0_CH1 (led azul). Para center alligned pwm, Duty cycle = CnV*2*/
	}
	else if (bRGB == 1)/*Si se desea modular el led rojo*/
	{
		TPM2_C0V = dwDutyCycle; /*Pulse width para el TPM2_CH0 (led rojo). Para center alligned pwm, Duty cycle = CnV*2*/
	}
	else if (bRGB == 2)/*Si se desea modular el led verde*/
	{
		TPM2_C1V = dwDutyCycle; /*Pulse width para el TPM2_CH1 (led verde). Para center alligned pwm, Duty cycle = CnV*2*/
	}

}
