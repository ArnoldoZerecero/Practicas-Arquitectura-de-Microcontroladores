#include "derivative.h" /* include peripheral declarations */
#include "stdint.h" /*Include para los tipos de datos*/

void fnStringReverse (int8_t *); /*Se declara la función que recibirá un apuntador y no regresará parámetros*/

int main(void) /*Comienza main*/
{
	int8_t baCadenaAReversear[] = "Arroz"; /*Se inicializa el contenido de la cadena*/
	int8_t *bApuntadorCadena; /*Se crea un apuntador el cual apuntará hacia esa cadena*/
	
	bApuntadorCadena = &baCadenaAReversear[0]; /*El apuntador apunta al primer elemento de la cadena*/
	fnStringReverse(bApuntadorCadena); /*Se llama la función y se le pasa el parámetro*/
	return 0;
}

/*Fin de main*/

void fnStringReverse (int8_t *bApuntadorCadena) /*Comienza la función*/ 
{
	 static int8_t *bApuntadorFinalCadena; /*Se crea otro apuntador, el cual comenzará al final de la cadena*/
	 static int8_t bTemporal; /*Se crea una variable temporal para evitar pérdida de datos*/
	 static uint8_t bLongitud = 0; /*En esta variable se guardará la longitud de la cadena, se inicializa en 0*/ 
	 static uint8_t bIndice = 0; /*Variable para el índice, se inicializa en 0*/
	
	bApuntadorFinalCadena = bApuntadorCadena; /*Ambos apuntadores comienzan apuntado al primer elemento de la cadena*/
	do /*Comienza el ciclo*/
	{
		bApuntadorFinalCadena++; /*Se recorrerá el apuntador al final de la cadena hasta que tope con el nulo*/
		bLongitud++; /*Cada que se recorra, se va incrementando esta variable para calcular la longitud de la cadena*/
	}while(*bApuntadorFinalCadena != 0);
	
	bApuntadorFinalCadena--; /*Se recorre hacia atrás una vez el 2do apuntador para que comience en el último elemento en vez de en el elemento nulo*/
	
	do
	{
		bTemporal = *bApuntadorFinalCadena; /*Se guarda el valor del último elemento en la variable temporal para no perderlo*/
		*bApuntadorFinalCadena = *bApuntadorCadena; /*El último elemento adquiere el valor del primero*/
		*bApuntadorCadena= bTemporal; /*El primer elemento adquiere el valor del último, ya que este se guardaba en la variable bTemporal*/
		bApuntadorCadena++; /*Se incrementa en uno la dirección del primer apuntador para que ahora apunte al segundo elemento*/
		bApuntadorFinalCadena--; /*Se decrementa en uno la dirección del segundo apuntador para que ahora apunte al penúltimo elemento*/
		bIndice++; /*Se incrementa en uno el índice*/
		/*El ciclo continuará intercambiando los datos de los extremos hasta llegar al centro*/
	}while (bIndice != (bLongitud/2) && bLongitud != 1); /*Se sabe que se llegó al centro de la cadena (donde cada elemento ya ha sido intercambiado de posición) al ser igual el índice a la longitud de la cadena sobre 2.El número es truncado si la división da decimal en caso de una longitud impar. El ciclo también termina si la longitud de la cadena fue de un solo elemento, ya que no hace falta hacer intercambios*/
return; /*Se regresa a main sin regresar parámetros*/
}


