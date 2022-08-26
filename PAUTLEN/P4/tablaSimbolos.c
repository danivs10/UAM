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

int main(int argc, char *argv[])
{
    FILE *yyin = NULL;
    FILE *yyout = NULL;
    size_t len;
    char *line = NULL;
    int words = 0;
    char name[100];
    int val = 0;
    void *out = NULL;
    int x = 0;

    /* Creation of global and local hash tables */
    Hash_Table *global = creat_hash_table();
    Hash_Table *local = NULL;
    Hash_Table *currentTable = global;

    /* If not input and output files where provided, send error */
    if (argc < 3)
    {
        fprintf(stderr, "Try executing the program this way: <name program> <input file> <output file>");
        return -1;
    }

    /* Open input file */
    yyin = fopen(argv[1], "r");
    if (yyin == NULL)
    {
        fprintf(stderr, "Not possible to open input file");
        return -1;
    }

    /* Open output file */
    yyout = fopen(argv[2], "w");
    if (yyout == NULL)
    {
        fprintf(stderr, "Not possible to open output file");
        return -1;
    }

    /* Loop throw every line of the file */
    while (getline(&line, &len, yyin) != EOF)
    {
        /* Store in words the number of words read, in name the first word and in val the number */
        words = sscanf(line, "%s\t%d\n", name, &val);

        /* If only one word was written */
        if (words == 1)
        {
            /* Search for the value of the variable in the hash table you are currently */
            out = get_value_from_hstable(currentTable, name, sizeof(name));
            
            /* If not found */
            if (out == NULL)
            {
                /* Search in the global table just in case you were on the local one */
                out = get_value_from_hstable(global, name, sizeof(name));
                
                /* If not found in the global table either */
                if (out == NULL)
                {  
                    /* Print the name of the variable and a -1 after a tab */
                    fprintf(yyout, "%s\t-1\n", name);
                }
                else
                {
                    /* If it was found at the global table print the value in the global table */
                    fprintf(yyout, "%s\t%d\n", name, (int)out);
                }
            }
            else
            {
                /* If the value was found in the current table print it */
                fprintf(yyout, "%s\t%d\n", name, (int)out);
            }
        }
        else if (words == 2)
        {
            /* If two words were written check if the value is grater or equal than 0 */
            if (val >= 0)
            {
                /* If the value is grater or equal than 0, add the variable to the hash table with 
                 * the corresponding value passed as second word */
                if (add_node2HashTable(currentTable, name, sizeof(name), val) == -1)
                {
                    /* If the add was unsuccesfull, it means that the value was previously
                     * stored into the table and it cannot be added */
                    fprintf(yyout, "-1\t%s\n", name);
                }
                else
                {
                    /* If the add was succesfull just print the name of the variable */
                    fprintf(yyout, "%s\n", name);
                }
            }
            else
            {
                /* If the value is negative and equal to -999 a clausure is detected */
                if (val == -999)
                {
                    /* Over clausure detected, delete the local table and set it to NULL and set
                     * the current table to the global one and print the statement 'cierre' */
                    hash_table_delete(local);
                    local=NULL;
                    currentTable = global;
                    fprintf(yyout, "%s\n", name);
                }
                else
                {
                    /* In the case every other negative number is witten, a function is detected,
                     * so we will need to create a new local table, set it to the curren one, store the
                     * name of the function in both tables (global and local) and print the name of the 
                     * function */
                    add_node2HashTable(currentTable, name, sizeof(name), val);
                    local = creat_hash_table();
                    currentTable = local;
                    add_node2HashTable(currentTable, name, sizeof(name), val);
                    fprintf(yyout, "%s\n", name);
                }
            }
        }
        else
        {
            /* If nor 1 nor 2 word where written that means that the input file is wrong witten and the
             * program does not support different input formats */
            fprintf(stderr, "Nor 1 or 2 words were written %d ", words);
            return -1;
        }
    }

    /* Frees and table deletion */
    free(line);
    fclose(yyin);
    fclose(yyout);
    if (local != NULL)
    {
        hash_table_delete(local);
    }
    hash_table_delete(global);
    printf("\n");
    return 0;
}
