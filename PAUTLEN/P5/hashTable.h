#ifndef HASHTABLE_H
#define HASHTABLE_H

/* Declaration of macros for alfa element kind */
#define VARIABLE 1
#define PARAMETRO 2
#define FUNCION 3

/* Declaration of macros for alfa data types */
#define BOOLEAN 1
#define INT 2

/* Declaration of the macros for alfa categories */
#define ESCALAR 1
#define VECTOR 2

/* Declaration for true and false */
#define TRUE 1
#define FALSE 0

/* Declaration for the max size of a vector */
#define MAX_VECTOR_SIZE 64


/* Declaration of the structures */
typedef struct hash_node
{
	struct hash_node *next;	/* Si el hash (clave) es el mismo, siga el relevo */
	char *key;		/* Palabra clave */
	Simbol *value;			/* valor */
	char is_occupied;	    /* ¿Está ocupado? */
}Hash_node;

typedef struct hash_table
{
	Hash_node **table;	/* Tabla de picadillo */
}Hash_Table;

typedef struct simbol
{
/*
   lexema
   categoría  (variable, parámetro o función)
   clase  (escalar o vector)
   tipo  (entero o booleano)
   tamaño  (número de elementos de un vector)
   número de variables locales
   posición de variable local
   número de parámetros
   posición de parámetro
*/
	char lexema[100];
    int categoria;
    int clase;
    int tipo;
    int tamanio;
    int localVar;
    int localVarPos;
    int param;
    int paramPos;
}Simbol;

/* Declaration of the functions */
unsigned int JSHash(char* key);
void init_hs_node(Hash_node *node);
Hash_Table *creat_hash_table(void);
int add_node2HashTable(Hash_Table *Hs_table, char *key, unsigned int key_len, Simbol *value);
Simbol *get_value_from_hstable(Hash_Table *Hs_table, char *key, unsigned int key_len);
void hash_table_delete(Hash_Table *Hs_Table);
Simbol * simboloinit(char* lexema, int categoria, int clase, int tipo, int tamanio, int localVar, int localVarPos, int param, int paramPos);


#endif