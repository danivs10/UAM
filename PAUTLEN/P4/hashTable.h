#ifndef HASHTABLE_H
#define HASHTABLE_H

/* Declaration of macros for alfa element categories */
#define VARIABLE 1
#define PARAMETRO 2
#define FUNCION 3

/* Declaration of macros for alfa data types */
#define BOOLEAN 1
#define INT 2

/* Declaration of the macros for alfa categories */
#define ESCALAR 1
#define VECTOR 2

/* Declaration for the max size of a vector */
#define MAX_VECTOR_SIZE 64

/* Declaration of the structures */
typedef struct hash_node
{
	struct hash_node *next;	/* Si el hash (clave) es el mismo, siga el relevo */
	char *key;		/* Palabra clave */
	void *value;			/* valor */
	int category;			/* valor */
    int type;
    int class; 
	char is_occupied;	    /* ¿Está ocupado? */
}Hash_node;

typedef struct hash_table
{
	Hash_node **table;	/* Tabla de picadillo */
}Hash_Table;

/* Declaration of the functions */
unsigned int JSHash(char* key);
void init_hs_node(Hash_node *node);
Hash_Table *creat_hash_table(void);
int add_node2HashTable(Hash_Table *Hs_table, char *key, unsigned int key_len, void *value);
void *get_value_from_hstable(Hash_Table *Hs_table, char *key, unsigned int key_len);
void hash_table_delete(Hash_Table *Hs_Table);

#endif