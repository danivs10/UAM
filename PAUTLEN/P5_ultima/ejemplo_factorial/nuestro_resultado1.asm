;escribir_subseccion_data
segment .data
	_err_divZ db "ERROR. The divisor can't be 0", 0
	err_index_out_of_range db "ERROR. The index is out of range 0", 0
;escribir_cabecera_bss

segment .bss
	__esp resd 1
;D:	main
;D:	{
;D:	int
;R10:	<tipo> ::= int
;R9:	<clase_escalar> ::= <tipo>
;R5:	<clase> ::= <clase_escalar>
;D:	x
;declarar_variable
	_x resd 1
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	,
;D:	y
;declarar_variable
	_y resd 1
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	;
;R18:	<identificadores> ::= <identificador>
;R19:	<identificadores> ::= <identificador> , <identificadores>
;R4:	<declaracion> ::= <clase> <identificadores> ;
;D:	scanf
;R2:	<declaraciones> ::= <declaracion>
;escribir_segmento_codigo
segment .text
	global main
	extern malloc, free
	extern scan_int, print_int, scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
;R21:	<funciones> ::= 
;escribir_inicio_main
; -----------------------
; PROCEDIMIENTO PRINCIPAL
main:
	mov dword [__esp], esp
;D:	x
;leer
	push dword _x
	call scan_int
	add esp, 4
;R54:	<lectura> ::= scanf <identificador>
;R35:	<sentencia_simple> ::= <lectura>
;D:	;
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	y
;D:	=
;D:	1
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 1
;R81:	<exp> ::= <constante>
;D:	;
	pop dword eax
	mov dword [_y], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	while
;D:	(
_start_loop_1:
;D:	(
;D:	x
;D:	>
;escribir_operando
	push dword _x
;R80:	<exp> ::= <identificador>
;D:	1
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 1
;R81:	<exp> ::= <constante>
;D:	)
	pop dword eax
	pop dword ebx
	mov dword ebx, [ebx]
	cmp ebx, eax
	jg near mayor_0
	mov dword ebx, 0
	push dword ebx
	jmp near fin_mayor_0
mayor_0:
	mov dword ebx,1
	push dword ebx
fin_mayor_0:
;R98:	<comparacion> ::= <exp> > <exp>
;R83:	<exp> ::= ( <comparacion> )
;D:	)
	pop dword eax
	cmp eax, 0
	je near _end_loop_1
;D:	{
;D:	y
;D:	=
;D:	x
;D:	*
;escribir_operando
	push dword _x
;R80:	<exp> ::= <identificador>
;D:	y
;D:	;
;escribir_operando
	push dword _y
;R80:	<exp> ::= <identificador>
	pop dword eax
	pop dword ebx
	mov dword ebx, [ebx]
	mov dword eax, [eax]
	imul ebx
	push dword eax
;R75:	<exp> ::= <exp> * <exp>
	pop dword eax
	mov dword [_y], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	x
;D:	=
;D:	x
;D:	-
;escribir_operando
	push dword _x
;R80:	<exp> ::= <identificador>
;D:	1
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 1
;R81:	<exp> ::= <constante>
;D:	;
	pop dword eax
	pop dword ebx
	mov dword ebx, [ebx]
	sub ebx, eax
	push dword ebx
;R73:	<exp> ::= <exp> - <exp>
	pop dword eax
	mov dword [_x], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
;R31:	<sentencias> ::= <sentencia> <sentencias>
	jmp near _start_loop_1
_end_loop_1:
;R52:	<bucle> ::= while ( <exp> ) { <sentencias> }
;R41:	<bloque> ::= <bucle>
;R33:	<sentencia> ::= <bloque>
;D:	printf
;D:	y
;D:	;
;escribir_operando
	push dword _y
;R80:	<exp> ::= <identificador>
;R56:	<escritura> ::= printf <exp>
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R1:	<programa> ::= main { <declaraciones> <funciones> <sentencias> }
	jmp end_program
_division_error:
	push dword _err_divZ
	call print_string
	add esp, 4
	call print_endofline
	jmp end_program
end_index_out_of_range:
	push dword err_index_out_of_range
	call print_string
	add esp, 4
	call print_endofline
	jmp near end_program
end_program:
	mov esp, [__esp]
	ret
