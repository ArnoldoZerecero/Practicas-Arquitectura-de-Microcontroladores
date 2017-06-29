	.data
	.align 1
	    gbaCadena1: /*Se declaran 2 cadenas que terminan en cero (nulo)*/
	    .asciz "Hola"
	.align 1
		gbaCadena2:
		.asciz "Hola"
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
	
	ldrb r1, = gbaCadena1 /*r1 será el apuntador para la primer cadena*/
	ldrb r2, = gbaCadena2 /*r2 será el apuntador para la segunda cadena*/
	bl bfnStrcmp /*Se llama la funcion*/
	
	mov r3, #0
	mov r0, r3
	pop {r3, pc}
	
	/*Fin de main*/
	
	.align 2
	.type bfnStrcmp function
	
bfnStrcmp: /*Comienza la funcion*/
	mov r3, #0 /*Registro para el índice, se inicializa en cero*/
	RECORRER:
	ldrb r4, [r1, r3] /*Se escribe en r4 el valor de la primer cadena. La posición en la cadena se recorre con el offset r3*/
	ldrb r5, [r2, r3] /*Se escribe en r5 el valor de la segunda cadena. La posición en la cadena se recorre con el offset r3*/
	cmp r4, #0 /*Se comparan ambos registros con cero para verificar que si se llegó al nulo*/
	beq FINALIZAR /*En caso de que se llegue al nulo, se va al branch de finalizado*/
	cmp r5, #0
	beq FINALIZAR 
	add r3, #1 /*Se incrementa el índice*/
	cmp r5, r4 /*Comparamos las letras de ambas cadenas en la misma posición*/
	beq RECORRER /*Si las letras son iguales, se repite el ciclo para recorrer las cadenas y volver a comparar*/
	bne FINALIZAR /*Si las letras sean diferentes, también se va al branch de finalizado*/
	
	FINALIZAR: /*Se comparan una vez más las letras en donde se quedaron ambas cadenas, ya que se pudo haber accedido a este branch si se alcanzó el nulo en ambas al mismo tiempo*/
	cmp r5, r4
	beq IGUALES 
	bne DIFERENTES
	
	IGUALES: /*Si son iguales, r0 (parámetro de retorno) será cero*/
	mov r0, #0
	bx lr /*Termina la funcion, regresa al main*/
	
	DIFERENTES: /*Si son diferentes, r0 (parámetro de retorno) será uno*/
	mov r0, #1
	bx lr /*Termina la funcion, regresa al main*/
	
	.align 2
.L3:
	.word .LC0
	.end
