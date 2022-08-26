/********************************************
 * 
 *  Authors: Santiaga Atria Rodríguez,
 *           Lucía Gil Maroto,
 *           Daniel Varela Sanchez,
 *           Javier López de el Nieta
 * 
 *  Prctice 1 PAUTLEN
 * 
 *  Submision Date: 18/10/2021 before 9:00am
 *
 * ******************************************/

#include <stdio.h>
#include "generacion.h"

void escribir_cabecera_bss(FILE *fpasm)
{
    if (fpasm == NULL)
        return;
    
    fprintf(fpasm, ";escribir_cabecera_bss\n");
    fprintf(fpasm, "\nsegment .bss\n\t__esp resd 1\n");

    return;
}
/*
Código para el principio de la sección .bss.
Con seguridad sabes que deberás reservar una variable entera para guardar el
puntero de pila extendido (esp). Se te sugiere el nombre __esp para esta variable.
*/

void escribir_subseccion_data(FILE *fpasm)
{
    if (fpasm == NULL)
        return;
    
    fprintf(fpasm, ";escribir_subseccion_data");
    fprintf(fpasm, "\nsegment .data\n\t_err_divZ db \"ERROR. The divisor can't be 0\", 0\n");
    fprintf(fpasm, "\terr_index_out_of_range db \"ERROR. The index is out of range 0\", 0\n");

    return;
}
/*
Declaración (con directiva db) de las variables que contienen el texto de los
mensajes para la identificación de errores en tiempo de ejecución.
En este punto, al menos, debes ser capaz de detectar la división por 0.
*/

void declarar_variable(FILE *fpasm, char *nombre, int tipo, int tamano)
{
    if (fpasm == NULL || nombre == NULL || tamano < 0 || tipo < 0) {
        fprintf(fpasm, "Error al pasar vairables a 'declarar_variable'\nNombre: %s\nTipo: %d\nTamano: %d", nombre, tipo, tamano);
        return;
    }
    fprintf(fpasm, ";declarar_variable\n");
    fprintf(fpasm, "\t_%s resd %d\n", nombre, tamano);
    return;
}
/*
Para ser invocada en la sección .bss cada vez que se quiera declarar una
variable:
- El argumento nombre es el de la variable.
- tipo puede ser ENTERO o BOOLEANO (observa la declaración de las constantes
del principio del fichero).
- Esta misma función se invocará cuando en el compilador se declaren
vectores, por eso se adjunta un argumento final (tamano) que para esta
primera práctica siempre recibirá el valor 1.
*/

void escribir_segmento_codigo(FILE *fpasm)
{
    if (fpasm == NULL)
        return;

    fprintf(fpasm, ";escribir_segmento_codigo\n");
    fprintf(fpasm, "segment .text\n\tglobal main\n\textern malloc, free\n\textern scan_int, print_int, scan_boolean, print_boolean\n\textern print_endofline, print_blank, print_string\n");
}
/*
Para escribir el comienzo del segmento .text, básicamente se indica que se
exporta la etiqueta main y que se usarán las funciones declaradas en la librería
alfalib.o
*/

void escribir_inicio_main(FILE *fpasm)
{
    if (fpasm == NULL)
        return;

    fprintf(fpasm, ";escribir_inicio_main\n; -----------------------\n; PROCEDIMIENTO PRINCIPAL\nmain:\n\tmov dword [__esp], esp\n");
}
/*
En este punto se debe escribir, al menos, la etiqueta main y la sentencia que
guarda el puntero de pila en su variable (se recomienda usar __esp).
*/

void escribir_fin(FILE *fpasm)
{
    if (fpasm == NULL)
        return;

    /*We jump to the end function when the program reaches its end successfully*/
    fprintf(fpasm, "\tjmp end_program");

    /*We print the error and end the program when the division cant be made*/
    fprintf(fpasm, "\n_division_error:\n\tpush dword _err_divZ\n\tcall print_string\n\tadd esp, 4\n\tcall print_endofline\n\tjmp end_program");

    /* Necessary code to manage the vector error index out of range */
    fprintf(fpasm, "\nend_index_out_of_range:\n\tpush dword err_index_out_of_range\n\tcall print_string\n\tadd esp, 4\n\tcall print_endofline\n\tjmp near end_program");

    /*Function that defines the behaviour of the end of program*/
    fprintf(fpasm, "\nend_program:\n\tmov esp, [__esp]\n\tret\n");
}
/*
Al final del programa se escribe:
- El código NASM para salir de manera controlada cuando se detecta un error
en tiempo de ejecución (cada error saltará a una etiqueta situada en esta
zona en la que se imprimirá el correspondiente mensaje y se saltará a la
zona de finalización del programa).
- En el final del programa se debe:
·Restaurar el valor del puntero de pila (a partir de su variable __esp)
·Salir del programa (ret).
*/

void escribir_operando(FILE *fpasm, char *nombre, int es_variable)
{
    if (fpasm == NULL || nombre == NULL)
        return;

    if (es_variable == 1)
    {
        fprintf(fpasm, ";escribir_operando");
        fprintf(fpasm, "\n\tpush dword _%s\n", nombre);
    }
    else
    {
        fprintf(fpasm, ";escribir_operando");
        fprintf(fpasm, "\n\tpush dword %s\n", nombre);
    }

    return;
}
/*
Función que debe ser invocada cuando se sabe un operando de una operación
aritmético-lógica y se necesita introducirlo en la pila.
- nombre es la cadena de caracteres del operando tal y como debería aparecer
en el fuente NASM
- es_variable indica si este operando es una variable (como por ejemplo b1)
con un 1 u otra cosa (como por ejemplo 34) con un 0. Recuerda que en el
primer caso internamente se representará como _b1 y, sin embargo, en el
segundo se representará tal y como esté en el argumento (34).
*/

void asignar(FILE *fpasm, char *nombre, int es_variable)
{

    if (fpasm == NULL || nombre == NULL || es_variable < 0 || es_variable > 1)
        return;

    fprintf(fpasm, "\tpop dword eax");

    if (es_variable == 1)
    {
        fprintf(fpasm, "\n\tmov dword eax, [eax]");
    }

    fprintf(fpasm, "\n\tmov dword [_%s], eax\n", nombre);

    return;
}
/*
- Genera el código para asignar valor a la variable de nombre nombre.
- Se toma el valor de la cima de la pila.
- El último argumento es el que indica si lo que hay en la cima de la pila es
una referencia (1) o ya un valor explícito (0).
*/

/* FUNCIONES ARITMÉTICO-LÓGICAS BINARIAS */
/*
En todas ellas se realiza la operación como se ha resumido anteriormente:
- Se extrae de la pila los operandos
- Se realiza la operación

Los dos últimos argumentos indican respectivamente si lo que hay en la pila es
una referencia a un valor o un valor explícito.

Deben tenerse en cuenta las peculiaridades de cada operación. En este sentido
sí hay que mencionar explícitamente que, en el caso de la división, se debe
controlar si el divisor es “0” y en ese caso se debe saltar a la rutina de error
controlado (restaurando el puntero de pila en ese caso y comprobando en el retorno
que no se produce “Segmentation Fault”)
*/
void sumar(FILE *fpasm, int es_variable_1, int es_variable_2)
{
    if (fpasm == NULL || es_variable_1 < 0 || es_variable_1 > 1 || es_variable_2 < 0 || es_variable_2 > 1)
        return;

    fprintf(fpasm, "\tpop dword eax"); /*second operand in eax, pops the element at the top of the stack*/
    fprintf(fpasm, "\n\tpop dword ebx"); /*first operandd in ebx, pops the element that is now at the top of the stack*/

    if (es_variable_1 == 1)
    {
        fprintf(fpasm, "\n\tmov dword ebx, [ebx]");
    }
    if (es_variable_2 == 1)
    {
        fprintf(fpasm, "\n\tmov dword eax, [eax]");
    }

    fprintf(fpasm, "\n\tadd eax, ebx\n\tpush dword eax\n");
}
void restar(FILE *fpasm, int es_variable_1, int es_variable_2)
{

    if (fpasm == NULL || es_variable_1 < 0 || es_variable_1 > 1 || es_variable_2 < 0 || es_variable_2 > 1)
        return;

    fprintf(fpasm, "\tpop dword eax"); /*second operand in eax, pops the element at the top of the stack*/
    fprintf(fpasm, "\n\tpop dword ebx"); /*first operandd in ebx, pops the element that is now at the top of the stack*/

    if (es_variable_1 == 1)
    {
        fprintf(fpasm, "\n\tmov dword ebx, [ebx]");
    }
    if (es_variable_2 == 1)
    {
        fprintf(fpasm, "\n\tmov dword eax, [eax]");
    }

    fprintf(fpasm, "\n\tsub ebx, eax\n\tpush dword ebx\n");
}

void multiplicar(FILE *fpasm, int es_variable_1, int es_variable_2)
{
    if (fpasm == NULL || es_variable_1 < 0 || es_variable_1 > 1 || es_variable_2 < 0 || es_variable_2 > 1)
        return;

    fprintf(fpasm, "\tpop dword eax"); /*second operand in eax, pops the element at the top of the stack*/
    fprintf(fpasm, "\n\tpop dword ebx"); /*first operandd in ebx, pops the element that is now at the top of the stack*/

    if (es_variable_1 == 1)
    {
        fprintf(fpasm, "\n\tmov dword ebx, [ebx]");
    }
    if (es_variable_2 == 1)
    {
        fprintf(fpasm, "\n\tmov dword eax, [eax]");
    }

    fprintf(fpasm, "\n\timul ebx\n\tpush dword eax\n");
}

void dividir(FILE *fpasm, int es_variable_1, int es_variable_2)
{
    if (fpasm == NULL || es_variable_1 < 0 || es_variable_1 > 1 || es_variable_2 < 0 || es_variable_2 > 1)
        return;

    fprintf(fpasm, "\tpop dword ebx"); /*first operandd in ebx, pops the element that is now at the top of the stack*/
    fprintf(fpasm, "\n\tpop dword eax"); /*second operand in eax, pops the element at the top of the stack*/

    if (es_variable_1 == 1)
    {
        fprintf(fpasm, "\n\tmov dword eax, [eax]");
    }
    if (es_variable_2 == 1)
    {
        fprintf(fpasm, "\n\tmov dword ebx, [ebx]");
    }
    
    fprintf(fpasm, "\n\tmov dword edx, 0");
    fprintf(fpasm, "\n\tcmp ebx, edx\n\tje near _division_error");
    fprintf(fpasm, "\n\tidiv ebx\n\tpush dword eax\n");
}

void o(FILE *fpasm, int es_variable_1, int es_variable_2)
{
    if (fpasm == NULL || es_variable_1 < 0 || es_variable_1 > 1 || es_variable_2 < 0 || es_variable_2 > 1)
        return;

    fprintf(fpasm, ";o\n");
    fprintf(fpasm, "\n\tpop dword ebx"); /*first operandd in ebx, pops the element that is now at the top of the stack*/

    if (es_variable_2 == 1)
    {
        fprintf(fpasm, "\n\tmov dword ebx, [ebx]");
    }

    fprintf(fpasm, "\n\tpop dword eax"); /*second operand in eax, pops the element at the top of the stack*/

    if (es_variable_1 == 1)
    {
        fprintf(fpasm, "\n\tmov dword eax, [eax]");
    }

    fprintf(fpasm, "\n\tor eax, ebx");
    fprintf(fpasm, "\n\tpush dword eax\n");
}
void y(FILE *fpasm, int es_variable_1, int es_variable_2)
{
    if (fpasm == NULL || es_variable_1 < 0 || es_variable_1 > 1 || es_variable_2 < 0 || es_variable_2 > 1)
        return;

    fprintf(fpasm, "\tpop dword eax"); /*second operand in eax, pops the element at the top of the stack*/
    fprintf(fpasm, "\n\tpop dword ebx"); /*first operandd in ebx, pops the element that is now at the top of the stack*/

    if (es_variable_1 == 1)
    {
        fprintf(fpasm, "\n\tmov dword ebx, [ebx]");
    }

    if (es_variable_2 == 1)
    {
        fprintf(fpasm, "\n\tmov dword eax, [eax]");
    }

    fprintf(fpasm, "\n\tand eax, ebx");
    fprintf(fpasm, "\n\tpush dword eax\n");
}
void cambiar_signo(FILE *fpasm, int es_variable)
{
    if (fpasm == NULL || es_variable < 0 || es_variable > 1)
        return;

    fprintf(fpasm, "\tpop dword eax");

    if (es_variable == 1)
    {
        fprintf(fpasm, "\n\tmov dword eax, [eax]");
    }

    fprintf(fpasm, "\n\tneg eax");
    fprintf(fpasm, "\n\tpush dword eax\n");
}
/*
Función aritmética de cambio de signo.
Es análoga a las binarias, excepto que sólo requiere de un acceso a la pila ya
que sólo usa un operando.
*/
void no(FILE *fpasm, int es_variable, int cuantos_no)
{
    if (fpasm == NULL || es_variable < 0 || es_variable > 1 || cuantos_no < 0)
        return;

    fprintf(fpasm, "\tpop dword ebx");

    if (es_variable == 1)
    {
        fprintf(fpasm, "\n\tmov dword ebx, [ebx]");
    }

    fprintf(fpasm, "\n\tmov dword eax, 0");
    fprintf(fpasm, "\n\tcmp eax, ebx");
    fprintf(fpasm, "\n\tje near logic_negation_%d", cuantos_no);

    fprintf(fpasm, "\n\tmov dword eax, 0");
    fprintf(fpasm, "\n\tpush dword eax");
    fprintf(fpasm, "\n\tjmp near no_next_%d", cuantos_no);

    fprintf(fpasm, "\nlogic_negation_%d:", cuantos_no);
    fprintf(fpasm, "\n\tmov dword eax, 1");
    fprintf(fpasm, "\n\tpush dword eax");

    fprintf(fpasm, "\nno_next_%d:\n", cuantos_no);
}
/*
Función monádica lógica de negación. No hay un código de operación de la ALU
que realice esta operación por lo que se debe codificar un algoritmo que, si
encuentra en la cima de la pila un 0 deja en la cima un 1 y al contrario.
El último argumento es el valor de etiqueta que corresponde (sin lugar a dudas,
la implementación del algoritmo requerirá etiquetas). Véase en los ejemplos de
programa principal como puede gestionarse el número de etiquetas cuantos_no.
*/

/* FUNCIONES COMPARATIVAS */
/*
Todas estas funciones reciben como argumento si los elementos a comparar son o
no variables. El resultado de las operaciones, que siempre será un booleano (“1”
si se cumple la comparación y “0” si no se cumple), se deja en la pila como en el
resto de operaciones. Se deben usar etiquetas para poder gestionar los saltos
necesarios para implementar las comparaciones.
*/
void igual(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    if (fpasm == NULL || es_variable1 < 0 || es_variable1 > 1 || es_variable2 < 0 || es_variable2 > 1)
        return;

    fprintf(fpasm, "\tpop dword eax"); /*second operand in eax, pops the element at the top of the stack*/
    fprintf(fpasm, "\n\tpop dword ebx"); /*first operandd in ebx, pops the element that is now at the top of the stack*/

    if (es_variable1 == 1)
    {
        fprintf(fpasm, "\n\tmov dword ebx, [ebx]");
    }
    if (es_variable2 == 1)
    {
        fprintf(fpasm, "\n\tmov dword eax, [eax]");
    }

    fprintf(fpasm, "\n\tcmp eax, ebx");
    fprintf(fpasm, "\n\tje near igual_%d", etiqueta);

    fprintf(fpasm, "\n\tmov dword eax, 0");
    fprintf(fpasm, "\n\tpush dword eax");
    fprintf(fpasm, "\n\tjmp near fin_igual_%d", etiqueta);

    fprintf(fpasm, "\nigual_%d:", etiqueta);
    fprintf(fpasm, "\n\tmov dword eax,1");
    fprintf(fpasm, "\n\tpush dword eax");

    fprintf(fpasm, "\nfin_igual_%d:\n", etiqueta);
}

void distinto(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    if (fpasm == NULL || es_variable1 < 0 || es_variable1 > 1 || es_variable2 < 0 || es_variable2 > 1)
        return;
    fprintf(fpasm, "\tpop dword eax"); /*second operand in eax, pops the element at the top of the stack*/
    fprintf(fpasm, "\n\tpop dword ebx"); /*first operandd in ebx, pops the element that is now at the top of the stack*/

    if (es_variable1 == 1)
    {
        fprintf(fpasm, "\n\tmov dword ebx, [ebx]");
    }
    if (es_variable2 == 1)
    {
        fprintf(fpasm, "\n\tmov dword eax, [eax]");
    }

    fprintf(fpasm, "\n\tcmp eax, ebx");
    fprintf(fpasm, "\n\tjnz near distinto_%d", etiqueta);

    fprintf(fpasm, "\n\tmov dword eax, 0");
    fprintf(fpasm, "\n\tpush dword eax");
    fprintf(fpasm, "\n\tjmp near fin_distinto_%d", etiqueta);

    fprintf(fpasm, "\ndistinto_%d:", etiqueta);
    fprintf(fpasm, "\n\tmov dword eax,1");
    fprintf(fpasm, "\n\tpush dword eax");

    fprintf(fpasm, "\nfin_distinto_%d:\n", etiqueta);
}

void menor_igual(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    if (fpasm == NULL || es_variable1 < 0 || es_variable1 > 1 || es_variable2 < 0 || es_variable2 > 1)
        return;
    fprintf(fpasm, "\tpop dword eax"); /*second operand in eax, pops the element at the top of the stack*/
    fprintf(fpasm, "\n\tpop dword ebx"); /*first operandd in ebx, pops the element that is now at the top of the stack*/

    if (es_variable1 == 1)
    {
        fprintf(fpasm, "\n\tmov dword ebx, [ebx]");
    }
    if (es_variable2 == 1)
    {
        fprintf(fpasm, "\n\tmov dword eax, [eax]");
    }

    fprintf(fpasm, "\n\tcmp ebx, eax");
    fprintf(fpasm, "\n\tjle near menorigual_%d", etiqueta);

    fprintf(fpasm, "\n\tmov dword ebx, 0");
    fprintf(fpasm, "\n\tpush dword ebx");
    fprintf(fpasm, "\n\tjmp near fin_menorigual_%d", etiqueta);

    fprintf(fpasm, "\nmenorigual_%d:", etiqueta);
    fprintf(fpasm, "\n\tmov dword ebx,1");
    fprintf(fpasm, "\n\tpush dword ebx");

    fprintf(fpasm, "\nfin_menorigual_%d:\n", etiqueta);
}

void mayor_igual(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    if (fpasm == NULL || es_variable1 < 0 || es_variable1 > 1 || es_variable2 < 0 || es_variable2 > 1)
        return;
    fprintf(fpasm, "\tpop dword eax"); /*second operand in eax, pops the element at the top of the stack*/
    fprintf(fpasm, "\n\tpop dword ebx"); /*first operandd in ebx, pops the element that is now at the top of the stack*/

    if (es_variable1 == 1)
    {
        fprintf(fpasm, "\n\tmov dword ebx, [ebx]");
    }
    if (es_variable2 == 1)
    {
        fprintf(fpasm, "\n\tmov dword eax, [eax]");
    }

    fprintf(fpasm, "\n\tcmp ebx, eax");
    fprintf(fpasm, "\n\tjge near mayorigual_%d", etiqueta);

    fprintf(fpasm, "\n\tmov dword ebx, 0");
    fprintf(fpasm, "\n\tpush dword ebx");
    fprintf(fpasm, "\n\tjmp fin_mayorigual_%d", etiqueta);

    fprintf(fpasm, "\nmayorigual_%d:", etiqueta);
    fprintf(fpasm, "\n\tmov dword ebx,1");
    fprintf(fpasm, "\n\tpush dword ebx");

    fprintf(fpasm, "\nfin_mayorigual_%d:\n", etiqueta);
}

void menor(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    if (fpasm == NULL || es_variable1 < 0 || es_variable1 > 1 || es_variable2 < 0 || es_variable2 > 1)
        return;
    fprintf(fpasm, "\tpop dword eax"); /*second operand in eax, pops the element at the top of the stack*/
    fprintf(fpasm, "\n\tpop dword ebx"); /*first operandd in ebx, pops the element that is now at the top of the stack*/

    if (es_variable1 == 1)
    {
        fprintf(fpasm, "\n\tmov dword ebx, [ebx]");
    }
    if (es_variable2 == 1)
    {
        fprintf(fpasm, "\n\tmov dword eax, [eax]");
    }

    fprintf(fpasm, "\n\tcmp ebx, eax");
    fprintf(fpasm, "\n\tjl near menor_%d", etiqueta);

    fprintf(fpasm, "\n\tmov dword ebx, 0");
    fprintf(fpasm, "\n\tpush dword ebx");
    fprintf(fpasm, "\n\tjmp near fin_menor_%d", etiqueta);

    fprintf(fpasm, "\n\tmenor_%d:", etiqueta);
    fprintf(fpasm, "\n\tmov dword ebx,1");
    fprintf(fpasm, "\n\tpush dword ebx");

    fprintf(fpasm, "\nfin_menor_%d:\n", etiqueta);
}

void mayor(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    if (fpasm == NULL || es_variable1 < 0 || es_variable1 > 1 || es_variable2 < 0 || es_variable2 > 1)
        return;
    fprintf(fpasm, "\tpop dword eax"); /*second operand in eax, pops the element at the top of the stack*/
    fprintf(fpasm, "\n\tpop dword ebx"); /*first operandd in ebx, pops the element that is now at the top of the stack*/

    if (es_variable1 == 1)
    {
        fprintf(fpasm, "\n\tmov dword ebx, [ebx]");
    }
    if (es_variable2 == 1)
    {
        fprintf(fpasm, "\n\tmov dword eax, [eax]");
    }

    fprintf(fpasm, "\n\tcmp ebx, eax");
    fprintf(fpasm, "\n\tjg near mayor_%d", etiqueta);

    fprintf(fpasm, "\n\tmov dword ebx, 0");
    fprintf(fpasm, "\n\tpush dword ebx");
    fprintf(fpasm, "\n\tjmp near fin_mayor_%d", etiqueta);

    fprintf(fpasm, "\nmayor_%d:", etiqueta);
    fprintf(fpasm, "\n\tmov dword ebx,1");
    fprintf(fpasm, "\n\tpush dword ebx");

    fprintf(fpasm, "\nfin_mayor_%d:\n", etiqueta);
}

/* FUNCIONES DE ESCRITURA Y LECTURA */
/*
Se necesita saber el tipo de datos que se va a procesar (ENTERO o BOOLEANO) ya
que hay diferentes funciones de librería para la lectura (idem. escritura) de cada
tipo.
Se deben insertar en la pila los argumentos necesarios, realizar la llamada
(call) a la función de librería correspondiente y limpiar la pila.
*/
void leer(FILE *fpasm, char *nombre, int tipo)
{
    if (fpasm == NULL || nombre == NULL)
        return;

    fprintf(fpasm, ";leer");
    fprintf(fpasm, "\n\tpush dword _%s", nombre);
    if (tipo == BOOLEAN)
    {
        fprintf(fpasm, "\n\tcall scan_boolean");
    }
    else if (tipo == INT)
    {
        fprintf(fpasm, "\n\tcall scan_int");
    }
    fprintf(fpasm, "\n\tadd esp, 4\n");
}

void escribir(FILE *fpasm, int es_variable, int tipo)
{
    if (fpasm == NULL || es_variable < 0 || es_variable > 1)
        return;

    if (es_variable)
    {
        fprintf(fpasm, "\tpop dword eax");
        fprintf(fpasm, "\n\tmov dword eax, [eax]");
        fprintf(fpasm, "\n\tpush dword eax\n");
    }
    if (tipo == BOOLEAN)
    {
        fprintf(fpasm, "\tcall print_boolean\n");
    }
    else if (tipo == INT)
    {
        fprintf(fpasm, "\tcall print_int\n");
    }
    fprintf(fpasm, "\tadd esp, 4");
    fprintf(fpasm, "\n\tcall print_endofline\n");
}

void ifthenelse_inicio(FILE *fpasm, int exp_es_variable, int etiqueta)
{
    if (fpasm == NULL || exp_es_variable < 0 || exp_es_variable > 1)
        return;

    fprintf(fpasm, "\tpop dword eax");
    if (exp_es_variable == 1)
    {
        fprintf(fpasm, "\n\tmov dword eax, [eax]");
    }
    fprintf(fpasm, "\n\tcmp eax, 0");
    fprintf(fpasm, "\n\tje near _end_simple_conditional_%d\n", etiqueta);

    return;
}

/*
Generación de código para el inicio de una estructura if-then-else
Como es el inicio de uno bloque de control de flujo de programa que requiere de una nueva
etiqueta deben ejecutarse antes las tareas correspondientes a esta situación
exp_es_variable
Es 1 si la expresión de la condición es algo asimilable a una variable (identificador,
elemento de vector)
Es 0 en caso contrario (constante u otro tipo de expresión)
*/
void ifthen_inicio(FILE *fpasm, int exp_es_variable, int etiqueta)
{
    if (fpasm == NULL || exp_es_variable < 0 || exp_es_variable > 1)
        return;

    fprintf(fpasm, "\tpop dword eax");
    if (exp_es_variable == 1)
    {
        fprintf(fpasm, "\n\tmov dword eax, [eax]");
    }

    fprintf(fpasm, "\n\tcmp eax, 0\n\tje near _end_simple_conditional_%d\n", etiqueta);

    return;
}
/*
Generación de código para el inicio de una estructura if-then
Como es el inicio de uno bloque de control de flujo de programa que requiere de una nueva
etiqueta deben ejecutarse antes las tareas correspondientes a esta situación
exp_es_variable
Es 1 si la expresión de la condición es algo asimilable a una variable (identificador,
elemento de vector)
Es 0 en caso contrario (constante u otro tipo de expresión)
*/

void ifthen_fin(FILE *fpasm, int etiqueta)
{
    if (fpasm == NULL)
        return;

    fprintf(fpasm, "_end_simple_conditional_%d:\n", etiqueta);

    return;
}
/*
Generación de código para el fin de una estructura if-then
Como es el fin de uno bloque de control de flujo de programa que hace uso de la etiqueta
del mismo se requiere que antes de su invocación tome el valor de la etiqueta que le toca
según se ha explicado
Y tras ser invocada debe realizar el proceso para ajustar la información de las etiquetas
puesto que se ha liberado la última de ellas.
*/

void ifthenelse_fin_then(FILE *fpasm, int etiqueta)
{
    if (fpasm == NULL)
        return;

    fprintf(fpasm, "\tjmp near _end_compound_conditional_%d", etiqueta);
    fprintf(fpasm, "\n_end_simple_conditional_%d:\n", etiqueta);

    return;
}

/*
Generación de código para el fin de la rama then de una estructura if-then-else
Sólo necesita usar la etiqueta adecuada, aunque es el final de una rama, luego debe venir
otra (la rama else) antes de que se termine la estructura y se tenga que ajustar las etiquetas
por lo que sólo se necesita que se utilice la etiqueta que corresponde al momento actual.
*/

void ifthenelse_fin(FILE *fpasm, int etiqueta)
{
    if (fpasm == NULL)
        return;

    fprintf(fpasm, "_end_compound_conditional_%d:\n", etiqueta);
    return;
}
/*
Generación de código para el fin de una estructura if-then-else
Como es el fin de uno bloque de control de flujo de programa que hace uso de la etiqueta
del mismo se requiere que antes de su invocación tome el valor de la etiqueta que le toca
según se ha explicado
Y tras ser invocada debe realizar el proceso para ajustar la información de las etiquetas
puesto que se ha liberado la última de ellas.
*/

void while_inicio(FILE *fpasm, int etiqueta)
{
    if (fpasm == NULL)
        return;

    fprintf(fpasm, "_start_loop_%d:\n", etiqueta);

    return;
}

/*
Generación de código para el inicio de una estructura while
Como es el inicio de uno bloque de control de flujo de programa que requiere de una nueva
etiqueta deben ejecutarse antes las tareas correspondientes a esta situación
exp_es_variable
Es 1 si la expresión de la condición es algo asimilable a una variable (identificador,
elemento de vector)
Es 0 en caso contrario (constante u otro tipo de expresión)
*/

void while_exp_pila(FILE *fpasm, int exp_es_variable, int etiqueta)
{
    if (fpasm == NULL || exp_es_variable < 0 || exp_es_variable > 1)
        return;

    fprintf(fpasm, "\tpop dword eax");

    if (exp_es_variable == 1)
    {
        fprintf(fpasm, "\n\tmov eax, [eax]");
    }

    fprintf(fpasm, "\n\tcmp eax, 0\n\tje near _end_loop_%d\n", etiqueta);

    return;
}
/*
Generación de código para el momento en el que se ha generado el código de la expresión
de control del bucle
Sólo necesita usar la etiqueta adecuada, por lo que sólo se necesita que se recupere el valor
de la etiqueta que corresponde al momento actual.
exp_es_variable
Es 1 si la expresión de la condición es algo asimilable a una variable (identificador,
o elemento de vector)
Es 0 en caso contrario (constante u otro tipo de expresión)
*/

void while_fin(FILE *fpasm, int etiqueta)
{
    if (fpasm == NULL)
        return;

    fprintf(fpasm, "\tjmp near _start_loop_%d", etiqueta);
    fprintf(fpasm, "\n_end_loop_%d:\n", etiqueta);

    return;
}
/*
Generación de código para el final de una estructura while
Como es el fin de uno bloque de control de flujo de programa que hace uso de la etiqueta
del mismo se requiere que antes de su invocación tome el valor de la etiqueta que le toca
según se ha explicado
Y tras ser invocada debe realizar el proceso para ajustar la información de las etiquetas
puesto que se ha liberado la última de ellas.
*/

void escribir_elemento_vector(FILE *fpasm, char *nombre_vector,
                              int tam_max, int exp_es_direccion)
{
    if (fpasm == NULL || nombre_vector == NULL || tam_max < 0 || exp_es_direccion < 0 || exp_es_direccion > 1)
        return;

    fprintf(fpasm, "\t;escribir_elemento_vector\n");
    fprintf(fpasm, "\tpop dword eax");

    if (exp_es_direccion == 1)
    {
        fprintf(fpasm, "\n\tmov dword eax, [eax]");
    }

    fprintf(fpasm, "\n\tcmp eax, 0");
    fprintf(fpasm, "\n\tjl near end_index_out_of_range");

    fprintf(fpasm, "\n\tcmp eax, %d", tam_max - 1);
    fprintf(fpasm, "\n\tjg near end_index_out_of_range");

    fprintf(fpasm, "\n\tmov dword edx, _%s", nombre_vector);
    fprintf(fpasm, "\n\tlea eax, [edx + eax*4]");
    fprintf(fpasm, "\n\tpush dword eax\n");

    return;
}
/*
Generación de código para indexar un vector
Cuyo nombre es nombre_vector
Declarado con un tamaño tam_max
La expresión que lo indexa está en la cima de la pila
Puede ser una variable (o algo equivalente) en cuyo caso exp_es_direccion vale 1
Puede ser un valor concreto (en ese caso exp_es_direccion vale 0)
Según se especifica en el material, es suficiente con utilizar dos registros para realizar esta
tarea.
*/

void declararFuncion(FILE *fd_asm, char *nombre_funcion, int num_var_loc)
{
    if (fd_asm == NULL || nombre_funcion == NULL)
        return;

    fprintf(fd_asm, "_%s:", nombre_funcion);

    fprintf(fd_asm, "\n\tpush dword ebp\n\tmov dword ebp, esp");

    fprintf(fd_asm, "\n\tsub esp, %d\n", 4 * num_var_loc);
}
/*
Generación de código para iniciar la declaración de una función.
Es necesario proporcionar
Su nombre
Su número de variables locales
*/

void retornarFuncion(FILE *fd_asm, int es_variable)
{
    if (fd_asm == NULL || es_variable < 0 || es_variable > 1)
        return;

    fprintf(fd_asm, "\tpop eax");

    if (es_variable == 1)
    {
        fprintf(fd_asm, "\n\tmov dword eax, [eax]");
    }

    fprintf(fd_asm, "\n\tmov esp, ebp\n\tpop ebp\n\tret\n");

    return;
}
/*
Generación de código para el retorno de una función.
La expresión que se retorna está en la cima de la pila.
Puede ser una variable (o algo equivalente) en cuyo caso exp_es_direccion vale 1
Puede ser un valor concreto (en ese caso exp_es_direccion vale 0)
*/

void escribirParametro(FILE *fpasm, int pos_parametro, int num_total_parametros)
{
    int d_ebp=0;
    
    if (fpasm == NULL || num_total_parametros < 0)
        return;
    
    d_ebp = 4 * (1 + (num_total_parametros - pos_parametro));
    fprintf(fpasm, "\tlea eax, [ebp + %d]\n\tpush dword eax\n", d_ebp);

    return;
}
/*
Función para dejar en la cima de la pila la dirección efectiva del parámetro que ocupa la
posición pos_parametro (recuerda que los parámetros se ordenan con origen 0) de un total
de num_total_parametros
*/

void escribirVariableLocal(FILE *fpasm, int posicion_variable_local)
{
    int d_ebp = 0;

    if (fpasm == NULL)
        return;
    
    d_ebp = 4 * posicion_variable_local;

    fprintf(fpasm, "\tlea eax, [ebp - %d]\n\tpush dword eax\n", d_ebp);

    return;
}
/*
Función para dejar en la cima de la pila la dirección efectiva de la variable local que ocupa
la posición posicion_variable_local (recuerda que ordenadas con origen 1)
*/

void asignarDestinoEnPila(FILE *fpasm, int es_variable)
{
    if (fpasm == NULL || es_variable < 0 || es_variable > 1)
        return;

    fprintf(fpasm, "\n\tpop dword ebx\n\tpop dword eax");

    if (es_variable == 1)
    {
        fprintf(fpasm, "\n\tmov dword ebx, [ebx]");
    }

    fprintf(fpasm, "\n\tmov dword [eax], ebx\n");

    return;
}

void invertirEnPila(FILE * fpasm){
  fprintf(fpasm,"\n\tpop dword eax");
  fprintf(fpasm,"\n\tpop dword ebx");
  fprintf(fpasm,"\n\tpush dword eax");
  fprintf(fpasm,"\n\tpush dword ebx");
}
/*
Función para poder asignar a un destino que no es una variable “global” (tipo _x) por
ejemplo parámetros o variables locales (ya que en ese caso su nombre real de alto nivel, no
se tiene en cuenta pues es realmente un desplazamiento a partir de ebp: ebp+4 o ebp-8 por
ejemplo).
Se debe asumir que en la pila estará
Primero (en la cima) lo que hay que asignar
Debajo (se ha introducido en la pila antes) la dirección donde hay que asignar
es_variable
Es 1 si la expresión que se va a asignar es algo asimilable a una variable
(identificador, o elemento de vector)
Es 0 en caso contrario (constante u otro tipo de expresión)
*/

void operandoEnPilaAArgumento(FILE *fd_asm, int es_variable)
{
    if (fd_asm == NULL || es_variable < 0 || es_variable > 1)
        return;

    if (es_variable == 1)
    {
        fprintf(fd_asm, ";operandoEnPilaAArgumento\n");
        fprintf(fd_asm, "\tpop dword eax\n\tmov dword eax, [eax]\n\tpush dword eax\n");
    }

    return;
}

/*
Como habrás visto en el material, nuestro convenio de llamadas a las funciones asume que
los argumentos se pasan por valor, esto significa que siempre se dejan en la pila “valores” y
no “variables”
Esta función realiza la tarea de dado un operando escrito en la pila y sabiendo si es variable
o no (es_variable) se deja en la pila el valor correspondiente
*/

void llamarFuncion(FILE *fd_asm, char *nombre_funcion, int num_argumentos)
{

    if (fd_asm == NULL || nombre_funcion == NULL || num_argumentos < 0)
        return;

    fprintf(fd_asm, "\tcall _%s\n", nombre_funcion);
    limpiarPila(fd_asm, num_argumentos);

    return;
}
/*
Esta función genera código para llamar a la función nombre_funcion asumiendo que los
argumentos están en la pila en el orden fijado en el material de la asignatura.
Debe dejar en la cima de la pila el retorno de la función tras haberla limpiado de sus
argumentos
Para limpiar la pila puede utilizar la función de nombre limpiarPila
*/

void limpiarPila(FILE *fd_asm, int num_argumentos)
{
    if (fd_asm == NULL || num_argumentos < 0)
    {
        fprintf(stderr, "Error with fpasm in function limpiarPila\n");
        return;
    }

    fprintf(fd_asm, "\tadd esp, %d", num_argumentos * 4);
    fprintf(fd_asm, "\n\tpush dword eax\n");

    return;
}
/*
Genera código para limpiar la pila tras invocar una función
Esta función es necesaria para completar la llamada a métodos, su gestión dificulta el
conocimiento por parte de la función de llamada del número de argumentos que hay en la
pila
*/



