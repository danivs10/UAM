/*  UNO DE MUCHOS INTENTOS    */
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
    char *line;
    int words = 0;
    char name[100];
    int val = 0;
    void *out = NULL;
    int x = 0;
    int loc=0;

    /* Creation of global and local hash tables */
    Hash_Table *global = creat_hash_table();
    Hash_Table *local = NULL;

    if (argc < 3)
    {
        fprintf(stderr, "Everything wrong. You are dumb.: <name program> <input file> <output file>");
        return -1;
    }

    yyin = fopen(argv[1], "r");
    if (yyin == NULL)
    {
        fprintf(stderr, "Not possible to open input file");
        return -1;
    }

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
        words = sscanf(line, "%s\t%d\n", &name, &val);

        /* If only one or two strings were written */
        if (words == 1)
        {
            if(loc==0){
                out = get_value_from_hstable(global, name, sizeof(name));

                if (out == NULL)
                {
                    fprintf(yyout, "%s\t-1\n", name);
                }
                else
                {
                    fprintf(yyout, "%s\t%d\n", name, (int)out);
                }
            }
            else {
                out = get_value_from_hstable(local, name, sizeof(name));
                
                if (out == NULL)
                {  
                    out = get_value_from_hstable(global, name, sizeof(name));
                    if (out == NULL)
                    {  
                        fprintf(yyout, "%s\t-1\n", name);
                    }
                    else{
                        fprintf(yyout, "%s\t%d\n", name, (int)out);
                    }
                }
                else
                {
                    fprintf(yyout, "%s\t%d\n", name, (int)out);
                }
            }
        }
        else if (words == 2)
        {
            if (val >= 0)
            {
                if (loc == 0) {
                    if (add_node2HashTable(global, name, sizeof(name), val) == -1)
                    {
                        fprintf(yyout, "-1\t%s\n", name);
                    }
                    else
                    {
                        fprintf(yyout, "%s\n", name);
                    }
                } else {
                    if (add_node2HashTable(local, name, sizeof(name), val) == -1)
                    {
                        fprintf(yyout, "-1\t%s\n", name);
                    }
                    else
                    {
                        fprintf(yyout, "%s\n", name);
                    }
                }
            }
            else
            {
                if (val == -999 && loc == 1)
                {
                    hash_table_delete(local);
                    loc=0;
                    fprintf(yyout, "%s\n", name);
                }
                else if (val < 0)
                {
                    add_node2HashTable(global, name, sizeof(name), val);
                    local = creat_hash_table();
                    loc=1;
                    add_node2HashTable(local, name, sizeof(name), val);
                    fprintf(yyout, "%s\n", name);
                } else {
                    printf("Something went wrong");
                    return -1;
                }
            }
        }
        else
        {
            fprintf(stderr, "Nor 1 or 2 words were written %d ", words);
            return -1;
        }
    }

    fclose(yyin);
    fclose(yyout);
    hash_table_delete(local);
    hash_table_delete(global);
    printf("\n");
    return 0;
}
