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
;D:	function
;R2:	<declaraciones> ::= <declaracion>
;escribir_segmento_codigo
segment .text
	global main
	extern malloc, free
	extern scan_int, print_int, scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
;D:	int
;R10:	<tipo> ::= int
;D:	suma
;D:	(
;D:	int
;R10:	<tipo> ::= int
;D:	num1
;R27:	<parametro_funcion> ::= <tipo> <identificador>
;D:	;
;D:	int
;R10:	<tipo> ::= int
;D:	num2
;R27:	<parametro_funcion> ::= <tipo> <identificador>
;D:	)
;R26:	<resto_parametros_funcion> ::=
;R25:	<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion>
;R23:	<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>
;D:	{
;D:	return
;R29:	<declaraciones_funcion> ::= 
_suma:
	push dword ebp
	mov dword ebp, esp
	sub esp, 0
;D:	num1
;D:	+
	lea eax, [ebp + 12]
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	num2
;D:	;
	lea eax, [ebp + 8]
	push dword eax
;R80:	<exp> ::= <identificador>
	pop dword eax
	pop dword ebx
	mov dword ebx, [ebx]
	mov dword eax, [eax]
	add eax, ebx
	push dword eax
;R72:	<exp> ::= <exp> + <exp>
;R61:	<retorno_funcion> ::= return <exp>
	pop eax
	mov esp, ebp
	pop ebp
	ret
;R38:	<sentencia_simple> ::= <retorno_funcion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
;R22:<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }
;D:	x
;R21:	<funciones> ::= 
;R20:	<funciones> ::= <funcion> <funciones>
;escribir_inicio_main
; -----------------------
; PROCEDIMIENTO PRINCIPAL
main:
	mov dword [__esp], esp
;D:	=
;D:	1
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 1
;R81:	<exp> ::= <constante>
;D:	;
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
;D:	resultado
;D:	=
;D:	suma
;D:	(
;D:	x
;D:	,
;escribir_operando
	push dword _x
;operandoEnPilaAArgumento
	pop dword eax
	mov dword eax, [eax]
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	y
;D:	)
;escribir_operando
	push dword _y
;operandoEnPilaAArgumento
	pop dword eax
	mov dword eax, [eax]
	push dword eax
;R80:	<exp> ::= <identificador>
;R92:	<resto_lista_expresiones> ::=
;R91:	<resto_lista_expresiones ::= , <exp> <resto_lista_expresiones>
;R89:	<lista_expresiones ::= <exp> <resto_lista_expresiones>
	call _suma
	add esp, 8
	push dword eax
;R88:	<exp> ::= <identificador> ( <lista_expresiones> )
;D:	;
	pop dword eax
	mov dword [_resultado], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	resultado
;D:	;
;escribir_operando
	push dword _resultado
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
;D:	resultado
;D:	=
;D:	suma
;D:	(
;D:	x
;D:	,
;escribir_operando
	push dword _x
;operandoEnPilaAArgumento
	pop dword eax
	mov dword eax, [eax]
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	1
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 1
;R81:	<exp> ::= <constante>
;D:	)
;R92:	<resto_lista_expresiones> ::=
;R91:	<resto_lista_expresiones ::= , <exp> <resto_lista_expresiones>
;R89:	<lista_expresiones ::= <exp> <resto_lista_expresiones>
	call _suma
	add esp, 8
	push dword eax
;R88:	<exp> ::= <identificador> ( <lista_expresiones> )
;D:	;
	pop dword eax
	mov dword [_resultado], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	resultado
;D:	;
;escribir_operando
	push dword _resultado
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
;D:	resultado
;D:	=
;D:	suma
;D:	(
;D:	10
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 10
;R81:	<exp> ::= <constante>
;D:	,
;D:	y
;D:	)
;escribir_operando
	push dword _y
;operandoEnPilaAArgumento
	pop dword eax
	mov dword eax, [eax]
	push dword eax
;R80:	<exp> ::= <identificador>
;R92:	<resto_lista_expresiones> ::=
;R91:	<resto_lista_expresiones ::= , <exp> <resto_lista_expresiones>
;R89:	<lista_expresiones ::= <exp> <resto_lista_expresiones>
	call _suma
	add esp, 8
	push dword eax
;R88:	<exp> ::= <identificador> ( <lista_expresiones> )
;D:	;
	pop dword eax
	mov dword [_resultado], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	resultado
;D:	;
;escribir_operando
	push dword _resultado
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
;D:	resultado
;D:	=
;D:	suma
;D:	(
;D:	3
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 3
;R81:	<exp> ::= <constante>
;D:	,
;D:	5
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 5
;R81:	<exp> ::= <constante>
;D:	)
;R92:	<resto_lista_expresiones> ::=
;R91:	<resto_lista_expresiones ::= , <exp> <resto_lista_expresiones>
;R89:	<lista_expresiones ::= <exp> <resto_lista_expresiones>
	call _suma
	add esp, 8
	push dword eax
;R88:	<exp> ::= <identificador> ( <lista_expresiones> )
;D:	;
	pop dword eax
	mov dword [_resultado], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	resultado
;D:	;
;escribir_operando
	push dword _resultado
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
