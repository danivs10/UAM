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
;D:	resultado
;declarar_variable
	_resultado resd 1
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	;
;R18:	<identificadores> ::= <identificador>
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
;D:	fibonacci
;D:	(
;D:	int
;R10:	<tipo> ::= int
;D:	num1
;R27:	<parametro_funcion> ::= <tipo> <identificador>
;D:	)
;R26:	<resto_parametros_funcion> ::=
;R23:	<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>
;D:	{
;D:	int
;R10:	<tipo> ::= int
;R9:	<clase_escalar> ::= <tipo>
;R5:	<clase> ::= <clase_escalar>
;D:	res1
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	,
;D:	res2
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	;
;R18:	<identificadores> ::= <identificador>
;R19:	<identificadores> ::= <identificador> , <identificadores>
;R4:	<declaracion> ::= <clase> <identificadores> ;
;D:	if
;R2:	<declaraciones> ::= <declaracion>
;R28:	<declaraciones_funcion> ::= <declaraciones>
_fibonacci:
	push dword ebp
	mov dword ebp, esp
	sub esp, 8
;D:	(
;D:	(
;D:	num1
;D:	==
	lea eax, [ebp + 8]
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	0
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	)
	pop dword eax
	pop dword ebx
	mov dword ebx, [ebx]
	cmp eax, ebx
	je near igual_0
	mov dword eax, 0
	push dword eax
	jmp near fin_igual_0
igual_0:
	mov dword eax,1
	push dword eax
fin_igual_0:
;R93:	<comparacion> ::= <exp> == <exp>
;R83:	<exp> ::= ( <comparacion> )
;D:	)
	pop dword eax
	cmp eax, 0
	je near _end_simple_conditional_1
;D:	{
;D:	return
;D:	0
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	;
;R61:	<retorno_funcion> ::= return <exp>
	pop eax
	mov esp, ebp
	pop ebp
	ret
;R38:	<sentencia_simple> ::= <retorno_funcion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
;D:	if
_end_simple_conditional_1:
;R50:	<condicional> ::= if ( <exp> ) { <sentencias> }
;R40:	<bloque> ::= <condicional>
;R33:	<sentencia> ::= <bloque>
;D:	(
;D:	(
;D:	num1
;D:	==
	lea eax, [ebp + 8]
	push dword eax
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
	cmp eax, ebx
	je near igual_1
	mov dword eax, 0
	push dword eax
	jmp near fin_igual_1
igual_1:
	mov dword eax,1
	push dword eax
fin_igual_1:
;R93:	<comparacion> ::= <exp> == <exp>
;R83:	<exp> ::= ( <comparacion> )
;D:	)
	pop dword eax
	cmp eax, 0
	je near _end_simple_conditional_2
;D:	{
;D:	return
;D:	1
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 1
;R81:	<exp> ::= <constante>
;D:	;
;R61:	<retorno_funcion> ::= return <exp>
	pop eax
	mov esp, ebp
	pop ebp
	ret
;R38:	<sentencia_simple> ::= <retorno_funcion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
;D:	res1
_end_simple_conditional_2:
;R50:	<condicional> ::= if ( <exp> ) { <sentencias> }
;R40:	<bloque> ::= <condicional>
;R33:	<sentencia> ::= <bloque>
;D:	=
;D:	fibonacci
;D:	(
;D:	num1
;D:	-
	lea eax, [ebp + 8]
	push dword eax
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
	sub ebx, eax
	push dword ebx
;R73:	<exp> ::= <exp> - <exp>
;R92:	<resto_lista_expresiones> ::=
;R89:	<lista_expresiones ::= <exp> <resto_lista_expresiones>
	call _fibonacci
	add esp, 4
	push dword eax
;R88:	<exp> ::= <identificador> ( <lista_expresiones> )
;D:	;
	lea eax, [ebp - 4]
	push dword eax

	pop dword eax
	pop dword ebx
	push dword eax
	push dword ebx
	pop dword ebx
	pop dword eax
	mov dword [eax], ebx
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	res2
;D:	=
;D:	fibonacci
;D:	(
;D:	num1
;D:	-
	lea eax, [ebp + 8]
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	2
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 2
;R81:	<exp> ::= <constante>
;D:	)
	pop dword eax
	pop dword ebx
	mov dword ebx, [ebx]
	sub ebx, eax
	push dword ebx
;R73:	<exp> ::= <exp> - <exp>
;R92:	<resto_lista_expresiones> ::=
;R89:	<lista_expresiones ::= <exp> <resto_lista_expresiones>
	call _fibonacci
	add esp, 4
	push dword eax
;R88:	<exp> ::= <identificador> ( <lista_expresiones> )
;D:	;
	lea eax, [ebp - 8]
	push dword eax

	pop dword eax
	pop dword ebx
	push dword eax
	push dword ebx
	pop dword ebx
	pop dword eax
	mov dword [eax], ebx
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	return
;D:	res1
;D:	+
	lea eax, [ebp - 4]
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	res2
;D:	;
	lea eax, [ebp - 8]
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
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R22:<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }
;D:	scanf
;R21:	<funciones> ::= 
;R20:	<funciones> ::= <funcion> <funciones>
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
;D:	resultado
;D:	=
;D:	fibonacci
;D:	(
;D:	x
;D:	)
;escribir_operando
	push dword _x
;operandoEnPilaAArgumento
	pop dword eax
	mov dword eax, [eax]
	push dword eax
;R80:	<exp> ::= <identificador>
;R92:	<resto_lista_expresiones> ::=
;R89:	<lista_expresiones ::= <exp> <resto_lista_expresiones>
	call _fibonacci
	add esp, 4
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
