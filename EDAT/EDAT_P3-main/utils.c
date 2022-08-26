#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int no_deleted_registers = NO_DELETED_REGISTERS;

void replaceExtensionByIdx(const char *fileName, char *indexName)
{
    int i = strlen(fileName) - 1;
    strcpy(indexName, fileName);
    indexName[i] = 'x';
    i--;
    indexName[i] = 'd';
    i--;
    indexName[i] = 'i';
    return;
}

bool createTable(const char *tableName)
{
    FILE *f;
    char *indexName;
    f = fopen(tableName, "r");
    if (f == NULL)
    {
        f = fopen(tableName, "wb+");
        if (f == NULL)
        {
            return false;
        }
        fwrite(&no_deleted_registers, sizeof(int), 1, f);
    }
    else
    {
        fclose(f);
        f = fopen(tableName, "rb+");
    }
    fclose(f);

    indexName = (char *)malloc(strlen(tableName));
    replaceExtensionByIdx(tableName, indexName);
    if (createIndex(indexName) == false)
    {
        free(indexName);
        return false;
    }
    free(indexName);
    return true;
}

bool createIndex(const char *indexName)
{
    FILE *f;
    f = fopen(indexName, "r");

    if (f == NULL)
    {
        f = fopen(indexName, "wb+");
        if (f == NULL)
        {
            return false;
        }
        fwrite(&no_deleted_registers, sizeof(int), 1, f);
        fwrite(&no_deleted_registers, sizeof(int), 1, f);
    }
    else
    {
        fclose(f);
        f = fopen(indexName, "rb+");
    }
    fclose(f);
    return true;
}

void printnode(size_t _level, size_t level, FILE *indexFileHandler, int node_id, char side);

void printTree(size_t level, const char *indexName)
{

    FILE *f;
    int root = 0;

    f = fopen(indexName, "rb+");
    if (f == NULL)
    {
        return;
    }
    fread(&root, sizeof(int), 1, f);
    printnode(0, level, f, 0, 's');

    fclose(f);
    return;
}

void printnode(size_t _level, size_t level, FILE *indexFileHandler, int node_id, char side)
{
    int i = 0;
    char key[PK_SIZE] = "\0";
    int firstSon = -1;
    int secondSon = -1;
    int empty = 0, pos = -1;

    /*printf("nid: %d -- _level: %d -- level: %d", node_id, _level, level);*/
    if (node_id == -1 || _level > level)
    {
        return;
    }

    for (i = 0; (size_t)i < _level; i++)
    {
        printf("\t");
    }

    if (side != 's')
    {
        printf("%c ", side);
    }

    fseek(indexFileHandler, 8, SEEK_SET);
    fseek(indexFileHandler, (20 * node_id + 8), SEEK_SET);
    fread(key, PK_SIZE, 1, indexFileHandler);
    fread(&firstSon, sizeof(int), 1, indexFileHandler);
    fread(&secondSon, sizeof(int), 1, indexFileHandler);
    fread(&empty, sizeof(int), 1, indexFileHandler);
    fread(&pos, sizeof(int), 1, indexFileHandler);
    printf("%s (%d): %d\n", key, node_id, pos);

    /*printf("%s (%d): %d\n", key, node_id, pos);
    printf(" -- key: %s -- id: (%d) -- pos: %d -- fs: %d -- sson: %d\n", key, node_id, pos, firstSon, secondSon);
    printf(" -- key: %s -- id: (%d) -- pos: %d -- fs: %d -- sson: %d\n", key, id, pos, firstSon, secondSon);
    printf("%d - %d - %d --- ", id, firstSon, secondSon);
    printf("id=%d, node_id=%d", id, node_id);*/
    _level++;
    if (firstSon >= 0)
    {
        printnode(_level, level, indexFileHandler, firstSon, 'l');
    }
    if (secondSon >= 0)
    {
        printnode(_level, level, indexFileHandler, secondSon, 'r');
    }
    return;
}

bool findKey(const char *book_id, const char *indexName, int *nodeIDOrDataOffset)
{
    FILE *f;
    char key[PK_SIZE] = "\0";
    int notused[3];
    int i = 0, aux = 0;
    f = fopen(indexName, "rb");
    fseek(f, 0, SEEK_SET);
    fread(&i, sizeof(int), 1, f);
    if (i == -1)
    {
        i = 0;
        aux = -1;
    }
    while (aux != -1)
    {
        i = aux;
        fseek(f, 8 + (20 * i), SEEK_SET);
        fread(key, PK_SIZE, 1, f);
        if (strncmp(key, book_id, PK_SIZE) == 0)
        {
            fread(&notused, sizeof(int), 3, f);
            fread(nodeIDOrDataOffset, sizeof(int), 1, f);
            return true;
        }
        else if (strncmp(key, book_id, PK_SIZE) < 0)
        {
            fread(&notused, sizeof(int), 1, f);
            fread(&aux, sizeof(int), 1, f);
        }
        else if (strncmp(key, book_id, PK_SIZE) > 0)
        {
            fread(&aux, sizeof(int), 1, f);
        }
    }

    *nodeIDOrDataOffset = i;
    fclose(f);
    return false;
}

bool addTableEntry(Book *book, const char *dataName,
                   const char *indexName)
{
    char empty[100] = " ";
    FILE *f;
    int firstNodeDeleted = 0;
    int previousNodeDeleted = 0;
    int nextNodeDeleted = 0;
    int bookOffset = 0;
    int nodeIDOrDataOffset;
    int header;
    int deletedNodeSize;
    bool fits = false;
    char book_id[PK_SIZE];
    strcpy(book_id, book->book_id);
    if (findKey(book_id, indexName, &nodeIDOrDataOffset) == true)
    {
        printf("An existing key already has that name\n");
        return false;
    }
    else
    {
        /*printf("opening file\n");*/
        f = fopen(dataName, "rb+");
        fread(&firstNodeDeleted, sizeof(int), 1, f);
        header = firstNodeDeleted;
        while (header != -1 && fits == false)
        {
            /*printf("checking for deleted node %d\n", header);*/
            fseek(f, header, SEEK_SET);
            /*comprobar si cabe*/
            fread(&nextNodeDeleted, sizeof(int), 1, f);
            fread(&deletedNodeSize, sizeof(int), 1, f);
            /*printf("    size --> %d\n", deletedNodeSize);*/
            if (deletedNodeSize >= (int)book->title_len)
            {
                /*/*printf("fits\n");*/
                /*si cabe fits=true*/
                fits = true;
            }
            else
            {
                /*si no cabe*/
                /*printf("doesnt fit\n");*/
                previousNodeDeleted = header;
                header = nextNodeDeleted;
            }
        }

        if (fits == true)
        {
            /*printf("adding to position %d\n", header);*/
            if (header == firstNodeDeleted)
            {
                fseek(f, 0, SEEK_SET);
                fwrite(&nextNodeDeleted, sizeof(int), 1, f);
            }
            else
            {
                fseek(f, previousNodeDeleted, SEEK_SET);
                fwrite(&nextNodeDeleted, sizeof(int), 1, f);
            }

            fseek(f, header, SEEK_SET);
            /*printf("Next deleted node now in header: %d\n", header);*/
        }
        else
        {
            /*printf("going to the end of the file\n");*/
            fseek(f, 0, SEEK_END);
        }
        bookOffset = ftell(f);
        /*printf("printing node\n");*/

        if (fits == false)
        {
            fwrite(book->book_id, PK_SIZE, 1, f);
            fwrite(&(book->title_len), sizeof(int), 1, f);
            fwrite(book->title, sizeof(char) * book->title_len, 1, f);
        }
        if (fits == true)
        {
            fwrite(book->book_id, PK_SIZE, 1, f);
            fwrite(&deletedNodeSize, sizeof(int), 1, f);
            fwrite(empty, sizeof(char) * deletedNodeSize, 1, f);
            fseek(f, bookOffset + 8, SEEK_SET);
            fwrite(book->title, sizeof(char) * book->title_len, 1, f);
        }
        /*printf("BID: %s -- BTL: %d -- BT: %s\n", book->book_id, book->title_len, book->title);*/
        fclose(f);
        /*printf("closing file and calling indexentry\n");*/
        addIndexEntry(book->book_id, bookOffset, indexName);
        return true;
    }
    return false;
}

bool addIndexEntry(char *book_id, int bookOffset, char const *indexName)
{
    FILE *f;
    int header = 0;
    int root = 0;
    int pos = 0;
    int nextDeletedNode = 0;
    char father[PK_SIZE];
    int nodeIDOrDataOffset;
    if (findKey(book_id, indexName, &nodeIDOrDataOffset) == true)
    {
        printf("An existing key already has that name\n");
        return false;
    }

    f = fopen(indexName, "rb+");
    if (f == NULL)
    {
        return false;
    }
    fread(&root, sizeof(int), 1, f);
    fread(&header, sizeof(int), 1, f);
    if (root == 0)
    {
        root = nodeIDOrDataOffset;
    }
    if (header == no_deleted_registers)
    {
        fseek(f, 0, SEEK_END);
    }
    else
    {
        fseek(f, 12 + (header * 20), SEEK_SET);
        fread(&nextDeletedNode, sizeof(int), 1, f);
        fseek(f, 4, SEEK_SET);
        fwrite(&nextDeletedNode, sizeof(int), 1, f);
        fseek(f, 8 + (header * 20), SEEK_SET);
    }

    pos = ftell(f);
    fwrite(book_id, PK_SIZE, 1, f);
    fwrite(&no_deleted_registers, sizeof(int), 1, f);
    fwrite(&no_deleted_registers, sizeof(int), 1, f);
    fwrite(&pos, sizeof(int), 1, f);
    fwrite(&bookOffset, sizeof(int), 1, f);
    pos = (pos - INDEX_HEADER_SIZE) / 20;
    if (nodeIDOrDataOffset != -1)
    {
        fseek(f, (nodeIDOrDataOffset * 20) + 8, SEEK_SET);
        fread(father, PK_SIZE, 1, f);
        if (strcmp(father, book_id) > 0)
        {
            fwrite(&pos, sizeof(int), 1, f);
        }
        else if (strcmp(father, book_id) < 0)
        {
            fseek(f, (nodeIDOrDataOffset * 20) + 16, SEEK_SET);
            fwrite(&pos, sizeof(int), 1, f);
        }
    }
    fclose(f);
    return true;
}



void printData(const char * tableName){
    FILE *f;
    int deletedNode;
    char key[4]="\0";
    int title_len=0;
    char title[264]="\0";
    int end=0;

    f = fopen(tableName, "rb");
    if (f == NULL)
    {
        return;
    }
    fseek(f, 0, SEEK_END);
    end=ftell(f);
    fseek(f, 0, SEEK_SET);
    fread(&deletedNode, sizeof(int), 1, f);
    printf("First Deleted node --> %d\n", deletedNode);
    while(ftell(f)!=end){
        if(ftell(f)==deletedNode){
            fread(&deletedNode, sizeof(int), 1, f);
            fread(&title_len, sizeof(int), 1, f);
            fread(title, title_len*sizeof(char), 1, f);
            printf("%d [%d] --> %s\n", deletedNode, title_len, title);
        }
        else{
            fread(key, sizeof(char)*4, 1, f);
            fread(&title_len, sizeof(int), 1, f);
            fread(title, title_len*sizeof(char), 1, f);
            printf("%.4s [%d] --> %s\n", key, title_len, title);
        }


    }
    fclose(f);
    return;
}