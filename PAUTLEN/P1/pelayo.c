#include <stdio.h>
#include <stdlib.h>
#include "generacion.h"

void escribir_cabecera_bss(FILE *fpasm)
{
	fprintf(fpasm, "\nsegment .bss\n\t__esp resd 1");
}

void escribir_subseccion_data(FILE *fpasm)
{
	fprintf(fpasm, "\nsegment .data");
	fprintf(fpasm, "\n\terr_div0 db \"Error al dividir entre 0\",0");
	fprintf(fpasm, "\n\terr_indice_vector db \"Indice de vector fuera de rango 0\", 0");
}

void declarar_variable(FILE *fpasm, char *nombre, int tipo, int tamano)
{
	fprintf(fpasm, "\n\t_%s resd %d", nombre, tamano);
}

void escribir_segmento_codigo(FILE *fpasm)
{
	fprintf(fpasm, "\nsegment .text\n\tglobal main\n\textern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean\n\textern print_endofline, print_blank, print_string\n\textern alfa_malloc, alfa_free, ld_float");
}

void escribir_inicio_main(FILE *fpasm)
{
	fprintf(fpasm, "\nmain:\n\tmov dword [__esp], esp"); //BIEN A FALTA DE PROBAR
}

void escribir_fin(FILE *fpasm)
{
	/* Sentencia necesaria si no ha habido errores en tiempo de ejecucion */
	fprintf(fpasm, "\n\tjmp near fin");

	/* Codigo necesario para gestionar el error de division entre 0 */
	fprintf(fpasm, "\nfin_error_division:");
	fprintf(fpasm, "\n\tpush dword err_div0");
	fprintf(fpasm, "\n\tcall print_string");
	fprintf(fpasm, "\n\tadd esp, 4");
	fprintf(fpasm, "\n\tcall print_endofline");
	fprintf(fpasm, "\n\tjmp near fin");

	/* Código necesario para gestionar el error de indice de vector fuera de rango */
	fprintf(fpasm, "\nfin_indice_fuera_rango:");
	fprintf(fpasm, "\n\tpush dword err_indice_vector");
	fprintf(fpasm, "\n\tcall print_string");
	fprintf(fpasm, "\n\tadd esp, 4");
	fprintf(fpasm, "\n\tcall print_endofline");
	fprintf(fpasm, "\n\tjmp near fin");

	/* Etiqueta de fin */
	fprintf(fpasm, "\nfin:");
	fprintf(fpasm, "\n\tmov esp, [__esp]");
	fprintf(fpasm, "\n\tret");
}

void escribir_operando(FILE *fpasm, char *nombre, int es_variable)
{
	if (es_variable == 1)
	{
		fprintf(fpasm, "\n\tpush dword _%s", nombre);
	}
	else
	{
		fprintf(fpasm, "\n\tpush dword %s", nombre);
	}
}

void asignar(FILE *fpasm, char *nombre, int es_variable)
{
	fprintf(fpasm, "\n\tpop dword eax");
	if (es_variable == 1)
	{
		fprintf(fpasm, "\n\tmov dword eax, [eax]");
	}
	fprintf(fpasm, "\n\tmov dword [_%s], eax", nombre);
}

void sumar(FILE *fpasm, int es_variable_1, int es_variable_2)
{
	fprintf(fpasm, "\n\tpop dword ebx");
	fprintf(fpasm, "\n\tpop dword eax");

	if (es_variable_1 == 1)
	{
		fprintf(fpasm, "\n\tmov dword eax, [eax]");
	}

	if (es_variable_2 == 1)
	{
		fprintf(fpasm, "\n\tmov dword ebx, [ebx]");
	}

	fprintf(fpasm, "\n\tadd eax, ebx");
	fprintf(fpasm, "\n\tpush dword eax");
}
void restar(FILE *fpasm, int es_variable_1, int es_variable_2)
{
	fprintf(fpasm, "\n\tpop dword ebx");
	fprintf(fpasm, "\n\tpop dword eax");

	if (es_variable_1 == 1)
	{
		fprintf(fpasm, "\n\tmov dword eax, [eax]");
	}

	if (es_variable_2 == 1)
	{
		fprintf(fpasm, "\n\tmov dword ebx, [ebx]");
	}

	fprintf(fpasm, "\n\tsub eax, ebx");
	fprintf(fpasm, "\n\tpush dword eax");
}
void multiplicar(FILE *fpasm, int es_variable_1, int es_variable_2)
{
	fprintf(fpasm, "\n\tpop dword ebx");
	fprintf(fpasm, "\n\tpop dword eax");

	if (es_variable_1 == 1)
	{
		fprintf(fpasm, "\n\tmov dword eax, [eax]");
	}

	if (es_variable_2 == 1)
	{
		fprintf(fpasm, "\n\tmov dword ebx, [ebx]");
	}

	fprintf(fpasm, "\n\timul ebx");
	fprintf(fpasm, "\n\tpush dword eax");
}
void dividir(FILE *fpasm, int es_variable_1, int es_variable_2)
{
	fprintf(fpasm, "\n\tpop dword ebx");
	fprintf(fpasm, "\n\tpop dword eax");

	if (es_variable_1 == 1)
	{
		fprintf(fpasm, "\n\tmov dword eax, [eax]");
	}

	if (es_variable_2 == 1)
	{
		fprintf(fpasm, "\n\tmov dword ebx, [ebx]");
	}

	fprintf(fpasm, "\n\tmov dword edx, 0");
	fprintf(fpasm, "\n\tcmp ebx, edx");
	fprintf(fpasm, "\n\tje near fin_error_division");

	fprintf(fpasm, "\n\tidiv ebx");
	fprintf(fpasm, "\n\tpush dword eax");
}
void o(FILE *fpasm, int es_variable_1, int es_variable_2)
{
	fprintf(fpasm, "\n\tpop dword ebx");
	fprintf(fpasm, "\n\tpop dword eax");

	if (es_variable_1 == 1)
	{
		fprintf(fpasm, "\n\tmov dword eax, [eax]");
	}

	if (es_variable_2 == 1)
	{
		fprintf(fpasm, "\n\tmov dword ebx, [ebx]");
	}

	fprintf(fpasm, "\n\tor eax, ebx");
	fprintf(fpasm, "\n\tpush dword eax");
}
void y(FILE *fpasm, int es_variable_1, int es_variable_2)
{
	fprintf(fpasm, "\n\tpop dword ebx");
	fprintf(fpasm, "\n\tpop dword eax");

	if (es_variable_1 == 1)
	{
		fprintf(fpasm, "\n\tmov dword eax, [eax]");
	}

	if (es_variable_2 == 1)
	{
		fprintf(fpasm, "\n\tmov dword ebx, [ebx]");
	}

	fprintf(fpasm, "\n\tand eax, ebx");
	fprintf(fpasm, "\n\tpush dword eax");
}

void cambiar_signo(FILE *fpasm, int es_variable)
{
	fprintf(fpasm, "\n\tpop dword eax");

	if (es_variable == 1)
	{
		fprintf(fpasm, "\n\tmov dword eax, [eax]");
	}

	fprintf(fpasm, "\n\tneg eax");
	fprintf(fpasm, "\n\tpush dword eax");
}

void no(FILE *fpasm, int es_variable, int cuantos_no)
{

	fprintf(fpasm, "\n\tpop dword ecx");

	if (es_variable == 1)
	{
		fprintf(fpasm, "\n\tmov dword ecx, [ecx]");
	}

	fprintf(fpasm, "\n\tmov dword eax, 0");
	fprintf(fpasm, "\n\tcmp eax, ecx");
	fprintf(fpasm, "\n\tje near positivo_negativo%d", cuantos_no);

	fprintf(fpasm, "\n\tmov dword eax, 0");
	fprintf(fpasm, "\n\tpush dword eax");
	fprintf(fpasm, "\n\tjmp near continua_%d", cuantos_no);

	fprintf(fpasm, "\npositivo_negativo%d:", cuantos_no);
	fprintf(fpasm, "\n\tmov dword eax, 1");
	fprintf(fpasm, "\n\tpush dword eax");

	fprintf(fpasm, "\ncontinua_%d:", cuantos_no);
}

void igual(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{

	fprintf(fpasm, "\n\tpop dword ecx\n\tpop dword eax");

	if (es_variable1 == 1)
	{
		fprintf(fpasm, "\n\tmov dword eax, [eax]");
	}

	if (es_variable2 == 1)
	{
		fprintf(fpasm, "\n\tmov dword ecx, [ecx]");
	}

	fprintf(fpasm, "\n\tcmp eax,ecx");
	fprintf(fpasm, "\n\tjz near true_igual_%d", etiqueta);

	fprintf(fpasm, "\n\tmov dword eax, 0");
	fprintf(fpasm, "\n\tpush dword eax");
	fprintf(fpasm, "\n\tjmp near continua_igual_%d", etiqueta);

	fprintf(fpasm, "\ntrue_igual_%d:", etiqueta);
	fprintf(fpasm, "\n\tmov dword eax,1");
	fprintf(fpasm, "\n\tpush dword eax");

	fprintf(fpasm, "\ncontinua_igual_%d:", etiqueta);
}

void distinto(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
	fprintf(fpasm, "\n\tpop dword ecx\n\tpop dword eax");

	if (es_variable1 == 1)
	{
		fprintf(fpasm, "\n\tmov dword eax, [eax]");
	}

	if (es_variable2 == 1)
	{
		fprintf(fpasm, "\n\tmov dword ecx, [ecx]");
	}

	fprintf(fpasm, "\n\tcmp eax,ecx");
	fprintf(fpasm, "\n\tjnz near true_distinto_%d", etiqueta);

	fprintf(fpasm, "\n\tmov dword eax, 0");
	fprintf(fpasm, "\n\tpush dword eax");
	fprintf(fpasm, "\n\tjmp near continua_distinto_%d", etiqueta);

	fprintf(fpasm, "\ntrue_distinto_%d:", etiqueta);
	fprintf(fpasm, "\n\tmov dword eax,1");
	fprintf(fpasm, "\n\tpush dword eax");

	fprintf(fpasm, "\ncontinua_distinto_%d:", etiqueta);
}

void menor_igual(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
	fprintf(fpasm, "\n\tpop dword ecx\n\tpop dword eax");

	if (es_variable1 == 1)
	{
		fprintf(fpasm, "\n\tmov dword eax, [eax]");
	}

	if (es_variable2 == 1)
	{
		fprintf(fpasm, "\n\tmov dword ecx, [ecx]");
	}

	fprintf(fpasm, "\n\tcmp eax,ecx");
	fprintf(fpasm, "\n\tjle near true_menor_igual_%d", etiqueta);

	fprintf(fpasm, "\n\tmov dword eax, 0");
	fprintf(fpasm, "\n\tpush dword eax");
	fprintf(fpasm, "\n\tjmp near continua_menor_igual_%d", etiqueta);

	fprintf(fpasm, "\ntrue_menor_igual_%d:", etiqueta);
	fprintf(fpasm, "\n\tmov dword eax,1");
	fprintf(fpasm, "\n\tpush dword eax");

	fprintf(fpasm, "\ncontinua_menor_igual_%d:", etiqueta);
}

void mayor_igual(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
	fprintf(fpasm, "\n\tpop dword ecx\n\tpop dword eax");

	if (es_variable1 == 1)
	{
		fprintf(fpasm, "\n\tmov dword eax, [eax]");
	}

	if (es_variable2 == 1)
	{
		fprintf(fpasm, "\n\tmov dword ecx, [ecx]");
	}

	fprintf(fpasm, "\n\tcmp eax,ecx");
	fprintf(fpasm, "\n\tjge near true_mayor_igual_%d", etiqueta);

	fprintf(fpasm, "\n\tmov dword eax, 0");
	fprintf(fpasm, "\n\tpush dword eax");
	fprintf(fpasm, "\n\tjmp near continua_mayor_igual_%d", etiqueta);

	fprintf(fpasm, "\ntrue_mayor_igual_%d:", etiqueta);
	fprintf(fpasm, "\n\tmov dword eax,1");
	fprintf(fpasm, "\n\tpush dword eax");

	fprintf(fpasm, "\ncontinua_mayor_igual_%d:", etiqueta);
}

void menor(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
	fprintf(fpasm, "\n\tpop dword ecx\n\tpop dword eax");

	if (es_variable1 == 1)
	{
		fprintf(fpasm, "\n\tmov dword eax, [eax]");
	}

	if (es_variable2 == 1)
	{
		fprintf(fpasm, "\n\tmov dword ecx, [ecx]");
	}

	fprintf(fpasm, "\n\tcmp eax,ecx");
	fprintf(fpasm, "\n\tjl near true_menor_%d", etiqueta);

	fprintf(fpasm, "\n\tmov dword eax, 0");
	fprintf(fpasm, "\n\tpush dword eax");
	fprintf(fpasm, "\n\tjmp near continua_menor_%d", etiqueta);

	fprintf(fpasm, "\ntrue_menor_%d:", etiqueta);
	fprintf(fpasm, "\n\tmov dword eax,1");
	fprintf(fpasm, "\n\tpush dword eax");

	fprintf(fpasm, "\ncontinua_menor_%d:", etiqueta);
}

void mayor(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
	fprintf(fpasm, "\n\tpop dword ecx\n\tpop dword eax");

	if (es_variable1 == 1)
	{
		fprintf(fpasm, "\n\tmov dword eax, [eax]");
	}

	if (es_variable2 == 1)
	{
		fprintf(fpasm, "\n\tmov dword ecx, [ecx]");
	}

	fprintf(fpasm, "\n\tcmp eax,ecx");
	fprintf(fpasm, "\n\tjg near true_mayor_%d", etiqueta);

	fprintf(fpasm, "\n\tmov dword eax, 0");
	fprintf(fpasm, "\n\tpush dword eax");
	fprintf(fpasm, "\n\tjmp near continua_mayor_%d", etiqueta);

	fprintf(fpasm, "\ntrue_mayor_%d:", etiqueta);
	fprintf(fpasm, "\n\tmov dword eax,1");
	fprintf(fpasm, "\n\tpush dword eax");

	fprintf(fpasm, "\ncontinua_mayor_%d:", etiqueta);
}

void leer(FILE *fpasm, char *nombre, int tipo)
{

	fprintf(fpasm, "\n\tpush dword _%s", nombre);

	if (tipo == ENTERO)
	{
		fprintf(fpasm, "\n\tcall scan_int");
	}
	else
	{
		fprintf(fpasm, "\n\tcall scan_boolean");
	}

	fprintf(fpasm, "\n\tadd esp, 4");
}

void escribir(FILE *fpasm, int es_variable, int tipo)
{

	if (es_variable == 1)
	{
		fprintf(fpasm, "\n\tpop dword eax");
		fprintf(fpasm, "\n\tmov dword eax, [eax]");
		fprintf(fpasm, "\n\tpush dword eax");
	}

	if (tipo == ENTERO)
	{
		fprintf(fpasm, "\n\tcall print_int");
	}
	else
	{
		fprintf(fpasm, "\n\tcall print_boolean");
	}

	fprintf(fpasm, "\n\tadd esp, 4");
	fprintf(fpasm, "\n\tcall print_endofline");
}

void ifthen_inicio(FILE *fpasm, int exp_es_variable, int etiqueta)
{
	fprintf(fpasm, "\n\tpop dword eax");
	if (exp_es_variable == 1)
	{
		fprintf(fpasm, "\n\tmov dword eax, [eax]");
	}

	fprintf(fpasm, "\n\tcmp eax, 0");
	fprintf(fpasm, "\n\tje near _fin_condicional_simple_%d", etiqueta);
}

void ifthenelse_inicio(FILE *fpasm, int exp_es_variable, int etiqueta)
{
	fprintf(fpasm, "\n\tpop dword eax");
	if (exp_es_variable == 1)
	{
		fprintf(fpasm, "\n\tmov dword eax, [eax]");
	}

	fprintf(fpasm, "\n\tcmp eax, 0");
	fprintf(fpasm, "\n\tje near _fin_condicional_simple_%d", etiqueta);
}

void ifthen_fin(FILE *fpasm, int etiqueta)
{
	fprintf(fpasm, "\n_fin_condicional_simple_%d:", etiqueta); //FIN del THEN
}

void ifthenelse_fin_then(FILE *fpasm, int etiqueta)
{
	fprintf(fpasm, "\n\tjmp near _fin_condicional_compuesto_%d", etiqueta);
	fprintf(fpasm, "\n_fin_condicional_simple_%d:", etiqueta);
}

void ifthenelse_fin(FILE *fpasm, int etiqueta)
{ //FIN DE CUALQUIER THEN CON ELSE INCLUIDO
	fprintf(fpasm, "\n_fin_condicional_compuesto_%d:", etiqueta);
}

void while_inicio(FILE *fpasm, int etiqueta)
{
	fprintf(fpasm, "\n_inicio_bucle_%d:", etiqueta);
}

void while_exp_pila(FILE *fpasm, int exp_es_variable, int etiqueta)
{
	fprintf(fpasm, "\n\tpop dword eax");
	if (exp_es_variable == 1)
	{
		fprintf(fpasm, "\n\tmov eax, [eax]");
	}

	fprintf(fpasm, "\n\tcmp eax, 0");
	fprintf(fpasm, "\n\tje near _fin_bucle_%d", etiqueta);
}

void while_fin(FILE *fpasm, int etiqueta)
{
	fprintf(fpasm, "\n\tjmp near _inicio_bucle_%d", etiqueta);
	fprintf(fpasm, "\n_fin_bucle_%d:", etiqueta);
}

void escribir_elemento_vector(FILE *fpasm, char *nombre_vector, int tam_max, int exp_es_direccion)
{
	fprintf(fpasm, "\n\tpop dword eax");

	if (exp_es_direccion == 1)
	{
		fprintf(fpasm, "\n\tmov dword eax, [eax]");
	}

	fprintf(fpasm, "\n\tcmp eax, 0");
	fprintf(fpasm, "\n\tjl near fin_indice_fuera_rango");

	fprintf(fpasm, "\n\tcmp eax, %d", tam_max - 1);
	fprintf(fpasm, "\n\tjg near fin_indice_fuera_rango");

	fprintf(fpasm, "\n\tmov dword edx, _%s", nombre_vector);
	fprintf(fpasm, "\n\tlea eax, [edx + eax*4]");
	fprintf(fpasm, "\n\tpush dword eax");
}

void declararFuncion(FILE *fd_asm, char *nombre_funcion, int num_var_loc)
{
	fprintf(fd_asm, "\n%s:", nombre_funcion);
	fprintf(fd_asm, "\n\tpush dword ebp");
	fprintf(fd_asm, "\n\tmov dword ebp, esp");
	fprintf(fd_asm, "\n\tsub esp, %d", 4 * num_var_loc);
}

void retornarFuncion(FILE *fd_asm, int es_variable)
{
	fprintf(fd_asm, "\n\tpop dword eax");
	if (es_variable == 1)
	{
		fprintf(fd_asm, "\n\tmov dword eax, [eax]");
	}

	fprintf(fd_asm, "\n\tmov dword esp, ebp");
	fprintf(fd_asm, "\n\tpop dword ebp");
	fprintf(fd_asm, "\n\tret");
}

void escribirParametro(FILE *fpasm, int pos_parametro, int num_total_parametros)
{
	int aux = 0;
	aux = 4 * (1 + (num_total_parametros - pos_parametro));
	fprintf(fpasm, "\n\tlea eax, [ebp + %d]", aux);
	fprintf(fpasm, "\n\tpush dword eax");
}

void escribirVariableLocal(FILE *fpasm, int posicion_variable_local)
{
	int aux = 0;
	aux = 4 * posicion_variable_local;
	fprintf(fpasm, "\n\tlea eax, [ebp - %d]", aux);
	fprintf(fpasm, "\n\tpush dword eax");
}

void asignarDestinoEnPila(FILE *fpasm, int es_variable)
{
	fprintf(fpasm, "\n\tpop dword ebx"); //direccion
	fprintf(fpasm, "\n\tpop dword eax"); //Valor de la cima, que corresponde lo que vamos a asignar
	if (es_variable == 1)
	{
		fprintf(fpasm, "\n\tmov dword eax, [eax]");
	}

	fprintf(fpasm, "\n\tmov dword [ebx], eax");
}

void operandoEnPilaAArgumento(FILE *fd_asm, int es_variable)
{
	if (es_variable == 1)
	{
		fprintf(fd_asm, "\n\tpop dword eax");
		fprintf(fd_asm, "\n\tmov dword eax, [eax]");
		fprintf(fd_asm, "\n\tpush dword eax");
	}
}

void llamarFuncion(FILE *fd_asm, char *nombre_funcion, int num_argumentos)
{
	fprintf(fd_asm, "\n\tcall %s", nombre_funcion);
	fprintf(fd_asm, "\n\tadd esp, %d", 4 * num_argumentos);
	fprintf(fd_asm, "\n\tpush dword eax");
}

void limpiarPila(FILE *fd_asm, int num_argumentos)
{
	fprintf(fd_asm, "\n\tadd esp, %d", 4 * num_argumentos);