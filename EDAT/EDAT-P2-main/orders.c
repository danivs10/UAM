#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "orders.h"

static int ShowOrdersSubMenu();
static int ShowOpen(SQLHSTMT stmt, SQLRETURN ret);
static int ShowRange(SQLHSTMT stmt, SQLRETURN ret);
static int ShowDetails(SQLHSTMT stmt, SQLRETURN ret);


/**
 * @brief Shows and processes the Orders menu.
 *
 * This function implements a loop that prints the Orders
 * menu, analyze the user selection and prints
 * the required query. It returns -1 if there was an error and 0 otherwise.
 * @return int 
 * @author Daniel Varela & Guillermo de Andrés
 */
int SQLOrders(SQLHSTMT stmt, SQLRETURN ret){
    int nChoice = 0;

    do {
        nChoice = ShowOrdersSubMenu();
        switch (nChoice) {
            case 1: {
                if(ShowOpen(stmt, ret)==-1){
                    return -1;
                }
            }
                break;

            case 2: {
                if(ShowRange(stmt, ret)==-1){
                    return -1;
                }
            }
                break;

            case 3: {
                if(ShowDetails(stmt, ret)==-1){
                    return -1;
                }
            }
                break;

            case 4: {
            }
                break;
        }
    } while (nChoice != 4);

    return 0;

} 


/**
 * @brief prints Orders menu and allows to select an option.
 *
 * @return selected option
 * @author Daniel Varela & Guillermo de Andrés
 */
int ShowOrdersSubMenu(){

    int nSelected = 0;
    char buf[16];

    do {

        printf(" (1) Open\n"
               " (2) Range\n"
               " (3) Detail\n"
               " (4) Back\n\n");

        printf("Enter a number that corresponds to your choice > ");
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


/**
 * @brief makes a querry to the database that returns all the products with a 
 * shippeddate=NULL hence, all the orders that have not been sent
 *
 * 
 * @return ordernumber
 * @author Daniel Varela & Guillermo de Andrés
 */

int ShowOpen(SQLHSTMT stmt, SQLRETURN ret){
    char ordernumber[512]="";
    if(SQLExecDirect(stmt, (SQLCHAR*) "select ordernumber from orders where shippeddate is null order by ordernumber", SQL_NTS)!=SQL_SUCCESS){
        return -1;
    }
    printf("\n");
    if(SQLBindCol(stmt, 1, SQL_C_CHAR, ordernumber, (SQLLEN)sizeof(ordernumber), NULL)!=SQL_SUCCESS){
        return -1;
    }
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        printf("\nPending order number : %s\n\n", ordernumber);
    }
    if(SQLCloseCursor(stmt)!=SQL_SUCCESS){
        return -1;
    }
    return 0;

}


/**
 * @brief This function asks for two dates and it returns all the orders made in
 * between those dates.
 *
 * @input Two dates in the following format: YYYY-MM-DD - YYYY-MM-DD
 * @return OrderNumber, OrderDate and ShippedDate
 * @author Daniel Varela & Guillermo de Andrés
 */

int ShowRange(SQLHSTMT stmt, SQLRETURN ret){
    
    char separation[3]="";
    char startdate[512]="";
    char enddate[512]="";
    char ordernumber[512]="";
    char orderdate[512]="";
    char shippeddate[512]="";


    if(SQLPrepare(stmt, (SQLCHAR*) "select ordernumber, orderdate, shippeddate from orders where orderdate between ? and  ?", SQL_NTS)!=SQL_SUCCESS){
        return -1;
    }

        printf("Enter dates (YYYY-MM-DD - YYYY-MM-DD) > ");
    if (fflush(stdout)==-1){
        return -1;
    }
    if(scanf("%s%s%s", startdate, separation, enddate)==EOF){
        return 1;   
    }
    if(getchar()==EOF){
        return -1;
    }
        if(SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_CHAR, SQL_C_CHAR, 0, 0, startdate, 0, NULL)!=SQL_SUCCESS){
        return -1;
    }
        if(SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_CHAR, SQL_C_CHAR, 0, 0, enddate, 0, NULL)!=SQL_SUCCESS){
        return -1;
    }
        
        if(SQLExecute(stmt)!=SQL_SUCCESS){
        return -1;
    }
        
        if(SQLBindCol(stmt, 1, SQL_C_CHAR, ordernumber, (SQLLEN)sizeof(ordernumber), NULL)!=SQL_SUCCESS){
        return -1;
    }
        if(SQLBindCol(stmt, 2, SQL_C_CHAR, orderdate, (SQLLEN)sizeof(orderdate), NULL)!=SQL_SUCCESS){
        return -1;
    }
        if(SQLBindCol(stmt, 3, SQL_C_CHAR, shippeddate, (SQLLEN)sizeof(shippeddate), NULL)!=SQL_SUCCESS){
        return -1;
    }

        /* Loop through the rows in the result-set */
        printf("Orders:\nNUMBER | ORDERDATE | SHIPPEDDATE");
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf("\n  %s %s %s", ordernumber,orderdate, shippeddate);
           /* printf("\nOrder Date : %s", orderdate);
            printf("\nShipped Date : %s\n\n", shippeddate);*/
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
 * @brief This function asks for a productnumber and it returns it's orderdate
 * its status, the total price and then a list containing all the products purchased
 * with its productcode, the quantity ordered and the price 
 *
 * @input ProductNumber
 * @return OrderDate, Status, Order price
 * @return productcode, quantity, price
 * @author Daniel Varela & Guillermo de Andrés
 */

int ShowDetails(SQLHSTMT stmt, SQLRETURN ret){
    
    int ordernumber=0;
    char orderdate[512]="";
    char status[512]="";
    float cost=0.000000;
    char productcode[512]="";
    int quantityordered=0;
    float priceeach=0;


    if(SQLPrepare(stmt, (SQLCHAR*) "select o.orderdate, o.status, sum(od.priceeach*od.quantityordered) from orders o join orderdetails od on o.ordernumber = od.ordernumber where o.ordernumber = ? group by o.orderdate, o.status;", SQL_NTS)!=SQL_SUCCESS){
        return -1;
    }

        printf("Enter ordernumber > ");
    if (fflush(stdout)==-1){
        return -1;
    }
    if(scanf("%d", &ordernumber)==EOF){
        return 1;   
    }    
    if(getchar()==EOF){
        return -1;
    }
        if(SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &ordernumber, 0, NULL)!=SQL_SUCCESS){
        return -1;
    }
        
        if(SQLExecute(stmt)!=SQL_SUCCESS){
        return -1;
    }
        
        if(SQLBindCol(stmt, 1, SQL_C_CHAR, orderdate, (SQLLEN)sizeof(orderdate), NULL)!=SQL_SUCCESS){
        return -1;
    }
        if(SQLBindCol(stmt, 2, SQL_C_CHAR, status, (SQLLEN)sizeof(status), NULL)!=SQL_SUCCESS){
        return -1;
    }  
        if(SQLBindCol(stmt, 3, SQL_C_FLOAT, &cost, (SQLLEN)sizeof(cost), NULL)!=SQL_SUCCESS){
        return -1;
    }

 
        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf("\nOrder Date=%s - status=%s \n \n", orderdate,status );

            printf("Total sum = %.2f0000 $ \n \n", cost);
        }

        if(SQLCloseCursor(stmt)!=SQL_SUCCESS){
        return -1;
    }
    if (fflush(stdout)==-1){
        return -1;
    }

    if(SQLPrepare(stmt, (SQLCHAR*) "select productcode, quantityordered, priceeach from orderdetails where ordernumber = ? order by orderlinenumber;", SQL_NTS)!=SQL_SUCCESS){
        return -1;
    }
        if(SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &ordernumber, 0, NULL)!=SQL_SUCCESS){
        return -1;
    }
        
        if(SQLExecute(stmt)!=SQL_SUCCESS){
        return -1;
    }
        
        if(SQLBindCol(stmt, 1, SQL_C_CHAR, productcode, (SQLLEN)sizeof(productcode), NULL)!=SQL_SUCCESS){
        return -1;
    }
        if(SQLBindCol(stmt, 2, SQL_C_LONG, &quantityordered, (SQLLEN)sizeof(quantityordered), NULL)!=SQL_SUCCESS){
        return -1;
    }
        if(SQLBindCol(stmt, 3, SQL_C_FLOAT, &priceeach, (SQLLEN)sizeof(priceeach), NULL)!=SQL_SUCCESS){
        return -1;
    }

        printf("Order details (productcode - quantity - price):");
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf("\n %s %d %.2f $", productcode, quantityordered, priceeach);
        }

        if(SQLCloseCursor(stmt)!=SQL_SUCCESS){
        return -1;
    }
    if (fflush(stdout)==-1){
        return -1;
    }
    
    printf("\n\n");
    return 0;

}