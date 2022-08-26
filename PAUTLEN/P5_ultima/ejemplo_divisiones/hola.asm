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
;D:	,
;D:	resultado
;declarar_variable
	_resultado resd 1
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	;
;R18:	<identificadores> ::= <identificador>
;R19:	<identificadores> ::= <identificador> , <identificadores>
;R19:	<identificadores> ::= <identificador> , <identificadores>
;R4:	<declaracion> ::= <clase> <identificadores> ;
;D:	x
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
;D:	=
;D:	15
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 15
;R81:	<exp> ::= <constante>
;D:	;
	pop dword eax
	mov dword [_x], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	y
;D:	=
;D:	5
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 5
;R81:	<exp> ::= <constante>
;D:	;
	pop dword eax
	mov dword [_y], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	resultado
;D:	=
;D:	x
;D:	/
;escribir_operando
	push dword _x
;R80:	<exp> ::= <identificador>
;D:	y
;D:	;
;escribir_operando
	push dword _y
;R80:	<exp> ::= <identificador>
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	mov dword ebx, [ebx]
	mov dword edx, 0
	cmp ebx, edx
	je near _division_error
	idiv ebx
	push dword eax
;R74:	<exp> ::= <exp> / <exp>
	pop dword eax
	mov dword [_resultado], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	(
;D:	resultado
;D:	)
;escribir_operando
	push dword _resultado
;R80:	<exp> ::= <identificador>
;R82:	<exp> ::= ( <exp> )
;D:	;
;R56:	<escritura> ::= printf <exp>
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	x
;D:	=
;D:	4
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 4
;R81:	<exp> ::= <constante>
;D:	;
	pop dword eax
	mov dword [_x], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	y
;D:	=
;D:	-
;D:	2
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 2
;R81:	<exp> ::= <constante>
;D:	;
	pop dword eax
	neg eax
	push dword eax
;R76:	<exp> ::= - <exp>
	pop dword eax
	mov dword [_y], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	resultado
;D:	=
;D:	x
;D:	/
;escribir_operando
	push dword _x
;R80:	<exp> ::= <identificador>
;D:	y
;D:	;
;escribir_operando
	push dword _y
;R80:	<exp> ::= <identificador>
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	mov dword ebx, [ebx]
	mov dword edx, 0
	cmp ebx, edx
	je near _division_error
	idiv ebx
	push dword eax
;R74:	<exp> ::= <exp> / <exp>
	pop dword eax
	mov dword [_resultado], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	(
;D:	resultado
;D:	)
;escribir_operando
	push dword _resultado
;R80:	<exp> ::= <identificador>
;R82:	<exp> ::= ( <exp> )
;D:	;
;R56:	<escritura> ::= printf <exp>
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	x
;D:	=
;D:	-
;D:	12
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 12
;R81:	<exp> ::= <constante>
;D:	;
	pop dword eax
	neg eax
	push dword eax
;R76:	<exp> ::= - <exp>
	pop dword eax
	mov dword [_x], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	y
;D:	=
;D:	3
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 3
;R81:	<exp> ::= <constante>
;D:	;
	pop dword eax
	mov dword [_y], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	(
;D:	x
;D:	)
;escribir_operando
	push dword _x
;R80:	<exp> ::= <identificador>
;R82:	<exp> ::= ( <exp> )
;D:	;
;R56:	<escritura> ::= printf <exp>
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	resultado
;D:	=
;D:	x
;D:	/
;escribir_operando
	push dword _x
;R80:	<exp> ::= <identificador>
;D:	y
;D:	;
;escribir_operando
	push dword _y
;R80:	<exp> ::= <identificador>
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	mov dword ebx, [ebx]
	mov dword edx, 0
	cmp ebx, edx
	je near _division_error
	idiv ebx
	push dword eax
;R74:	<exp> ::= <exp> / <exp>
	pop dword eax
	mov dword [_resultado], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	(
;D:	resultado
;D:	)
;escribir_operando
	push dword _resultado
;R80:	<exp> ::= <identificador>
;R82:	<exp> ::= ( <exp> )
;D:	;
;R56:	<escritura> ::= printf <exp>
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	x
;D:	=
;D:	-
;D:	4
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 4
;R81:	<exp> ::= <constante>
;D:	;
	pop dword eax
	neg eax
	push dword eax
;R76:	<exp> ::= - <exp>
	pop dword eax
	mov dword [_x], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	y
;D:	=
;D:	-
;D:	4
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 4
;R81:	<exp> ::= <constante>
;D:	;
	pop dword eax
	neg eax
	push dword eax
;R76:	<exp> ::= - <exp>
	pop dword eax
	mov dword [_y], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	resultado
;D:	=
;D:	x
;D:	/
;escribir_operando
	push dword _x
;R80:	<exp> ::= <identificador>
;D:	y
;D:	;
;escribir_operando
	push dword _y
;R80:	<exp> ::= <identificador>
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	mov dword ebx, [ebx]
	mov dword edx, 0
	cmp ebx, edx
	je near _division_error
	idiv ebx
	push dword eax
;R74:	<exp> ::= <exp> / <exp>
	pop dword eax
	mov dword [_resultado], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	(
;D:	resultado
;D:	)
;escribir_operando
	push dword _resultado
;R80:	<exp> ::= <identificador>
;R82:	<exp> ::= ( <exp> )
;D:	;
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
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
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
