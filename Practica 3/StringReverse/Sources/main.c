#include "derivative.h" /* include peripheral declarations */
#include "stdint.h" /*Include para los tipos de datos*/

void fnStringReverse (int8_t *); /*Se declara la funci�n que recibir� un apuntador y no regresar� par�metros*/

int main(void) /*Comienza main*/
{
	int8_t baCadenaAReversear[] = "Arroz"; /*Se inicializa el contenido de la cadena*/
	int8_t *bApuntadorCadena; /*Se crea un apuntador el cual apuntar� hacia esa cadena*/
	
	bApuntadorCadena = &baCadenaAReversear[0]; /*El apuntador apunta al primer elemento de la cadena*/
	fnStringReverse(bApuntadorCadena); /*Se llama la funci�n y se le pasa el par�metro*/
	return 0;
}

/*Fin de main*/

void fnStringReverse (int8_t *bApuntadorCadena) /*Comienza la funci�n*/ 
{
	 static int8_t *bApuntadorFinalCadena; /*Se crea otro apuntador, el cual comenzar� al final de la cadena*/
	 static int8_t bTemporal; /*Se crea una variable temporal para evitar p�rdida de datos*/
	 static uint8_t bLongitud = 0; /*En esta variable se guardar� la longitud de la cadena, se inicializa en 0*/ 
	 static uint8_t bIndice = 0; /*Variable para el �ndice, se inicializa en 0*/
	
	bApuntadorFinalCadena = bApuntadorCadena; /*Ambos apuntadores comienzan apuntado al primer elemento de la cadena*/
	do /*Comienza el ciclo*/
	{
		bApuntadorFinalCadena++; /*Se recorrer� el apuntador al final de la cadena hasta que tope con el nulo*/
		bLongitud++; /*Cada que se recorra, se va incrementando esta variable para calcular la longitud de la cadena*/
	}while(*bApuntadorFinalCadena != 0);
	
	bApuntadorFinalCadena--; /*Se recorre hacia atr�s una vez el 2do apuntador para que comience en el �ltimo elemento en vez de en el elemento nulo*/
	
	do
	{
		bTemporal = *bApuntadorFinalCadena; /*Se guarda el valor del �ltimo elemento en la variable temporal para no perderlo*/
		*bApuntadorFinalCadena = *bApuntadorCadena; /*El �ltimo elemento adquiere el valor del primero*/
		*bApuntadorCadena= bTemporal; /*El primer elemento adquiere el valor del �ltimo, ya que este se guardaba en la variable bTemporal*/
		bApuntadorCadena++; /*Se incrementa en uno la direcci�n del primer apuntador para que ahora apunte al segundo elemento*/
		bApuntadorFinalCadena--; /*Se decrementa en uno la direcci�n del segundo apuntador para que ahora apunte al pen�ltimo elemento*/
		bIndice++; /*Se incrementa en uno el �ndice*/
		/*El ciclo continuar� intercambiando los datos de los extremos hasta llegar al centro*/
	}while (bIndice != (bLongitud/2) && bLongitud != 1); /*Se sabe que se lleg� al centro de la cadena (donde cada elemento ya ha sido intercambiado de posici�n) al ser igual el �ndice a la longitud de la cadena sobre 2.El n�mero es truncado si la divisi�n da decimal en caso de una longitud impar. El ciclo tambi�n termina si la longitud de la cadena fue de un solo elemento, ya que no hace falta hacer intercambios*/
return; /*Se regresa a main sin regresar par�metros*/
}


