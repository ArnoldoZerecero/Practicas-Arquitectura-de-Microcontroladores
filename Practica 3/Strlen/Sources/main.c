#include "derivative.h" /* include peripheral declarations */
#include "stdint.h" /*Include para los tipos de datos*/

uint8_t bfnStrlen (int8_t *); /*Se declara la funci�n que recibir� un apuntador y regresar� un valor de 8 bits*/

int main(void) /*Comienza main*/
{
	int8_t baCadenaAMedir[] = "Microcontroladores"; /*Se inicializa el contenido de la cadena y se crea un apuntador que apunta hacia su primer elemento*/
	int8_t *bApuntadorCadena;
	bApuntadorCadena= &baCadenaAMedir[0];
	
	uint8_t bLongitud = bfnStrlen(bApuntadorCadena); /*Se llama la funci�n y se le pasa el par�metro. Lo que la funci�n regrese se guardar� en bLongitud*/
	bLongitud = bLongitud;
	return 0;
}

/*Fin de main*/

uint8_t bfnStrlen (int8_t *bApuntadorCadena) /*Comienza la funci�n*/ 
{
	static uint8_t bAcumulador = 0; /*Se declara una variable para llevar el conteo del n�mero de caracteres*/
	do /*Comienza el ciclo*/
	{
		bAcumulador++; /*Se incrementa en uno el acumulador*/
		bApuntadorCadena++; /*Se incrementa en uno la direcci�n a la cual apunta el apuntador para que se recorra a trav�s de la cadena*/
	}while (*bApuntadorCadena != 0); /*El ciclo termina cuando el apuntador llegue al nulo*/
return bAcumulador; /*Se regresa el valor de bAcumulador a main*/
}



