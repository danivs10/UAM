#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "products.h"
#include "orders.h"
#include "customers.h"

/*global variables to allow accessing the database*/
/* #include "menu_template.h" */
/* #ifndef A2BIS_MENU_TEMPLATE_H */
/* #define A2BIS_MENU_TEMPLATE_H */

/* Prototypes:
 * Since in this example this functions are not used outside menu_template
 * it does not make sense to create an include file and export them
 * BUT in your code it will make sense to break this file in many files
 * and create several include files with the prototypes
 *
 * A static function in C is a function that has a scope that is limited
 * to its object file. This means that the static function is only
 * visible in its object file. Therefore,
 * you need to remove the static keyword from the declaration
 * if the function is declared in a file and used in another
 * */


static int ShowMainMenu();



/* #endif //A2BIS_MENU_TEMPLATE_H */

/**
 * @file menu_template.c
 * @author rmarabini
 * @date 15 April 2020
 * @brief File containing an example of a menu system with submenus
 *
 * The following program allows a user to select a nursery rhyme
 * or a fairy tail from a menu. The menu has two levels, the top
 * one allows to select between fairy tails or nursery rhymes. The
 * second level (sub-menus) allow to select either a particular
 * rhyme or tail.
 *
 * @see https://bytes.com/topic/c/answers/567136-creating-menus-sub-menus
 */


/**
 * @brief Entry point, shows and process main menu.
 *
 * This function connects to the database, then, 
 * it implements a loop that prints the main
 * menu, analyze the user selection and calls the
 * corresponding submenu. After that it disconnects from 
 * the database.
 *
 * @return 0 if no error
 * @author Daniel Varela & Guillermo de Andres
 */
int main(void) {

    SQLHENV env=NULL;
    SQLHDBC dbc=NULL;
    SQLHSTMT stmt=NULL;
    SQLRETURN ret=0; /* ODBC API return status */
    int ret2=0;
    int nChoice = 0;

    /* CONNECT */
    ret2 = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    if(SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt)!=SQL_SUCCESS){
        return EXIT_FAILURE;
    }

    do {
        nChoice = ShowMainMenu();
        switch (nChoice) {
            case 1: {
                if(SQLProducts(stmt, ret)==-1){
                    return -1;
                }
            }
                break;

            case 2: {
                if(SQLOrders(stmt, ret)==-1){
                    return -1;
                }
            }
                break;

            case 3: {
                if(SQLCustomers(stmt, ret)==-1){
                    return -1;
                }
            }
                break;

            case 4: {
                printf("System closed\n\n");
            }
                break;
        }
    } while (nChoice != 4);
    /* DISCONNECT */
    ret2 = odbc_disconnect(env, dbc);
    if(ret2!=SQL_SUCCESS){
        return EXIT_FAILURE;
    }
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


/**
 * @brief prints main menu and allows to select an option.
 *
 *
 * @return selected entry in the menu
 * @author rmarabini
 */

int ShowMainMenu() {
    int nSelected = 0;
    char buf[16]; /* buffer for reading user input
                     in theory we only need 1 char
                     but a large buffer will handle
                     more gracefully wrong inputs
                     as 'qwerty' */

    do {
        printf("This is a classic cars's database\n");
        printf("You can access the data of all the classic cars purchases\n\n");

        printf(" (1) Products\n"
               " (2) Orders\n"
               " (3) Customers\n"
               " (4) Exit\n\n"
               "Enter a number that corresponds to your choice > ");
        if (!fgets(buf, 16, stdin))
            /* reading input failed, give up: */
            nSelected =0;
        else
            /* have some input, convert it to integer: */
            nSelected = atoi(buf);
        printf("\n");

        if ((nSelected < 1) || (nSelected > 4)) {
            printf("You have entered an invalid choice. Please try again\n\n\n");
        }
    } while ((nSelected < 1) || (nSelected > 4));

    return nSelected;
}

 
     
