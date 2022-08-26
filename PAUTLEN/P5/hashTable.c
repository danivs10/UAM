/* =====================================================================================
 *
 *       Filename:  tablaSimbolos.c
 *
 *    Description:  table of symbols
 *
 *        Version:  1.0
 *        Created:  27th of november of 2021 19:38:00
 *        Authors:  Santiago Atrio, Lucía Gil, Javier López de la Nieta and Daniel Varela
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashTable.h"


#define MAX_TABLE_SIZE 	1024*1024

#define TRUE			1
#define FLASE			0

/*
	 Función: algoritmo hash, devolver valor hash
	 clave: tipo char *, valor clave
	 ken_len: longitud de la clave
	 Valor de retorno: valor hash
*/
unsigned int JSHash(char* key)
{	
	int j=0;
    unsigned long i = 0;
    for (j=0; key[j]; j++)
        i += key[j];
    return i % MAX_TABLE_SIZE;
}
/*
	 Función: inicializar el nodo hash
	 nodo: nodo hash
	 Valor de retorno: ninguno
*/
void init_hs_node(Hash_node *node)
{
	node->next = NULL;
	node->key = NULL;
	node->value = NULL;
	node->is_occupied = FALSE;
}
/*
	 Función: inicializar el nodo hash
	 nodo: nodo hash
	 Valor de retorno: ninguno
*/
Simbol * simboloinit(char* lexema, int categoria, int clase, int tipo, int tamanio, int localVar, int localVarPos, int param, int paramPos)
{
	Simbol *s = NULL;
	
	s = (Simbol*)malloc(sizeof(Simbol));
	if(s==NULL){
		free(s);
		return NULL;
	}
	
    strcpy(s->lexema, lexema);
    s->categoria = categoria;
    s->clase = clase;
    s->tipo = tipo;
    s->tamanio = tamanio;
    s->localVar = localVar;
    s->localVarPos = localVarPos;
    s->param = param;
    s->paramPos = paramPos;

	return s;
}

/*
	 Función: crear una tabla hash
	 Parámetros: ninguno
	 Valor de retorno: devuelve correctamente una tabla hash creada; de lo contrario, NULL
*/
Hash_Table *creat_hash_table(void)
{
	Hash_Table *Hs_table = (Hash_Table *)malloc(sizeof(Hash_Table));
	if (!Hs_table)
	{
		printf("no enough memory\n");
		return NULL;
	}
	
	Hs_table->table = malloc(sizeof(Hash_node) * MAX_TABLE_SIZE);
	if (!Hs_table->table)
	{
		printf("no enough memory for table\n");
		free(Hs_table);
		Hs_table = NULL;
		return NULL;
	}
	
	memset(Hs_table->table, 0, sizeof(Hash_node) * MAX_TABLE_SIZE);
	
	return Hs_table;
}

/*
	 Función: agregar un nodo a la tabla hash
	 Hs_table: tabla hash, no puede estar vacía
	 clave: valor clave, no puede estar vacío
	 key_len: longitud de la clave
	 valor: valor
	 Valor de retorno: 0 éxito -1 falla
*/
int add_node2HashTable(Hash_Table *Hs_table, char *key, unsigned int key_len, Simbol *value)
{
	char *tmp_key = NULL;
	unsigned int i = 0;
	Hash_node *p = NULL;
	Hash_node *pri = NULL;
	
	if(!Hs_table || !key )
	{
		printf("something is NULL\n");
		return -1;
	}

	if(get_value_from_hstable(Hs_table, key, key_len)!=NULL){
		return -1;
	}

	i =  JSHash(key) % MAX_TABLE_SIZE;

	p = Hs_table->table[i];
	pri = p;
	
	while(p)
	{
		if ( strncmp(key, p->key, key_len) == 0 )
		{
			if(p->is_occupied)
			{
				p->value = value;
				p->is_occupied = 1;
				break;
			}
		}
		pri = p;
		p = p->next;
	}
	
	if(!p)
	{
		Hash_node *tmp = (Hash_node *)malloc(sizeof(Hash_node));
		if( !tmp )
		{
			printf("no enough memory\n");
			return -1;
		}
		init_hs_node(tmp);
		
		tmp_key = (char *)malloc(key_len+1);
		if(!tmp_key)
		{
			free(tmp);
			tmp = NULL;
			return -1;
		}
		strncpy(tmp_key, key, key_len);
		tmp->key = tmp_key;
		tmp->value = value;
		tmp->is_occupied = TRUE;
		
		if(pri == NULL)
		{
			Hs_table->table[i] = tmp;
		}
		else
		{
			pri->next = tmp;
		}
	}
	
	return 0;
}

/*
	 Función: obtener datos de la tabla hash
	 Hs_table: tabla hash, no puede estar vacía
	 clave: valor clave, no puede estar vacío
	 key_len: longitud de la clave
	 Valor de retorno: contenido de almacenamiento, NULL si no se encuentra
*/
Simbol *get_value_from_hstable(Hash_Table *Hs_table, char *key, unsigned int key_len)
{
	int i = 0;
	Hash_node *tmp = NULL;

	if( !Hs_table || !key)
	{
		printf("something is NULL\n");
		return NULL;
	}
	
	i = JSHash(key) % MAX_TABLE_SIZE;
	tmp = Hs_table->table[i];
	
	while(tmp)
	{
		if(strncmp(tmp->key, key, key_len) == 0)
		{
			return (Simbol *)(tmp->value);
		}
		tmp = tmp->next;
	}
	
	return NULL;
}

/*
	 Función: Eliminar tabla hash
	 Hs_Table: nombre de la tabla hash
	 Valor de retorno: ninguno
*/
void hash_table_delete(Hash_Table *Hs_Table)
{
	Simbol *s=NULL;
    if (Hs_Table)
	{
        if (Hs_Table->table)
		{
            int i = 0;
            for (i = 0; i<MAX_TABLE_SIZE; i++)
			{
                Hash_node *p = Hs_Table->table[i];
                Hash_node *q = NULL;
                while (p)
				{
                    q = p->next;
                    p->is_occupied = 0;
					free(p->key);
					free(p->value);
					free(p);
                    p = q;
                }
            }
            free(Hs_Table->table);
            Hs_Table->table = NULL;
        }
        free(Hs_Table);	
		Hs_Table = NULL;
    }
	return ;
}

/*
	 Función: Muestra por terminal los valores de la hash table
	 Hs_Table: puntero a la hash table
	 Valor de retorno: ninguno
*/
/*void getSimbols(Hash_Table *Hs_Table) {
    if (Hs_Table)
	{
        if (Hs_Table->table)
		{
            int i = 0;
            for (i = 0; i<MAX_TABLE_SIZE; i++)
			{
                Hash_node *p = Hs_Table->table[i];
                Hash_node *q = NULL;
                while (p)
				{
                    q = p->next;
					printf("%s has value : %d\n", p->key, (int)p->value);
                    p = q;
                }
            }
        }
    }
	return;

}*/