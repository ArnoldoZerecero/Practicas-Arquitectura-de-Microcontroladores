	.data
	.align 1
	    gbaCadena1: /*Se declara una cadena que termina en cero (nulo)*/
	    .asciz "Microcontrolador"
/* This assembly file uses GNU syntax */
	.text
	.section	.rodata
	.align	2
	
	
.LC0:
	
	.text
	.align	2
	.global	main
	.type main function
	
main:
	push {r3, lr}
	add	r3, sp, #4
	
	ldrb r1, = gbaCadena1 /*r1 será el apuntador para la cadena*/
	bl bfnStrlen /*Se llama la funcion*/
	
	
	mov	r3, #0
	mov	r0, r3
	pop {r3, pc}
	
	/*Fin de main*/
	
	.align 2
	.type bfnStrlen function
	
bfnStrlen: /*Comienza la funcion*/
	mov r0, #0 /*Registro para el acumulador (parámetro de retorno), se inicializa en cero*/
	mov r3, #0 /*Registro para el índice, se inicializa en cero*/
	RECORRER:
	ldrb r2, [r1, r3] /*Se escribe en r2 la letra de la cadena según la posición dictada por r3*/
	add r0, #1 /*Se incrementa en uno el acumulador*/
	add r3, #1 /*Se incrementa en uno el índice*/
	cmp r2, #0 /*Se verifica que la letra leída no sea el nulo*/
	bne RECORRER /*En caso de que no sea nulo, se repite el ciclo para comparar la siguiente letra*/
	sub r0, #1 /*Se resta uno del acumulador para no contar el nulo*/
	bx lr /*Termina la funcion, regresa al main*/
	
	.align	2
.L3:
	.word	.LC0
	.end
