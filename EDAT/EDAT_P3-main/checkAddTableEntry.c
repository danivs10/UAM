/*
// Created by Daniel Varela &Guillermo De Andres Perez on 14/12/20.
*/
#include "tester.h"


void checkAddTableEntry(const char * tableName, const char * indexName)
/**
 *  check AddTableEntry
 */
{
    bool result;
    Book *book=NULL;
    book = (Book *)malloc(sizeof(Book));
    book->title = calloc(264, sizeof(char));

    createTestDataFile(tableName);
    printf("\n\n-----CheckAddTableEntry-------\n");

    /* 1) add existing book should complain*/

    result = addTableEntry(&b[0], tableName, indexName);
    if (result){
        fprintf(stderr,
"Error in addIndexEntry, inserted existing key %s",
                b[0].book_id);
        exit(EXIT_FAILURE);
    }
    printf("\n\n-----Original Table-------\n");
    printData(tableName);

    /*2) add new book RAR3 of size 10 it should place it in offset 139 */

    printf("\n\n-----after adding RAR3-------\n");
    strcpy(book->book_id, "RAR3");
    strcpy(book->title, "RAR3_three");
    book->title_len=10;
    result = addTableEntry(book, tableName, indexName);
    printData(tableName);
    strcpy(book->title, "\0");
    /*3) add new book WAR4 of size 10 it should place it at the end of the table */

    printf("\n\n-----after adding WAR4-------\n");
    strcpy(book->book_id, "WAR4");
    strcpy(book->title, "WAR4_three");
    book->title_len=10;
    result = addTableEntry(book, tableName, indexName);
    printData(tableName);
    strcpy(book->title, "\0");


    /*4) add new book WAR4 of size 6 it should place it at offset 71 and change the first deleted node to -1 */

    printf("\n\n-----after adding CAR6-------\n");
    strcpy(book->book_id, "CAR6");
    strcpy(book->title, "CAR6_a");
    book->title_len=6;
    result = addTableEntry(book, tableName, indexName);
    printData(tableName);
    strcpy(book->title, "\0");

    printf("* checkAddTableEntry: OK\n");
    return;
}

