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
;D:	a
;declarar_variable
	_a resd 1
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	,
;D:	b
;declarar_variable
	_b resd 1
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	,
;D:	c
;declarar_variable
	_c resd 1
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	;
;R18:	<identificadores> ::= <identificador>
;R19:	<identificadores> ::= <identificador> , <identificadores>
;R19:	<identificadores> ::= <identificador> , <identificadores>
;R4:	<declaracion> ::= <clase> <identificadores> ;
;D:	a
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
;D:	false
;R103:	<constante_logica> ::= false
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	;
	pop dword eax
	mov dword [_a], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	b
;D:	=
;D:	true
;R102:	<constante_logica> ::= true
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 1
;R81:	<exp> ::= <constante>
;D:	;
	pop dword eax
	mov dword [_b], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	c
;D:	=
;D:	true
;R102:	<constante_logica> ::= true
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 1
;R81:	<exp> ::= <constante>
;D:	;
	pop dword eax
	mov dword [_c], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	a
;D:	||
;escribir_operando
	push dword _a
;R80:	<exp> ::= <identificador>
;D:	b
;D:	&&
;escribir_operando
	push dword _b
;R80:	<exp> ::= <identificador>
;o

	pop dword ebx
	mov dword ebx, [ebx]
	pop dword eax
	mov dword eax, [eax]
	or eax, ebx
	push dword eax
;R78:	<exp> ::= <exp> || <exp>
;D:	c
;D:	;
;escribir_operando
	push dword _c
;R80:	<exp> ::= <identificador>
	pop dword eax
	pop dword ebx
	mov dword eax, [eax]
	and eax, ebx
	push dword eax
;R77:	<exp> ::= <exp> && <exp>
;R56:	<escritura> ::= printf <exp>
	call print_boolean
	add esp, 4
	call print_endofline
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	(
;D:	a
;D:	||
;escribir_operando
	push dword _a
;R80:	<exp> ::= <identificador>
;D:	b
;D:	)
;escribir_operando
	push dword _b
;R80:	<exp> ::= <identificador>
;o

	pop dword ebx
	mov dword ebx, [ebx]
	pop dword eax
	mov dword eax, [eax]
	or eax, ebx
	push dword eax
;R78:	<exp> ::= <exp> || <exp>
;R82:	<exp> ::= ( <exp> )
;D:	&&
;D:	c
;D:	;
;escribir_operando
	push dword _c
;R80:	<exp> ::= <identificador>
	pop dword eax
	pop dword ebx
	mov dword eax, [eax]
	and eax, ebx
	push dword eax
;R77:	<exp> ::= <exp> && <exp>
;R56:	<escritura> ::= printf <exp>
	call print_boolean
	add esp, 4
	call print_endofline
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	!
;D:	a
;D:	&&
;escribir_operando
	push dword _a
;R80:	<exp> ::= <identificador>
	pop dword ebx
	mov dword ebx, [ebx]
	mov dword eax, 0
	cmp eax, ebx
	je near logic_negation_0
	mov dword eax, 0
	push dword eax
	jmp near no_next_0
logic_negation_0:
	mov dword eax, 1
	push dword eax
no_next_0:
;R79:	<exp> ::= ! <exp>
;D:	b
;D:	&&
;escribir_operando
	push dword _b
;R80:	<exp> ::= <identificador>
	pop dword eax
	pop dword ebx
	mov dword eax, [eax]
	and eax, ebx
	push dword eax
;R77:	<exp> ::= <exp> && <exp>
;D:	!
;D:	c
;D:	;
;escribir_operando
	push dword _c
;R80:	<exp> ::= <identificador>
	pop dword ebx
	mov dword ebx, [ebx]
	mov dword eax, 0
	cmp eax, ebx
	je near logic_negation_1
	mov dword eax, 0
	push dword eax
	jmp near no_next_1
logic_negation_1:
	mov dword eax, 1
	push dword eax
no_next_1:
;R79:	<exp> ::= ! <exp>
	pop dword eax
	pop dword ebx
	and eax, ebx
	push dword eax
;R77:	<exp> ::= <exp> && <exp>
;R56:	<escritura> ::= printf <exp>
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
