.set CANTIDAD_DATOS, 5 /*Macro para la cantidad de elementos a copiar entre los arreglos*/

	.data
	.align 1
		 gbaArray1: /*Este arreglo será el apuntador fuente, 5 elementos*/
		 .byte 1,2,3,4,5
	.align 1
		 gbaArray2: /*Este arreglo será el apuntador destino, los valores con el que se inicialice no importa*/
		 .byte 1,1,1,1,1
/* This assembly file uses GNU syntax */
	.text
	.section .rodata
	.align 2

.LC0:
	.text
	.align 2
	.global main
	.type main function
main:
    push {r3, lr}
	add r3, sp, #4
	
	ldrb r0, = gbaArray1 /*Se guarda en r0 la dirección del primer apuntador*/
	ldrb r1, = gbaArray2 /*Se guarda en r1 la dirección del segundo apuntador*/
	mov r2, #CANTIDAD_DATOS /*Se guarda en r2 el valor de la cantidad de datos*/
	bl fnMemCopy /*Se llama la funcion*/
	
	mov r3, #0
	mov r0, r3
	pop {r3, pc}
	
	/*Fin de main*/
	
	.align 2
	.type fnMemCopy function
	
fnMemCopy: /*Comienza la funcion*/
	mov r3, #0 /*Registro para el índice, se inicializa en cero*/
	WHILE:
	ldrb r4, [r0, r3] /*r4 adquiere el valor del primer apuntador incrementado r3 veces para moverse entre los elementos del arreglo*/
	strb r4, [r1, r3] /*Se guarda el valor r3 en el segundo apuntador incrementado r3 veces para moverse entre los elementos del arreglo*/
	add r3, #1 /*Se incrementa el índice en 1*/
	cmp r3, r2 /*Compara el índice y la cantidad de datos a copiar*/
	bne WHILE /*Si no son iguales, sifnifica que aun no se recorren por completo ambos arreglos, se repite el ciclo*/
	bx lr /*Termina la funcion, regresa al main*/
	
	.align 2
.L3:
	.word .LC0
	.end
