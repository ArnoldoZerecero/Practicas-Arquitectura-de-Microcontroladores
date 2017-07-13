#include "derivative.h"/* include peripheral declarations */
#include "stdint.h" /*Include para los tipos de datos*/

void fnQsort (uint8_t *, uint8_t); /*Se declara la funci�n que recibir� un apuntador y un n�mero de 8 bits, y que no regresar� par�metros*/

int main(void) /*Comienza main*/
{
	const uint8_t bNumeroDeElementos = 5; /*Variable que indica cu�ntos elementos tendr� el arreglo*/
	uint8_t baArregloAOrdenar[bNumeroDeElementos]; /*Arreglo con elementos a ordenar de menor a mayor*/
	uint8_t *bApuntadorArreglo; /*Apuntador para el arreglo*/
	
	baArregloAOrdenar[0] = 5; 	/*Inicializaci�n de valores de cada elemento del arreglo.*/
	baArregloAOrdenar[1] = 3; 
	baArregloAOrdenar[2] = 4; 
	baArregloAOrdenar[3] = 1; 
	baArregloAOrdenar[4] = 2; 
	bApuntadorArreglo = &baArregloAOrdenar[0]; /*El apuntador para el arreglo comenzar� apuntando a su primera posici�n*/
	
	fnQsort(bApuntadorArreglo, bNumeroDeElementos); /*Se llama la funci�n y se le pasan los dos par�metros*/
	
	return 0;
}

/*Fin de main*/

void fnQsort (uint8_t *bApuntadorArreglo, uint8_t bNumeroDeElementos) /*Comienza la funci�n*/ 
{
	static uint8_t bIndice = 0; /*Se crea una variable para el �ndice y se inicia en cero*/
	static uint8_t *bApuntadorSiguienteElemento; /*Se declara un nuevo apuntador que comparar� los siguientes elementos con el apuntador base actual (bApuntadorArreglo)*/
	static uint8_t bTemporal; /*Se crea una variable temporal para evitar p�rdida de datos*/
	static uint8_t bOffset = 1; /*Esta variable determina cu�ntas veces le falta por recorrerse el *bApuntadorSiguienteElemento para llegar al final del arreglo. Se inicializa en uno debido a que el *bApuntadorSiguienteElemento comienza en la posici�n [1] del arreglo*/

	do /*Comienza el primer ciclo*/
	{
		bApuntadorSiguienteElemento = bApuntadorArreglo + 1; /*El apuntador para el siguiente elemento siempre comienza uno por delante del apuntador base*/
			do /*Comienza el segundo ciclo*/
			{
				if (*bApuntadorArreglo > *bApuntadorSiguienteElemento) /*En caso de que sea mayor el valor base (de la izquierda), se intercambia con el de la derecha*/
				{
					bTemporal = *bApuntadorSiguienteElemento; /*Se guarda el elemento al que apunta el *bApuntadorSiguienteElemento en bTemporal para no perderlo*/
					*bApuntadorSiguienteElemento = *bApuntadorArreglo; /**bApuntadorSiguienteElemento adquiere el valor del elemento al que apunta *bApuntadorArreglo*/
					*bApuntadorArreglo = bTemporal; /*El apuntador base adquiere el valor en el que estaba el *bApuntadorSiguienteElemento, el cual se guard� en bTemporal*/
				}
				else /*En caso de que el elemento de la izquierda sea menor, quiere decir que se encuentra en orden, y ninguna acci�n ocurre*/
				{
				}
				bApuntadorSiguienteElemento++; /*Se incrementa en uno el bApuntadorSiguienteElemento para apuntar a la siguiente posici�n de la cadena*/
				bIndice++; /*Se incrementa en uno el �ndice*/
			}
			while ((bIndice != (bNumeroDeElementos - bOffset)) && bNumeroDeElementos != 1); /*El ciclo interno continuar� hasta que se haya recorrido bApuntadorSiguienteElemento hasta el �ltimo elemento. En caso de que el arreglo contenga un �nico elemento, el ciclo tambi�n finalizar�*/
		bIndice = 0; /*El �ndice se reinicia a 0 antes de volver a comenzar el ciclo*/
		bApuntadorArreglo++; /*El apuntador base se recorre al siguiente elemento, lo que significa que el elemento en el que estaba ya qued� ordenado*/
		bOffset++; /*El bOffset se incrementa en uno, lo cual indica que en el pr�ximo ciclo, el bApuntadorSiguienteElemento tedr� que recorrerse una vez menos para llegar al final del arreglo*/
	}while(bOffset != bNumeroDeElementos && bNumeroDeElementos != 1); /*El ciclo principal termina cuando el bOffset se incrementa hasta ser igual al n�mero de elementos, lo cual significa que el apuntador base (bApuntadorArreglo) ya ha pasado por todos los elementos.  En caso de que el arreglo contenga un �nico elemento, el ciclo tambi�n finalizar�*/
return; /*Se regresa a main sin retornar par�metros*/
}
