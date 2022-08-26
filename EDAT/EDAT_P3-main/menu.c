#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define MENU_SIZE 264

int main(void)
{
    char input[MENU_SIZE] = "\0";
    char tableName[MENU_SIZE] = "\0";
    char tableNameDat[MENU_SIZE] = "\0";
    char tableNameIdx[MENU_SIZE] = "\0";
    bool tablecreated = false;
    char key[PK_SIZE] = "\0";
    char title[MENU_SIZE] = "\0";
    Book *book = NULL;
    int levels = 0;
    book = (Book *)malloc(sizeof(Book));
    book->title = calloc(10, sizeof(char));
    printf("/*********************************************************************************************\n");
    printf("Intoduce one of this commands(lowercase):\n\t**use: Allows the user to input the table with which they want to work with\n\t**insert: Allows the user to insert a new book to the table hence also to the tree\n\t**print: Allows the user to print the ordered tree to the level they specify\n\t**table: Command that allows the user to print the table of the .dat file\n\t**exit: Command to exit the interface\n");
    printf("*********************************************************************************************/\n\n");
    while (strcmp(input, "exit") != 0)
    {
        if (tablecreated == true)
        {
            printf("\nyou are using table: %s\n\n", tableName);
            printf("    Command: ");
        }
        else
        {
            printf("Command: ");
        }
        scanf("%s", input);
        if (strcmp(input, "use") == 0)
        {
            printf("\ninsert a table name: ");
            scanf("%s", tableName);
            strcpy(tableNameDat, tableName);
            strcat(tableNameDat, ".dat");
            replaceExtensionByIdx(tableNameDat, tableNameIdx);
            tablecreated = createTable(tableNameDat);
            if (tablecreated == true)
            {
                printf("\n    Checking table: %s\n", tableName);
                printf("    Table name correct....\n\n");
            }
        }
        else if (strcmp(input, "insert") == 0)
        {
            if (tablecreated == false)
            {
                printf("Select a table first with command (use)\n");
            }
            else
            {
                printf("    Insert a key: ");
                scanf("%s", key);
                if (strlen(key) > 4)
                {
                    printf("\n------ERROR: The key must be 4 characters long------\n");
                }
                else
                {
                    book->book_id[0] = key[0];
                    book->book_id[1] = key[1];
                    book->book_id[2] = key[2];
                    book->book_id[3] = key[3];
                    printf("    Insert a title: ");
                    getchar();
                    scanf("%[^\n]s", title);
                    strcpy(book->title, title);
                    book->title_len = strlen(title);
                    if (addTableEntry(book, tableNameDat, tableNameIdx) == false)
                    {
                        printf("------ERROR: inserting the key------\n");
                        return 1;
                    }
                }
            }
        }
        else if (strcmp(input, "print") == 0)
        {
            if (tablecreated == true)
            {
                printf("    Levels of the tree you want to print:");
                scanf("%d", &levels);
                printf("\n------printing %s.idx tree------\n", tableName);
                printTree(levels, tableNameIdx); /*We do not know the size*/
                printf("\n");
            }
            else
            {
                printf("Select a table first with command (use)\n");
            }
        }
        else if (strcmp(input, "table") == 0)
        {
            if (tablecreated == true)
            {
                printf("\n------printing %s.dat table------\n", tableName);
                printData(tableNameDat); /*We do not know the size*/
                printf("\n");
            }
            else
            {
                printf("Select a table first with command (use)\n");
            }
        }
    }
    free(book->title);
    free(book);
    printf("\n------Good bye!------\n");
    return 0;
}
