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
;D:	z
;declarar_variable
	_z resd 1
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	;
;R18:	<identificadores> ::= <identificador>
;R19:	<identificadores> ::= <identificador> , <identificadores>
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
;D:	scanf
;D:	y
;leer
	push dword _y
	call scan_int
	add esp, 4
;R54:	<lectura> ::= scanf <identificador>
;R35:	<sentencia_simple> ::= <lectura>
;D:	;
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	scanf
;D:	z
;leer
	push dword _z
	call scan_int
	add esp, 4
;R54:	<lectura> ::= scanf <identificador>
;R35:	<sentencia_simple> ::= <lectura>
;D:	;
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	if
;D:	(
;D:	(
;D:	x
;D:	==
;escribir_operando
	push dword _x
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
;D:	&&
;D:	(
;D:	y
;D:	==
;escribir_operando
	push dword _y
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
;D:	&&
	pop dword eax
	pop dword ebx
	and eax, ebx
	push dword eax
;R77:	<exp> ::= <exp> && <exp>
;D:	(
;D:	z
;D:	==
;escribir_operando
	push dword _z
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
	je near igual_2
	mov dword eax, 0
	push dword eax
	jmp near fin_igual_2
igual_2:
	mov dword eax,1
	push dword eax
fin_igual_2:
;R93:	<comparacion> ::= <exp> == <exp>
;R83:	<exp> ::= ( <comparacion> )
;D:	)
	pop dword eax
	pop dword ebx
	and eax, ebx
	push dword eax
;R77:	<exp> ::= <exp> && <exp>
	pop dword eax
	cmp eax, 0
	je near _end_simple_conditional_1
;D:	{
;D:	printf
;D:	0
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	;
;R56:	<escritura> ::= printf <exp>
	call print_int
	add esp, 4
	call print_endofline
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
;D:	else
	jmp near _end_compound_conditional_1
_end_simple_conditional_1:
;D:	{
;D:	if
;D:	(
;D:	(
;D:	x
;D:	>
;escribir_operando
	push dword _x
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
	cmp ebx, eax
	jg near mayor_3
	mov dword ebx, 0
	push dword ebx
	jmp near fin_mayor_3
mayor_3:
	mov dword ebx,1
	push dword ebx
fin_mayor_3:
;R98:	<comparacion> ::= <exp> > <exp>
;R83:	<exp> ::= ( <comparacion> )
;D:	&&
;D:	(
;D:	y
;D:	>
;escribir_operando
	push dword _y
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
	cmp ebx, eax
	jg near mayor_4
	mov dword ebx, 0
	push dword ebx
	jmp near fin_mayor_4
mayor_4:
	mov dword ebx,1
	push dword ebx
fin_mayor_4:
;R98:	<comparacion> ::= <exp> > <exp>
;R83:	<exp> ::= ( <comparacion> )
;D:	)
	pop dword eax
	pop dword ebx
	and eax, ebx
	push dword eax
;R77:	<exp> ::= <exp> && <exp>
	pop dword eax
	cmp eax, 0
	je near _end_simple_conditional_2
;D:	{
;D:	if
;D:	(
;D:	(
;D:	z
;D:	>
;escribir_operando
	push dword _z
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
	cmp ebx, eax
	jg near mayor_5
	mov dword ebx, 0
	push dword ebx
	jmp near fin_mayor_5
mayor_5:
	mov dword ebx,1
	push dword ebx
fin_mayor_5:
;R98:	<comparacion> ::= <exp> > <exp>
;R83:	<exp> ::= ( <comparacion> )
;D:	)
	pop dword eax
	cmp eax, 0
	je near _end_simple_conditional_3
;D:	{
;D:	printf
;D:	1
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 1
;R81:	<exp> ::= <constante>
;D:	;
;R56:	<escritura> ::= printf <exp>
	call print_int
	add esp, 4
	call print_endofline
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
;D:	else
	jmp near _end_compound_conditional_3
_end_simple_conditional_3:
;D:	{
;D:	printf
;D:	5
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 5
;R81:	<exp> ::= <constante>
;D:	;
;R56:	<escritura> ::= printf <exp>
	call print_int
	add esp, 4
	call print_endofline
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
_end_compound_conditional_3:
;R51:	<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }
;R40:	<bloque> ::= <condicional>
;R33:	<sentencia> ::= <bloque>
;D:	}
;R30:	<sentencias> ::= <sentencia>
;D:	if
_end_simple_conditional_2:
;R50:	<condicional> ::= if ( <exp> ) { <sentencias> }
;R40:	<bloque> ::= <condicional>
;R33:	<sentencia> ::= <bloque>
;D:	(
;D:	(
;D:	x
;D:	<
;escribir_operando
	push dword _x
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
	cmp ebx, eax
	jl near menor_6
	mov dword ebx, 0
	push dword ebx
	jmp near fin_menor_6
	menor_6:
	mov dword ebx,1
	push dword ebx
fin_menor_6:
;R97:	<comparacion> ::= <exp> < <exp>
;R83:	<exp> ::= ( <comparacion> )
;D:	&&
;D:	(
;D:	y
;D:	>
;escribir_operando
	push dword _y
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
	cmp ebx, eax
	jg near mayor_7
	mov dword ebx, 0
	push dword ebx
	jmp near fin_mayor_7
mayor_7:
	mov dword ebx,1
	push dword ebx
fin_mayor_7:
;R98:	<comparacion> ::= <exp> > <exp>
;R83:	<exp> ::= ( <comparacion> )
;D:	)
	pop dword eax
	pop dword ebx
	and eax, ebx
	push dword eax
;R77:	<exp> ::= <exp> && <exp>
	pop dword eax
	cmp eax, 0
	je near _end_simple_conditional_4
;D:	{
;D:	if
;D:	(
;D:	(
;D:	z
;D:	>
;escribir_operando
	push dword _z
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
	cmp ebx, eax
	jg near mayor_8
	mov dword ebx, 0
	push dword ebx
	jmp near fin_mayor_8
mayor_8:
	mov dword ebx,1
	push dword ebx
fin_mayor_8:
;R98:	<comparacion> ::= <exp> > <exp>
;R83:	<exp> ::= ( <comparacion> )
;D:	)
	pop dword eax
	cmp eax, 0
	je near _end_simple_conditional_5
;D:	{
;D:	printf
;D:	2
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 2
;R81:	<exp> ::= <constante>
;D:	;
;R56:	<escritura> ::= printf <exp>
	call print_int
	add esp, 4
	call print_endofline
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
;D:	else
	jmp near _end_compound_conditional_5
_end_simple_conditional_5:
;D:	{
;D:	printf
;D:	6
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 6
;R81:	<exp> ::= <constante>
;D:	;
;R56:	<escritura> ::= printf <exp>
	call print_int
	add esp, 4
	call print_endofline
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
_end_compound_conditional_5:
;R51:	<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }
;R40:	<bloque> ::= <condicional>
;R33:	<sentencia> ::= <bloque>
;D:	}
;R30:	<sentencias> ::= <sentencia>
;D:	if
_end_simple_conditional_4:
;R50:	<condicional> ::= if ( <exp> ) { <sentencias> }
;R40:	<bloque> ::= <condicional>
;R33:	<sentencia> ::= <bloque>
;D:	(
;D:	(
;D:	x
;D:	<
;escribir_operando
	push dword _x
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
	cmp ebx, eax
	jl near menor_9
	mov dword ebx, 0
	push dword ebx
	jmp near fin_menor_9
	menor_9:
	mov dword ebx,1
	push dword ebx
fin_menor_9:
;R97:	<comparacion> ::= <exp> < <exp>
;R83:	<exp> ::= ( <comparacion> )
;D:	&&
;D:	(
;D:	y
;D:	<
;escribir_operando
	push dword _y
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
	cmp ebx, eax
	jl near menor_10
	mov dword ebx, 0
	push dword ebx
	jmp near fin_menor_10
	menor_10:
	mov dword ebx,1
	push dword ebx
fin_menor_10:
;R97:	<comparacion> ::= <exp> < <exp>
;R83:	<exp> ::= ( <comparacion> )
;D:	)
	pop dword eax
	pop dword ebx
	and eax, ebx
	push dword eax
;R77:	<exp> ::= <exp> && <exp>
	pop dword eax
	cmp eax, 0
	je near _end_simple_conditional_6
;D:	{
;D:	if
;D:	(
;D:	(
;D:	z
;D:	>
;escribir_operando
	push dword _z
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
	cmp ebx, eax
	jg near mayor_11
	mov dword ebx, 0
	push dword ebx
	jmp near fin_mayor_11
mayor_11:
	mov dword ebx,1
	push dword ebx
fin_mayor_11:
;R98:	<comparacion> ::= <exp> > <exp>
;R83:	<exp> ::= ( <comparacion> )
;D:	)
	pop dword eax
	cmp eax, 0
	je near _end_simple_conditional_7
;D:	{
;D:	printf
;D:	3
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 3
;R81:	<exp> ::= <constante>
;D:	;
;R56:	<escritura> ::= printf <exp>
	call print_int
	add esp, 4
	call print_endofline
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
;D:	else
	jmp near _end_compound_conditional_7
_end_simple_conditional_7:
;D:	{
;D:	printf
;D:	7
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 7
;R81:	<exp> ::= <constante>
;D:	;
;R56:	<escritura> ::= printf <exp>
	call print_int
	add esp, 4
	call print_endofline
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
_end_compound_conditional_7:
;R51:	<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }
;R40:	<bloque> ::= <condicional>
;R33:	<sentencia> ::= <bloque>
;D:	}
;R30:	<sentencias> ::= <sentencia>
;D:	if
_end_simple_conditional_6:
;R50:	<condicional> ::= if ( <exp> ) { <sentencias> }
;R40:	<bloque> ::= <condicional>
;R33:	<sentencia> ::= <bloque>
;D:	(
;D:	(
;D:	x
;D:	>
;escribir_operando
	push dword _x
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
	cmp ebx, eax
	jg near mayor_12
	mov dword ebx, 0
	push dword ebx
	jmp near fin_mayor_12
mayor_12:
	mov dword ebx,1
	push dword ebx
fin_mayor_12:
;R98:	<comparacion> ::= <exp> > <exp>
;R83:	<exp> ::= ( <comparacion> )
;D:	&&
;D:	(
;D:	y
;D:	<
;escribir_operando
	push dword _y
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
	cmp ebx, eax
	jl near menor_13
	mov dword ebx, 0
	push dword ebx
	jmp near fin_menor_13
	menor_13:
	mov dword ebx,1
	push dword ebx
fin_menor_13:
;R97:	<comparacion> ::= <exp> < <exp>
;R83:	<exp> ::= ( <comparacion> )
;D:	)
	pop dword eax
	pop dword ebx
	and eax, ebx
	push dword eax
;R77:	<exp> ::= <exp> && <exp>
	pop dword eax
	cmp eax, 0
	je near _end_simple_conditional_8
;D:	{
;D:	if
;D:	(
;D:	(
;D:	z
;D:	>
;escribir_operando
	push dword _z
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
	cmp ebx, eax
	jg near mayor_14
	mov dword ebx, 0
	push dword ebx
	jmp near fin_mayor_14
mayor_14:
	mov dword ebx,1
	push dword ebx
fin_mayor_14:
;R98:	<comparacion> ::= <exp> > <exp>
;R83:	<exp> ::= ( <comparacion> )
;D:	)
	pop dword eax
	cmp eax, 0
	je near _end_simple_conditional_9
;D:	{
;D:	printf
;D:	4
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 4
;R81:	<exp> ::= <constante>
;D:	;
;R56:	<escritura> ::= printf <exp>
	call print_int
	add esp, 4
	call print_endofline
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
;D:	else
	jmp near _end_compound_conditional_9
_end_simple_conditional_9:
;D:	{
;D:	printf
;D:	8
;R104:	<constante_entera> ::= TOK_CONSTANTE_ENTERA
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 8
;R81:	<exp> ::= <constante>
;D:	;
;R56:	<escritura> ::= printf <exp>
	call print_int
	add esp, 4
	call print_endofline
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
_end_compound_conditional_9:
;R51:	<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }
;R40:	<bloque> ::= <condicional>
;R33:	<sentencia> ::= <bloque>
;D:	}
;R30:	<sentencias> ::= <sentencia>
;D:	}
_end_simple_conditional_8:
;R50:	<condicional> ::= if ( <exp> ) { <sentencias> }
;R40:	<bloque> ::= <condicional>
;R33:	<sentencia> ::= <bloque>
;R30:	<sentencias> ::= <sentencia>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
_end_compound_conditional_1:
;R51:	<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }
;R40:	<bloque> ::= <condicional>
;R33:	<sentencia> ::= <bloque>
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
