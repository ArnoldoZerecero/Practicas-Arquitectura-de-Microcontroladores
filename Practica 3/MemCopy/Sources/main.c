#include "derivative.h" /* include peripheral declarations */
#include "stdint.h" /*Include para los tipos de datos*/

void fnMemCopy (uint8_t *, uint8_t *, uint8_t); /*Se declara la función que recibirá dos apuntadores y un número de 8 bits, y que no regresará parámetros*/

int main(void) /*Comienza main*/
{
	const uint8_t bNumeroDeElementos = 8; /*Variable que indica cuántos elementos tendrán ambos arreglos*/
	uint8_t baArregloFuente[bNumeroDeElementos]; /*Arreglo que contiene los elementos a pasar al arreglo destino*/
	uint8_t baArregloDestino[bNumeroDeElementos]; /*Arreglo no inicializado en donde se copiarán los elementos del arreglo fuente*/
	uint8_t *bApuntadorFuente; /*Apuntador para el arreglo fuente*/
	uint8_t *bApuntadorDestino; /*Apuntador para el arreglo destino*/
	
	baArregloFuente[0] = 1; 	/*Inicialización de valores de cada elemento del arreglo fuente.*/
	baArregloFuente[1] = 2;
	baArregloFuente[2] = 3;
	baArregloFuente[3] = 4;
	baArregloFuente[4] = 5;
	baArregloFuente[5] = 6;
	baArregloFuente[6] = 7;
	baArregloFuente[7] = 8;
	bApuntadorFuente = &baArregloFuente[0]; /*El apuntador para el arreglo fuente comenzará apuntando a su primera posición*/
	bApuntadorDestino = &baArregloDestino[0]; /*El apuntador para el arreglo destino comenzará apuntando a su primera posición*/
	
	fnMemCopy(bApuntadorDestino, bApuntadorFuente, bNumeroDeElementos); /*Se llama la función y se le pasan los tres parámetros*/
	
	return 0;
}

/*Fin de main*/

void fnMemCopy (uint8_t *bApuntadorDestino, uint8_t *bApuntadorFuente, uint8_t bNumeroDeElementos) /*Comienza la función*/ 
{
	static uint8_t bIndice = 0; /*Se crea una variable para el índice y se inicia en cero*/
	do /*Comienza el ciclo*/
	{
		*bApuntadorDestino = *bApuntadorFuente; /*El valor a donde apunta el apuntador destino es reemplazado por el valor al cual apunta el apuntador fuente*/
		bApuntadorDestino++; /*Se incrementa en uno la dirección de ambos apuntadores, para apuntar hacia el siguiente elemento de los arreglos*/
		bApuntadorFuente++;
		bIndice++; /*Se incrementa en uno el índice*/
	}
	while (bIndice != bNumeroDeElementos); /*El ciclo continuará hasta que se hayan recorrido todos los elementos de ambos arreglos, es decir, hasta que el índice alcance el valor del número de elementos especificado*/
return;
}


