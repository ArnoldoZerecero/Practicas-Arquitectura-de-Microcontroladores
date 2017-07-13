#include "derivative.h"/* include peripheral declarations */
#include "stdint.h" /*Include para los tipos de datos*/

void fnQsort (uint8_t *, uint8_t); /*Se declara la función que recibirá un apuntador y un número de 8 bits, y que no regresará parámetros*/

int main(void) /*Comienza main*/
{
	const uint8_t bNumeroDeElementos = 5; /*Variable que indica cuántos elementos tendrá el arreglo*/
	uint8_t baArregloAOrdenar[bNumeroDeElementos]; /*Arreglo con elementos a ordenar de menor a mayor*/
	uint8_t *bApuntadorArreglo; /*Apuntador para el arreglo*/
	
	baArregloAOrdenar[0] = 5; 	/*Inicialización de valores de cada elemento del arreglo.*/
	baArregloAOrdenar[1] = 3; 
	baArregloAOrdenar[2] = 4; 
	baArregloAOrdenar[3] = 1; 
	baArregloAOrdenar[4] = 2; 
	bApuntadorArreglo = &baArregloAOrdenar[0]; /*El apuntador para el arreglo comenzará apuntando a su primera posición*/
	
	fnQsort(bApuntadorArreglo, bNumeroDeElementos); /*Se llama la función y se le pasan los dos parámetros*/
	
	return 0;
}

/*Fin de main*/

void fnQsort (uint8_t *bApuntadorArreglo, uint8_t bNumeroDeElementos) /*Comienza la función*/ 
{
	static uint8_t bIndice = 0; /*Se crea una variable para el índice y se inicia en cero*/
	static uint8_t *bApuntadorSiguienteElemento; /*Se declara un nuevo apuntador que comparará los siguientes elementos con el apuntador base actual (bApuntadorArreglo)*/
	static uint8_t bTemporal; /*Se crea una variable temporal para evitar pérdida de datos*/
	static uint8_t bOffset = 1; /*Esta variable determina cuántas veces le falta por recorrerse el *bApuntadorSiguienteElemento para llegar al final del arreglo. Se inicializa en uno debido a que el *bApuntadorSiguienteElemento comienza en la posición [1] del arreglo*/

	do /*Comienza el primer ciclo*/
	{
		bApuntadorSiguienteElemento = bApuntadorArreglo + 1; /*El apuntador para el siguiente elemento siempre comienza uno por delante del apuntador base*/
			do /*Comienza el segundo ciclo*/
			{
				if (*bApuntadorArreglo > *bApuntadorSiguienteElemento) /*En caso de que sea mayor el valor base (de la izquierda), se intercambia con el de la derecha*/
				{
					bTemporal = *bApuntadorSiguienteElemento; /*Se guarda el elemento al que apunta el *bApuntadorSiguienteElemento en bTemporal para no perderlo*/
					*bApuntadorSiguienteElemento = *bApuntadorArreglo; /**bApuntadorSiguienteElemento adquiere el valor del elemento al que apunta *bApuntadorArreglo*/
					*bApuntadorArreglo = bTemporal; /*El apuntador base adquiere el valor en el que estaba el *bApuntadorSiguienteElemento, el cual se guardó en bTemporal*/
				}
				else /*En caso de que el elemento de la izquierda sea menor, quiere decir que se encuentra en orden, y ninguna acción ocurre*/
				{
				}
				bApuntadorSiguienteElemento++; /*Se incrementa en uno el bApuntadorSiguienteElemento para apuntar a la siguiente posición de la cadena*/
				bIndice++; /*Se incrementa en uno el índice*/
			}
			while ((bIndice != (bNumeroDeElementos - bOffset)) && bNumeroDeElementos != 1); /*El ciclo interno continuará hasta que se haya recorrido bApuntadorSiguienteElemento hasta el último elemento. En caso de que el arreglo contenga un único elemento, el ciclo también finalizará*/
		bIndice = 0; /*El índice se reinicia a 0 antes de volver a comenzar el ciclo*/
		bApuntadorArreglo++; /*El apuntador base se recorre al siguiente elemento, lo que significa que el elemento en el que estaba ya quedó ordenado*/
		bOffset++; /*El bOffset se incrementa en uno, lo cual indica que en el próximo ciclo, el bApuntadorSiguienteElemento tedrá que recorrerse una vez menos para llegar al final del arreglo*/
	}while(bOffset != bNumeroDeElementos && bNumeroDeElementos != 1); /*El ciclo principal termina cuando el bOffset se incrementa hasta ser igual al número de elementos, lo cual significa que el apuntador base (bApuntadorArreglo) ya ha pasado por todos los elementos.  En caso de que el arreglo contenga un único elemento, el ciclo también finalizará*/
return; /*Se regresa a main sin retornar parámetros*/
}
