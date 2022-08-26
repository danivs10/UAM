#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "products.h"


static int ShowProductsSubMenu();
static int ShowStock(SQLHSTMT stmt, SQLRETURN ret);
static int ShowFindProducts(SQLHSTMT stmt, SQLRETURN ret);

/**
 * @brief Shows and processes the Products menu.
 *
 * This function implements a loop that prints the Product
 * menu, analyze the user selection and prints
 * the required query. It returns -1 if there was an error and 0 otherwise.
 * @return int 
 * @author Daniel Varela & Guillermo de Andrés
 */

int SQLProducts(SQLHSTMT stmt, SQLRETURN ret){
    int nChoice = 0;

    do {
        nChoice = ShowProductsSubMenu();
        switch (nChoice) {
            case 1: {
                if(ShowStock(stmt, ret)==-1){
                    return -1;
                }
            }
                break;

            case 2: {
                if(ShowFindProducts(stmt, ret)==-1){
                    return -1;
                }
            }
                break;

            case 3: {
            }
                break;
        }
    } while (nChoice != 3);

    return 0;
} 



/**
 * @brief prints product menu and allows to select an option.
 *
 * @return selected option
 * @author Daniel Varela & Guillermo de Andrés
 */

int ShowProductsSubMenu(){

    int nSelected = 0;
    char buf[16];
    
    do {

        printf(" (1) Stock\n"
               " (2) Find\n"
               " (3) Back\n\n");

        printf("Enter a number that corresponds to your choice > ");
        if (!fgets(buf, 16, stdin))
            /* reading input failed, give up: */
            nSelected =0;
        else
            /* have some input, convert it to integer: */
            nSelected = atoi(buf);
        printf("\n");

        if ((nSelected < 1) || (nSelected > 3)) {
            printf("You have entered an invalid choice. Please try again\n\n\n");
        }
    } while ((nSelected < 1) || (nSelected > 3));

    return nSelected;
}

    
/**
 * @brief makes a querry to the database and returns the quantity in stock
 * of a product given a specific product code that the user must introduce
 *
 * @input Product code
 * @return Stock of a product
 * @author Daniel Varela & Guillermo de Andrés
 */


int ShowStock(SQLHSTMT stmt, SQLRETURN ret){
    char productCode[512]="";
    char stock[512]="";

    if(SQLPrepare(stmt, (SQLCHAR*) "select quantityInStock from products where productCode=?", SQL_NTS)!=SQL_SUCCESS){
            return -1;
    }

        printf("Enter productcode > ");
    if (fflush(stdout)==-1){
        return -1;
    }
    if(scanf("%s", productCode)==EOF){
        return 1;   
    }    
    if(getchar()==EOF){
        return -1;
    }
        if(SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_CHAR, SQL_C_CHAR, 0, 0, productCode, 0, NULL)!=SQL_SUCCESS){
            return -1;
    }
        
        if(SQLExecute(stmt)!=SQL_SUCCESS){
            return -1;
    }
        
        if(SQLBindCol(stmt, 1, SQL_C_CHAR, stock, (SQLLEN)sizeof(stock), NULL)!=SQL_SUCCESS){
            return -1;
    }

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf("\nQuantity in Stock : %s\n\n", stock);
        }

        if(SQLCloseCursor(stmt)!=SQL_SUCCESS){
            return -1;
    }
    if (fflush(stdout)==-1){
        return -1;
    }
    
    printf("\n");
    return 0;

}




/**
 * @brief makes a querry to the database and returns the products names and codes of the ones that
 * match the search that the user inputs 
 *
 * @input Search
 * @return Name and code of products that match your search
 * @author Daniel Varela & Guillermo de Andrés
 */

int ShowFindProducts(SQLHSTMT stmt, SQLRETURN ret){
    char chain[100]="";
    char chainAux[100]="";
    char productname[100]="";
    char productcode[10]="";
    strcpy(chainAux, "%%");


    if(SQLPrepare(stmt, (SQLCHAR*) "select productname,productcode from products where productname like ? order by productcode;", SQL_NTS)!=SQL_SUCCESS){
            return -1;
    }
        printf("Enter productname > ");
    if (fflush(stdout)==-1){
        return -1;
    }
    if(scanf("%[^\n]s", chain)==EOF){
        return 1;   
    }
    if(getchar()==EOF){
        return -1;
    }
        if(strcat((char *)chainAux, (char *)chain)==NULL){
            return -1;
        }
        if(strcat((char *)chainAux, "%%")==NULL){
            return -1;
        }
        if(SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_CHAR, SQL_C_CHAR, 0, 0, chainAux, 0, NULL)!=SQL_SUCCESS){
            return -1;
    }
        
        if(SQLExecute(stmt)!=SQL_SUCCESS){
            return -1;
    }
        
        if(SQLBindCol(stmt, 1, SQL_C_CHAR, productname, (SQLLEN)sizeof(productname), NULL)!=SQL_SUCCESS){
            return -1;
    }
        if(SQLBindCol(stmt, 2, SQL_C_CHAR, productcode, (SQLLEN)sizeof(productcode), NULL)!=SQL_SUCCESS){
            return -1;
    }

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf("\nproduct name : %s", productname);
            printf("\nproduct code : %s\n\n", productcode);
        }

        if(SQLCloseCursor(stmt)!=SQL_SUCCESS){
            return -1;
    }
    if (fflush(stdout)==-1){
        return -1;
    }
    return 0;
}




