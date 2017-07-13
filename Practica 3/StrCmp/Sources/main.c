#include "derivative.h" /* include peripheral declarations */
#include "stdint.h" /*Include para los tipos de datos*/

uint8_t bfnStrcmp (int8_t *, int8_t *); /*Se declara la función que recibirá dos apuntadores y regresará un valor de 8 bits*/

int main(void) /*Comienza main*/
{
	int8_t *bApuntadorCadena1 = "Hola"; /*Se inicializan los contenidos de ambas cadenas y se crea un apuntador que apunta hacia su dirección*/
	int8_t *bApuntadorCadena2 = "Ho";
	
	
	uint8_t bResultado = bfnStrcmp(bApuntadorCadena1, bApuntadorCadena2); /*Se llama la función y se le pasan los dos parámetros. Lo que la función regrese se guardará en bResultado*/
	bResultado = bResultado;
	return 0;
}

/*Fin de main*/

uint8_t bfnStrcmp (int8_t *bApuntadorCadena1, int8_t *bApuntadorCadena2) /*Comienza la función*/ 
{
	do /*Comienza el ciclo*/
	{
		if (*bApuntadorCadena1 != *bApuntadorCadena2) /*En caso de que el contenido de los apuntadores sea diferente, la función regresa un 1*/
		{
			return 1;
		}
		else /*En caso de que sean iguales, la dirección a la cual apuntan se incrementa en uno para recorrerse por las cadenas*/
		{
			bApuntadorCadena1++;
			bApuntadorCadena2++;
		}
	}while ((*bApuntadorCadena1 + *bApuntadorCadena2) != 0); /*Si el ciclo termina debido a que se alcanzó el nulo al mismo tiempo en ambas cadenas, la función regresa un cero*/
return 0;
}



