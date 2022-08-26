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
#include "tablaSimbolos.h"

Hash_Table *GlobalTable = NULL;
Hash_Table *LocalTable = NULL;

/*
	Function: Declare a node in the corresponding hash table
	lexema: symbol identifier
	s: symbol information
    Return value: integer with the status information
*/
int declare(char *lexema, Simbol *s){
    if(LocalTable == NULL){
        return globalDeclaration(lexema, s);
    }
    
    return localDeclaration(lexema,s);
}

/*
	Function: Declare a node in the corresponding hash table
	lexema: symbol identifier
	s: symbol information
    Return value: integer with the status information
*/
int globalDeclaration(char*lexema, Simbol *s){
    if(GlobalTable == NULL){
        if((GlobalTable = creat_hash_table())==NULL){
            return 0;
        }
    }

    if(get_value_from_hstable(GlobalTable, lexema, sizeof(lexema)) == NULL){
        return add_node2HashTable(GlobalTable, lexema, sizeof(lexema), s);
    }

    return 0;
}

/*
	Function: Declare a node in the corresponding hash table
	lexema: symbol identifier
	s: symbol information
    Return value: integer with the status information
*/
int localDeclaration(char *lexema, Simbol *s){

    if(get_value_from_hstable(LocalTable, lexema, sizeof(lexema)) == NULL){
        return add_node2HashTable(LocalTable, lexema, sizeof(lexema), s);
    }

    return 0;
}

/*
	Function: checks if an identifier is in the local table
	lexema: symbol identifier
    Return value: NULL is not in it or the symbol information
*/
Simbol *isLocal(char *lexema){
    Simbol *s=NULL;
    if(LocalTable==NULL){
        return isGlobal(lexema);
    }

    s = get_value_from_hstable(LocalTable, lexema, sizeof(lexema));
    
    if(s == NULL){
        return isGlobal(lexema);
    } 

    return s;
}

/*
    Function: checks if an identifier is in the global table
    lexema: symbol identifier
    reutn: NULL if it is not in it or the symbol information
*/
Simbol *isGlobal(char *lexema){
    Simbol *s=NULL;
    if(GlobalTable==NULL){
        return NULL;
    }

    s = get_value_from_hstable(GlobalTable, lexema, sizeof(lexema));
    
    return s;
}

/*
    Function: starts a function by creating the tables
    lexema: symbol identifier
    s: symbol information
    return: 1 in success, 0 in error 
*/
int functionDeclaration(char *lexema, Simbol* s){
    int res = 0;
    
    if(LocalTable != NULL){
        return 0;
    }
    LocalTable = creat_hash_table();
    if(LocalTable == NULL){
        return 0;
    }
    if(add_node2HashTable(GlobalTable, lexema, sizeof(lexema), s) == -1){
        return 0;
    }
    add_node2HashTable(LocalTable, lexema, sizeof(lexema), s);
    return 1;
}

/*
    Function: ends the local part of the program deleting the local table
    args: None
    return: None
*/
int endFunction(void){
    if(LocalTable == NULL){
        return 0;
    }
    hash_table_delete(LocalTable);
    LocalTable = NULL;
    return 1;
}

/*
    Function: ends the program deleting all the tables
    args: None
    return: None
*/
void finish(void){
    if(LocalTable != NULL){
        hash_table_delete(LocalTable);
    }
    hash_table_delete(GlobalTable);
}

/*
    Function: searches a specific symbol in both tables
    local: local table
    global: global table
    key: symbol to search
    return: the symbol in case of found, NULL in case of not found or error
*/
void *searchSimbolInTables(Hash_Table *local, Hash_Table *global, char *key){
    Simbol *aux;

    if (local != NULL) {
        aux = get_value_from_hstable(local, key, sizeof(key));
        if (aux != NULL) {
            return aux;
        }
    }

    aux = get_value_from_hstable(global, key, sizeof(key));
    if (aux != NULL) {
        return aux;
    }
    
    return NULL;
}