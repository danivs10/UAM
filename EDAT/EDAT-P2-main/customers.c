#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "customers.h"


static int ShowCustomersSubMenu();
static int ShowFindCustomers(SQLHSTMT stmt, SQLRETURN ret);
static int ShowListProducts(SQLHSTMT stmt, SQLRETURN ret);
static int ShowBalance(SQLHSTMT stmt, SQLRETURN ret);


/**
 * @brief Shows and processes the Customers menu.
 *
 * This function implements a loop that prints the Customers
 * menu, analyze the user selection and prints
 * the required query. It returns -1 if there was an error and 0 otherwise.
 * @return int 
 * @author Daniel Varela & Guillermo de Andrés
 */
int SQLCustomers(SQLHSTMT stmt, SQLRETURN ret){
    int nChoice = 0;

    do {
        nChoice = ShowCustomersSubMenu();
        switch (nChoice) {
            case 1: {
                if(ShowFindCustomers(stmt, ret)==-1){
                    return 1;
                }
            }
                break;

            case 2: {
                if(ShowListProducts(stmt, ret)==-1){
                    return 1;
                }
            }
                break;

            case 3: {
                if(ShowBalance(stmt, ret)==-1){
                    return 1;
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
 * @brief prints product menu and allows to select an option.
 *
 * @return selected option
 * @author Daniel Varela & Guillermo de Andrés
 */
int ShowCustomersSubMenu(){

    int nSelected = 0;
    char buf[16];

    do {

        printf(" (1) Find\n"
               " (2) List Products\n"
               " (3) Balance\n"
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
 * @brief makes a querry to the database and returns the customers names and codes of the ones that
 * match the search that the user inputs 
 *
 * @input Search
 * @return Customername Contactfirstname ContactLastname and custommernumber of contact's last and 
 *         first names that match your search
 * @author Daniel Varela & Guillermo de Andrés
 */

int ShowFindCustomers(SQLHSTMT stmt, SQLRETURN ret){
    char chain[512]="";
    char chainAux[512]="";
    char contactfirstname[512]="";
    char contactlastname[512]="";
    char customername[512]="";
    int customernumber=0;
    strcpy((char *)chainAux, "%%");


    if(SQLPrepare(stmt, (SQLCHAR*) "select customername, contactfirstname, contactlastname, customernumber from customers where contactfirstname like ? or  contactlastname like ? order by customernumber", SQL_NTS)!=SQL_SUCCESS){
        return -1;
    }
        printf("Enter customer name > ");
    if (fflush(stdout)==-1){
        return -1;
    }
    if(scanf("%[^\n]s", chain)==EOF){
        return -1;   
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

        if(SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_CHAR, SQL_C_CHAR, 0, 0, chainAux, 0, NULL)!=SQL_SUCCESS) return -1;
        if(SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_CHAR, SQL_C_CHAR, 0, 0, chainAux, 0, NULL)!=SQL_SUCCESS) return -1;
        
        if(SQLExecute(stmt)!=SQL_SUCCESS) return -1;
        
        if(SQLBindCol(stmt, 1, SQL_C_CHAR, customername, (SQLLEN)sizeof(customername), NULL)!=SQL_SUCCESS) return -1;
        if(SQLBindCol(stmt, 2, SQL_C_CHAR, contactfirstname, (SQLLEN)sizeof(contactfirstname), NULL)!=SQL_SUCCESS) return -1;
        if(SQLBindCol(stmt, 3, SQL_C_CHAR, contactlastname, (SQLLEN)sizeof(contactlastname), NULL)!=SQL_SUCCESS) return -1;
        if(SQLBindCol(stmt, 4, SQL_INTEGER, &customernumber, (SQLLEN)sizeof(customernumber), NULL)!=SQL_SUCCESS) return -1;

        /* Loop through the rows in the result-set */
        printf("\nNUMBER | NAME | CONTACT NAME & LASTNAME");
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf("\n%d %s %s %s", customernumber, customername, contactfirstname, contactlastname);
        }

        printf("\n\n");
        if(SQLCloseCursor(stmt)!=SQL_SUCCESS) return -1;
    if (fflush(stdout)==-1){
        return -1;
    }
    
    return 0;
}


/**
 * @brief makes a querry to the database and returns the products and quantity that an
 * specific customer (given by the user with it's customer number) has ordered
 *
 * @input Customer number
 * @return Product name & quantity ordered
 * @author Daniel Varela & Guillermo de Andrés
 */

int ShowListProducts(SQLHSTMT stmt, SQLRETURN ret){
    int customernumber=0;
    char productname[512]="";
    int quantityordered=0;


    if(SQLPrepare(stmt, (SQLCHAR*) "select p.productname, sum(od.quantityordered) from orderdetails od join orders o on od.ordernumber = o.ordernumber join products p on od.productcode =p.productcode where customernumber = ? group by p.productname, od.productcode order by od.productcode  ", SQL_NTS)!=SQL_SUCCESS) return -1;
    printf("Enter customer number > ");
    if (fflush(stdout)==-1){
        return -1;
    }
    if(scanf("%d", &customernumber)==EOF){
        return 1;   
    }
    if(getchar()==EOF){
        return -1;
    }

        if(SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_INTEGER, SQL_C_LONG, 0, 0, &customernumber, 0, NULL)!=SQL_SUCCESS) return -1;
        
        if(SQLExecute(stmt)!=SQL_SUCCESS) return -1;
        
        if(SQLBindCol(stmt, 1, SQL_C_CHAR, productname, (SQLLEN)sizeof(productname), NULL)!=SQL_SUCCESS) return -1;
        if(SQLBindCol(stmt, 2, SQL_C_LONG, &quantityordered, (SQLLEN)sizeof(quantityordered), NULL)!=SQL_SUCCESS) return -1;

        /* Loop through the rows in the result-set */
        printf("\n PRODUCT NAME | QUANTITY\n");
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf("\n %s %d ", productname, quantityordered);
        }
        printf("\n\n");
        if(SQLCloseCursor(stmt)!=SQL_SUCCESS) return -1;
    if (fflush(stdout)==-1){
        return -1;
    }
    
    return 0;
}


/**
 * @brief makes a querry to the database and returns the balance between the payed orders
 * minus the sum of the price of all the purchased products
 *
 * @input Customer number
 * @return balance
 * @author Daniel Varela & Guillermo de Andrés
 */
int ShowBalance(SQLHSTMT stmt, SQLRETURN ret){
    
    int customernumber=0;
    float debt=0;


    if(SQLPrepare(stmt, (SQLCHAR*) "select b.amount-a.owed from (select sum(od.priceeach*od.quantityordered) as owed, o.customernumber from orders o join orderdetails od on o.ordernumber =od.ordernumber where o.customernumber = ? group by o.customernumber) as a, (select sum(p.amount)as amount, p.customernumber from payments p where p.customernumber = ? group by p.customernumber) as b group by a.owed, b.amount", SQL_NTS)!=SQL_SUCCESS) return -1;

    printf("Enter customer number > ");
    if (fflush(stdout)==-1){
        return -1;
    }
    if(scanf("%d", &customernumber)==EOF){
        return 1;   
    }
    if(getchar()==EOF){
        return -1;
    }
        if(SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &customernumber, 0, NULL)!=SQL_SUCCESS) return -1;
        if(SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &customernumber, 0, NULL)!=SQL_SUCCESS) return -1;
        
        if(SQLExecute(stmt)!=SQL_SUCCESS) return -1;
        
        if(SQLBindCol(stmt, 1, SQL_C_FLOAT, &debt, (SQLLEN)sizeof(debt), NULL)!=SQL_SUCCESS) return -1;

        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf("\nBalance = %.2f\n", debt);
        }

    if(SQLCloseCursor(stmt)!=SQL_SUCCESS) return -1;
    if (fflush(stdout)==-1){
        return -1;
    }
    printf("\n\n");
    return 0;


}