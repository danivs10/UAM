;escribir_subseccion_data
segment .data
	_err_divZ db "ERROR. The divisor can't be 0", 0
	err_index_out_of_range db "ERROR. The index is out of range 0", 0
;escribir_cabecera_bss

segment .bss
	__esp resd 1
;D:	main
;D:	{
;D:	boolean
;R11:	<tipo> ::= boolean
;R9:	<clase_escalar> ::= <tipo>
;R5:	<clase> ::= <clase_escalar>
;D:	resultado
;declarar_variable
	_resultado resd 1
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	;
;R18:	<identificadores> ::= <identificador>
;R4:	<declaracion> ::= <clase> <identificadores> ;
;D:	array
;D:	boolean
;R11:	<tipo> ::= boolean
;D:	[
;D:	3
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;D:	]
;R15:	<clase_vector> ::= array <tipo> [ <constante_entera> ]
;R7:	<clase> ::= <clase_vector>
;D:	vector
;declarar_variable
	_vector resd 3
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	;
;R18:	<identificadores> ::= <identificador>
;R4:	<declaracion> ::= <clase> <identificadores> ;
;D:	function
;R2:	<declaraciones> ::= <declaracion>
;R3:	<declaraciones> ::= <declaracion> <declaraciones>
;escribir_segmento_codigo
segment .text
	global main
	extern malloc, free
	extern scan_int, print_int, scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
;D:	boolean
;R11:	<tipo> ::= boolean
;D:	or
;D:	(
;D:	boolean
;R11:	<tipo> ::= boolean
;D:	b1
;R27:	<parametro_funcion> ::= <tipo> <identificador>
;D:	;
;D:	boolean
;R11:	<tipo> ::= boolean
;D:	b2
;R27:	<parametro_funcion> ::= <tipo> <identificador>
;D:	;
;D:	boolean
;R11:	<tipo> ::= boolean
;D:	b3
;R27:	<parametro_funcion> ::= <tipo> <identificador>
;D:	)
;R26:	<resto_parametros_funcion> ::=
;R25:	<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion>
;R25:	<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion>
;R23:	<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>
;D:	{
;D:	boolean
;R11:	<tipo> ::= boolean
;R9:	<clase_escalar> ::= <tipo>
;R5:	<clase> ::= <clase_escalar>
;D:	a
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	;
;R18:	<identificadores> ::= <identificador>
;R4:	<declaracion> ::= <clase> <identificadores> ;
;D:	a
;R2:	<declaraciones> ::= <declaracion>
;R28:	<declaraciones_funcion> ::= <declaraciones>
_or:
	push dword ebp
	mov dword ebp, esp
	sub esp, 4
;D:	=
;D:	b1
;D:	||
	lea eax, [ebp + 16]
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	b2
;D:	||
	lea eax, [ebp + 12]
	push dword eax
;R80:	<exp> ::= <identificador>
;o

	pop dword ebx
	mov dword ebx, [ebx]
	pop dword eax
	mov dword eax, [eax]
	or eax, ebx
	push dword eax
;R78:	<exp> ::= <exp> || <exp>
;D:	b3
;D:	;
	lea eax, [ebp + 8]
	push dword eax
;R80:	<exp> ::= <identificador>
;o

	pop dword ebx
	mov dword ebx, [ebx]
	pop dword eax
	or eax, ebx
	push dword eax
;R78:	<exp> ::= <exp> || <exp>
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
;D:	return
;D:	a
;D:	;
	lea eax, [ebp - 4]
	push dword eax
;R80:	<exp> ::= <identificador>
;R61:	<retorno_funcion> ::= return <exp>
	pop eax
	mov dword eax, [eax]
	mov esp, ebp
	pop ebp
	ret
;R38:	<sentencia_simple> ::= <retorno_funcion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R22:<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }
;D:	vector
;R21:	<funciones> ::= 
;R20:	<funciones> ::= <funcion> <funciones>
;escribir_inicio_main
; -----------------------
; PROCEDIMIENTO PRINCIPAL
main:
	mov dword [__esp], esp
;D:	[
;D:	0
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	]
	;escribir_elemento_vector
	pop dword eax
	cmp eax, 0
	jl near end_index_out_of_range
	cmp eax, 2
	jg near end_index_out_of_range
	mov dword edx, _vector
	lea eax, [edx + eax*4]
	push dword eax
;R48:	<elemento_vector> ::= <identificador> [ <exp> ]
;D:	=
;D:	false
;R103:	<constante_logica> ::= false
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	;
;R44:	<asignacion> ::= <elemento_vector> = <exp>

	pop dword ebx
	pop dword eax
	mov dword [eax], ebx
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	vector
;D:	[
;D:	1
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 1
;R81:	<exp> ::= <constante>
;D:	]
	;escribir_elemento_vector
	pop dword eax
	cmp eax, 0
	jl near end_index_out_of_range
	cmp eax, 2
	jg near end_index_out_of_range
	mov dword edx, _vector
	lea eax, [edx + eax*4]
	push dword eax
;R48:	<elemento_vector> ::= <identificador> [ <exp> ]
;D:	=
;D:	true
;R102:	<constante_logica> ::= true
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 1
;R81:	<exp> ::= <constante>
;D:	;
;R44:	<asignacion> ::= <elemento_vector> = <exp>

	pop dword ebx
	pop dword eax
	mov dword [eax], ebx
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	vector
;D:	[
;D:	2
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 2
;R81:	<exp> ::= <constante>
;D:	]
	;escribir_elemento_vector
	pop dword eax
	cmp eax, 0
	jl near end_index_out_of_range
	cmp eax, 2
	jg near end_index_out_of_range
	mov dword edx, _vector
	lea eax, [edx + eax*4]
	push dword eax
;R48:	<elemento_vector> ::= <identificador> [ <exp> ]
;D:	=
;D:	false
;R103:	<constante_logica> ::= false
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	;
;R44:	<asignacion> ::= <elemento_vector> = <exp>

	pop dword ebx
	pop dword eax
	mov dword [eax], ebx
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	resultado
;D:	=
;D:	or
;D:	(
;D:	vector
;D:	[
;D:	0
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	]
	;escribir_elemento_vector
	pop dword eax
	cmp eax, 0
	jl near end_index_out_of_range
	cmp eax, 2
	jg near end_index_out_of_range
	mov dword edx, _vector
	lea eax, [edx + eax*4]
	push dword eax
;operandoEnPilaAArgumento
	pop dword eax
	mov dword eax, [eax]
	push dword eax
;R48:	<elemento_vector> ::= <identificador> [ <exp> ]
;R85:	<exp> ::= <elemento_vector>
;D:	,
;D:	vector
;D:	[
;D:	1
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 1
;R81:	<exp> ::= <constante>
;D:	]
	;escribir_elemento_vector
	pop dword eax
	cmp eax, 0
	jl near end_index_out_of_range
	cmp eax, 2
	jg near end_index_out_of_range
	mov dword edx, _vector
	lea eax, [edx + eax*4]
	push dword eax
;operandoEnPilaAArgumento
	pop dword eax
	mov dword eax, [eax]
	push dword eax
;R48:	<elemento_vector> ::= <identificador> [ <exp> ]
;R85:	<exp> ::= <elemento_vector>
;D:	,
;D:	vector
;D:	[
;D:	2
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 2
;R81:	<exp> ::= <constante>
;D:	]
	;escribir_elemento_vector
	pop dword eax
	cmp eax, 0
	jl near end_index_out_of_range
	cmp eax, 2
	jg near end_index_out_of_range
	mov dword edx, _vector
	lea eax, [edx + eax*4]
	push dword eax
;operandoEnPilaAArgumento
	pop dword eax
	mov dword eax, [eax]
	push dword eax
;R48:	<elemento_vector> ::= <identificador> [ <exp> ]
;R85:	<exp> ::= <elemento_vector>
;D:	)
;R92:	<resto_lista_expresiones> ::=
;R91:	<resto_lista_expresiones ::= , <exp> <resto_lista_expresiones>
;R91:	<resto_lista_expresiones ::= , <exp> <resto_lista_expresiones>
;R89:	<lista_expresiones ::= <exp> <resto_lista_expresiones>
	call _or
	add esp, 12
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
	call print_boolean
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
