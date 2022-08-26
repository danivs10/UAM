%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "alfa.h"

    void yyerror(const char* e);
    extern int yylex();
    extern FILE *yyin;
    extern FILE *yyout;
    extern char *yytext;
    extern int yyleng;
    extern int l;
    extern int pos;
    extern int e;

    int tipo_actual;
    int clase_actual;

    int value_scalar_actual;        /* Scalar value*/
    int vector_size;                /* Vector size */

    int pos_local_var_act=0;        /* Actual local variable position */
    int loc_var_num=0;              /* Number of local variables*/
    int param_act_num = 0;          /* Actual number of parametres */
    int pos_param_act = 0;          /* Actual parametre position */
    int param_call_act_num = 0;     /* Actual number of parametres in a call */
    int en_explist = 0;
    int vector_size_act = 0;        /* Actual size of the vector*/

    Hash_Table *GlobalTable;        /* Global table of symbols */
    Hash_Table *LocalTable;         /* Local table of symbols */
    Hash_Table *CurrentTable=NULL;       /* Indicates if we are in the local table or in the global */

    Simbol *aux=NULL;

    int is_func = 0;                /* Indicates if we are passing a parametre in the funccion */
    int fn_return = 0;              /* Indicates if it is return */
    int return_type = 0;            /* Indicates the return type*/
    int num_no = 0;                 /* Number of arithmetic negations */
    int num_comp = 0;               /* Number of comparations */
    int num_cond = 1;               /* Number of conditions */
    int en_explist;                 /* Function instead of parameter */  
    int num_loop = 0;               /* Counter for the loops operations */
    int num_parametros_llamada_actual;/*Numero de parametros de la llamada actual*/
%}

%union {
    char *string;
    int number;
    type_atributes atributos;
}

%token <atributos> TOK_CONSTANTE_ENTERA
%token <atributos> TOK_CONSTANTE_REAL
%token <atributos> TOK_IDENTIFICADOR

%token TOK_MAIN
%token TOK_INT
%token TOK_BOOLEAN
%token TOK_ARRAY
%token TOK_FUNCTION
%token TOK_IF
%token TOK_ELSE
%token TOK_WHILE
%token TOK_SCANF
%token TOK_PRINTF
%token TOK_RETURN

%token TOK_PUNTOYCOMA
%token TOK_COMA
%token TOK_PARENTESISIZQUIERDO
%token TOK_PARENTESISDERECHO
%token TOK_CORCHETEIZQUIERDO
%token TOK_CORCHETEDERECHO
%token TOK_LLAVEIZQUIERDA
%token TOK_LLAVEDERECHA
%token TOK_ASIGNACION
%token TOK_MAS
%token TOK_MENOS
%token TOK_DIVISION
%token TOK_ASTERISCO
%token TOK_AND
%token TOK_OR
%token TOK_NOT
%token TOK_IGUAL
%token TOK_DISTINTO
%token TOK_MENORIGUAL
%token TOK_MAYORIGUAL
%token TOK_MENOR
%token TOK_MAYOR
%token TOK_TRUE
%token TOK_FALSE

%token TOK_ERROR

/*%type <atributos> idf_llamada_funcion*/
%type <atributos> fn_declaracion
%type <atributos> fn_name
%type <atributos> condicional
%type <atributos> comparacion
%type <atributos> elemento_vector
%type <atributos> exp
%type <atributos> constante
%type <atributos> constante_entera
%type <atributos> constante_logica
%type <atributos> identificador
%type <atributos> if_exp
%type <atributos> if_exp_else
%type <atributos> while
%type <atributos> while_exp
%type <atributos> en_explist_act

%left TOK_ASIGNACION
%left TOK_OR TOK_AND
%left TOK_IGUAL TOK_DISTINTO
%left TOK_MAYOR TOK_MAYORIGUAL TOK_MENOR TOK_MENORIGUAL
%left TOK_MAS TOK_MENOS
%left TOK_ASTERISCO TOK_DIVISION
%left TOK_NOT
%left TOK_CORCHETEIZQUIERDO 
%left TOK_CORCHETEDERECHO
%left TOK_PARENTESISIZQUIERDO
%left TOK_PARENTESISDERECHO

%start programa

%%

/*-------------------------Regla 1--------------------------------*/
programa: init TOK_MAIN TOK_LLAVEIZQUIERDA declaraciones escritura1 funciones escritura2 sentencias TOK_LLAVEDERECHA {
    fprintf(yyout, ";R1:\t<programa> ::= main { <declaraciones> <funciones> <sentencias> }\n");
    escribir_fin(yyout);
    finish();
};

init: {
    /* Declaramos la tabla de simbolos local para la función main y que las
        declaraciones siguientes se añadan a la tabla local */
    GlobalTable = creat_hash_table();
    CurrentTable = GlobalTable;
    num_no = 0;
    escribir_subseccion_data(yyout);
    escribir_cabecera_bss(yyout);
};

escritura1: {
    /* Llamada a funciones para escribir la sección data con los mensajes
    generales, y la
    tabla de símbolos así como todo lo necesario para que lo siguiente que
    haya que escribirse
    sea main: */
    
    escribir_segmento_codigo(yyout); 
};

/*-----------------Escritura main---------------------------------*/
escritura2: {
    /* Aquí ya se podría llamar a la función que escribe inicio main */
    escribir_inicio_main(yyout);
};

/*-------------------------Regla 2--------------------------------*/
declaraciones: declaracion {
        fprintf(yyout, ";R2:\t<declaraciones> ::= <declaracion>\n");
    }
    /*-----------------------Regla 3--------------------------*/
    | declaracion declaraciones {
        fprintf(yyout, ";R3:\t<declaraciones> ::= <declaracion> <declaraciones>\n");
    
    };

/*--------------------------Regla 4------------------------------*/
declaracion: clase identificadores TOK_PUNTOYCOMA {
    /* Añadir el identificador a la tabla de símbolos */
    fprintf(yyout, ";R4:\t<declaracion> ::= <clase> <identificadores> ;\n");
};

/*---------------------------Regla 5-----------------------------*/
clase: clase_escalar {
        clase_actual = ESCALAR;
        fprintf(yyout, ";R5:\t<clase> ::= <clase_escalar>\n");
    }
    /*------------------------------Regla 7 ----------------------*/
    | clase_vector {
        clase_actual = VECTOR;
        fprintf(yyout, ";R7:\t<clase> ::= <clase_vector>\n");
    };

/*---------------------------------Regla 9 ---------------------------*/
clase_escalar: tipo {
    fprintf(yyout, ";R9:\t<clase_escalar> ::= <tipo>\n");
};

/*------------------------------Regla 10-----------------------------*/
tipo: TOK_INT {
        tipo_actual = INT;
        fprintf(yyout, ";R10:\t<tipo> ::= int\n");
    } 
    /*--------------------------Regla 11-------------------------*/
    | TOK_BOOLEAN {
        tipo_actual = BOOLEAN;
        fprintf(yyout, ";R11:\t<tipo> ::= boolean\n");
    };

/*-----------------------Regla 15-------------------------------*/
clase_vector: TOK_ARRAY tipo TOK_CORCHETEIZQUIERDO constante_entera TOK_CORCHETEDERECHO {
    vector_size_act = $4.valor_entero;
    if((vector_size_act < 1) || (vector_size_act > MAX_VECTOR_SIZE)){
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Vector fuera de rango. Rango (1, 64)\n", l, pos);
        finish();
        return -1;
    }
    fprintf(yyout, ";R15:\t<clase_vector> ::= array <tipo> [ <constante_entera> ]\n");
};

/*-------------------------Regla 18-----------------------------*/
identificadores: identificador {
        fprintf(yyout, ";R18:\t<identificadores> ::= <identificador>\n");
    };
    /*---------------------Regla 19------------------------------*/
    | identificador TOK_COMA identificadores {
        fprintf(yyout, ";R19:\t<identificadores> ::= <identificador> , <identificadores>\n");
    };

/*------------------------Regla 20------------------------------*/
funciones: funcion funciones {
        fprintf(yyout, ";R20:\t<funciones> ::= <funcion> <funciones>\n");
    }
    /*-------------------Regla 21-------------------------*/
    |  {
        fprintf(yyout, ";R21:\t<funciones> ::= \n");
    };

/*------------------------------Regla 22--------------------------------*/
funcion: fn_declaracion sentencias TOK_LLAVEDERECHA {
    hash_table_delete(LocalTable); 
    LocalTable = NULL;

    aux = isGlobal($1.lexema);

    if(aux==NULL){
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, variable not in global table\n", l, pos);
        finish();
        return -1;
    }
    
    if(fn_return == 0){
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, function without return statement\n", l, pos);
        finish();
        return -1;
    }
    
    if(return_type != aux->tipo){
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, incorrect return type\n", l, pos);
        finish();
        return -1;
    }
    
    fprintf(yyout, ";R22:<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }\n");
};

/*---------------------------Añadimos Regla fn_declaración-----------------*/
fn_declaracion: fn_name TOK_PARENTESISIZQUIERDO parametros_funcion TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA declaraciones_funcion {
        
    aux = isLocal($1.lexema);
    aux->param = param_act_num;
    aux->localVar = loc_var_num;

    aux = isGlobal($1.lexema);
    aux->param = param_act_num;
    aux->localVar = loc_var_num;

    strcpy($$.lexema, $1.lexema);

    declararFuncion(yyout, $1.lexema, loc_var_num);
};

/*------------Añadimos regla fn_nombre (se refiere al nombre de la función)----------------*/
fn_name: TOK_FUNCTION tipo TOK_IDENTIFICADOR {
    aux = get_value_from_hstable(GlobalTable, $3.lexema, sizeof($3.lexema));
    

    if(aux == NULL){
        aux = simboloinit($3.lexema, FUNCION, ESCALAR, tipo_actual, sizeof($3.lexema), 0, 0, 0, 0);
        if(aux == NULL) {
            finish();
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error when initializing the symbol\n", l, pos);
            return -1;
        }
        if(functionDeclaration($3.lexema, aux)==0) {
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error when declarating the function\n", l, pos);
            finish();
            return-1;
        }
        pos_local_var_act=1;
        loc_var_num=0;
        param_act_num = 0;
        pos_param_act = 0;
        vector_size_act = 0;
        $$.tipo = tipo_actual;
        strcpy($$.lexema, $3.lexema);
        fn_return=0;
        
    }else{
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, duplicated declaration\n", l, pos);
        finish();
        return -1;
    }
};
    
        
/*--------------------------------Regla 23-----------------------------------*/
parametros_funcion: parametro_funcion resto_parametros_funcion {
        fprintf(yyout, ";R23:\t<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>\n");
    }
    /*--------------------------Regla 24----------------------------------*/
    |  {
        fprintf(yyout, ";R24:\t<parametros_funcion> ::=\n");
    };

/*----------------------Regla 25-------------------------------------*/
resto_parametros_funcion: TOK_PUNTOYCOMA parametro_funcion resto_parametros_funcion {
        fprintf(yyout, ";R25:\t<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion>\n");
    }
    /*---------------------------Regla 26------------------------------------*/
    |  {
        fprintf(yyout, ";R26:\t<resto_parametros_funcion> ::=\n");
    };

/*--------------------------Regla 27------------------------------------*/
parametro_funcion: tipo idpf {
    fprintf(yyout, ";R27:\t<parametro_funcion> ::= <tipo> <identificador>\n");
};

/*--------------------------IDPF------------------------------------*/
idpf: TOK_IDENTIFICADOR {
    Simbol *s = NULL;

    if(!LocalTable){
        finish();
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, the local table doesnt exist\n", l, pos);
        return -1;
    }
    s = isLocal($1.lexema);
    if (s){
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, duplicated variable\n", l, pos);
        finish();
        return -1;
    }else{
        s = simboloinit($1.lexema, PARAMETRO, ESCALAR, tipo_actual, sizeof($1.lexema), 0, 0, 0, pos_param_act);
        if(s == NULL){
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, symbol not created properly\n", l, pos);
            finish();
            return -1;
        }
        if(add_node2HashTable(LocalTable, $1.lexema, sizeof($1.lexema), s)==0){
            pos_param_act++;
            param_act_num++;
        }else{
            fprintf(stderr, "****Error Semantico en la linea %d: Repeated node.\n",l);
            finish();
            return -1;
        }
    }
    
}

/*---------------------------Regla 28-------------------------------------*/
declaraciones_funcion: declaraciones {
        fprintf(yyout, ";R28:\t<declaraciones_funcion> ::= <declaraciones>\n");
    }
    /*-------------------------Regla 29---------------------------------*/
    |  {
        fprintf(yyout, ";R29:\t<declaraciones_funcion> ::= \n");
    };

/*---------------------------Regla 30-----------------------------------------*/
sentencias: sentencia {
        fprintf(yyout, ";R30:\t<sentencias> ::= <sentencia>\n");
    }
    /*----------------------Regla 31-----------------------------------*/
    | sentencia sentencias {
        fprintf(yyout, ";R31:\t<sentencias> ::= <sentencia> <sentencias>\n");
    };

/*------------------------------Regla 32---------------------------------*/
sentencia: sentencia_simple TOK_PUNTOYCOMA {
        fprintf(yyout, ";R32:\t<sentencia> ::= <sentencia_simple> ;\n");
    }
    /*-------------------------Regla 33---------------------------------------*/
    | bloque {
        fprintf(yyout, ";R33:\t<sentencia> ::= <bloque>\n");
    };

/*---------------------------Regla 34-----------------------------------------*/
sentencia_simple: asignacion {
        fprintf(yyout, ";R34:\t<sentencia_simple> ::= <asignacion>\n");
    }
    /*---------------------------Regla 35-----------------------------------------*/
    | lectura {
        fprintf(yyout, ";R35:\t<sentencia_simple> ::= <lectura>\n");
    }
    /*---------------------------Regla 36-----------------------------------------*/
    | escritura {
        fprintf(yyout, ";R36:\t<sentencia_simple> ::= <escritura>\n");
    }
    /*---------------------------Regla 38-----------------------------------------*/
    | retorno_funcion {
        fprintf(yyout, ";R38:\t<sentencia_simple> ::= <retorno_funcion>\n");
    };

/*---------------------------Regla 40-----------------------------------------*/
bloque: condicional {
        fprintf(yyout, ";R40:\t<bloque> ::= <condicional>\n");
    }
    /*---------------------------Regla 41-----------------------------------------*/
    | bucle {
        fprintf(yyout, ";R41:\t<bloque> ::= <bucle>\n");
    };

/*-------------------------Regla 43-----------------------------------------*/
asignacion: TOK_IDENTIFICADOR TOK_ASIGNACION exp {
        Simbol *s = NULL;
        s = searchSimbolInTables(LocalTable, GlobalTable, $1.lexema);
        if(s==NULL) {
            fprintf(stderr, "****Error Semantico en la linea %d: Acceso a variable no declarada (%s).\n",l,$1.lexema);
            finish();
            return -1;
        }
        if (s->categoria==FUNCION || s->clase==VECTOR || s->tipo!=$3.tipo) {
            fprintf(stderr, "****Error Semantico en la linea %d: Asignacion incompatible.\n",l);
            finish();
            return -1;
        }
        
        if (LocalTable==NULL){
            asignar(yyout, $1.lexema, $3.es_direccion);
        }
        else {
            if (s->categoria==PARAMETRO){
                    escribirParametro(yyout, s->paramPos, param_act_num);
            }
            else{
                    escribirVariableLocal(yyout, s->localVarPos);
            }
            invertirEnPila(yyout);
            asignarDestinoEnPila(yyout, $3.es_direccion);
        }
        fprintf(yyout, ";R43:\t<asignacion> ::= <identificador> = <exp>\n");
    }
    /*---------------------------Regla 44-----------------------------------------*/
    | elemento_vector TOK_ASIGNACION exp {
        Simbol * aux;

        fprintf(yyout, ";R44:\t<asignacion> ::= <elemento_vector> = <exp>\n");
        
        aux = searchSimbolInTables(LocalTable,GlobalTable,$1.lexema);

        if(aux == NULL){
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, variable no declarada\n", l, pos);
            finish();
            return -1;
        }
        if(aux->tipo != $3.tipo){
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, intento de indexacion de una variable que no es de tipo vector\n", l, pos);
            finish();
            return -1;
        }
        /*escribir_elemento_vector(yyout, $1.lexema, vector_size, $3.es_direccion);*/
        asignarDestinoEnPila(yyout, $3.es_direccion);
    };

/*-------------------------Regla 48-----------------------------------------*/
elemento_vector: TOK_IDENTIFICADOR TOK_CORCHETEIZQUIERDO exp TOK_CORCHETEDERECHO {
    Simbol *aux;

    aux = get_value_from_hstable(GlobalTable, $1.lexema, sizeof($1.lexema));
    if(aux==NULL) {
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Variable not declared %s\n", l, pos, $1.lexema);
        finish();
        return -1;
    }

    if(aux->clase != VECTOR){
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, The variable is not of type vector, you cannot index it\n", l, pos);
        finish();
        return -1;
    }

    if($3.tipo != INT){
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, The variable is not of type vector, you cannot index it\n", l, pos);
        finish();
        return -1;
    }

    if(en_explist == 0){
        escribir_elemento_vector(yyout, $1.lexema, aux->tamanio, $3.es_direccion);
    }else{
        escribir_elemento_vector(yyout, $1.lexema, aux->tamanio, $3.es_direccion);
        operandoEnPilaAArgumento(yyout,1);
    }

    $$.tipo = aux->tipo;
    $$.es_direccion = 1;
    strcpy($$.lexema, $1.lexema);
    vector_size = aux->tamanio;

    fprintf(yyout, ";R48:\t<elemento_vector> ::= <identificador> [ <exp> ]\n");
};

/*-------------------------Regla 50-----------------------------------------*/
condicional: if_exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA {
        ifthen_fin(yyout, $1.etiqueta);
        fprintf(yyout, ";R50:\t<condicional> ::= if ( <exp> ) { <sentencias> }\n");
    }
    /*-------------------------Regla 51-----------------------------------------*/
    | if_exp_else TOK_ELSE TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA {
        ifthenelse_fin(yyout, $1.etiqueta);
        fprintf(yyout, ";R51:\t<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }\n");
    };

if_exp_else: if_exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA{
    $$.etiqueta=$1.etiqueta;
    ifthenelse_fin_then(yyout, $$.etiqueta);
};

if_exp: TOK_IF TOK_PARENTESISIZQUIERDO exp {
    if($3.tipo != BOOLEAN){
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, condicional con condicion de tipo int\n", l, pos);
        finish();
        return -1;
    }

    $$.etiqueta = num_cond++;
    ifthen_inicio(yyout, $3.es_direccion, $$.etiqueta);
};

/*---------------------------Regla 52-----------------------------------------*/
while: TOK_WHILE TOK_PARENTESISIZQUIERDO{
    num_loop++;
    while_inicio(yyout, num_loop);
}

while_exp: while exp {
    if ($2.tipo!=BOOLEAN) {
        fprintf(stderr, "****Error sintactico en [lin %d, col %d]: Bucle con condicion de tipo int.\n", l, pos);       
    }
    while_exp_pila(yyout, $2.es_direccion, num_loop);
}

bucle: while_exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA {
    while_fin(yyout, num_loop);
    fprintf(yyout,";R52:\t<bucle> ::= while ( <exp> ) { <sentencias> }\n");
};

/*---------------------------Regla 54-----------------------------------------*/
lectura: TOK_SCANF TOK_IDENTIFICADOR {
    Simbol *s = NULL;
    s = searchSimbolInTables(LocalTable, GlobalTable, $2.lexema);
    if(s==NULL) {
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Variable not declared %s\n", l, pos, $2.lexema);
        finish();
        return -1;
    }
    if (s->categoria==FUNCION || s->categoria==VECTOR) {
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Incorrect category\n", l, pos);
        finish();
        return -1;
    }
    
    if (LocalTable!=NULL) {
        if (s->categoria==PARAMETRO){
            escribirParametro(yyout, s->paramPos, param_act_num);
        }
        else{
            escribirVariableLocal(yyout, s->localVarPos);
        }
    }
    leer(yyout, $2.lexema, s->tipo);
    fprintf(yyout,";R54:\t<lectura> ::= scanf <identificador>\n");
};

/*---------------------------Regla 56-----------------------------------------*/
escritura: TOK_PRINTF exp {
    fprintf(yyout,";R56:\t<escritura> ::= printf <exp>\n");
    escribir(yyout, $2.es_direccion, $2.tipo);
    
};

/*---------------------------Regla 61-----------------------------------------*/
retorno_funcion: TOK_RETURN exp {
    fprintf(yyout,";R61:\t<retorno_funcion> ::= return <exp>\n");
    if(LocalTable == NULL){
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Trying to return out of a function\n", l, pos);
        finish();
        return -1;
    }
    retornarFuncion(yyout,$2.es_direccion);
    return_type = $2.tipo;
    fn_return++;

};

/*---------------------------Regla 72-----------------------------------------*/
exp: exp TOK_MAS exp {
        if($1.tipo != INT || $3.tipo != INT) {
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Non compatible types\n", l, pos);
            finish();
            return -1;
        }
        $$.tipo = INT;
        $$.es_direccion = 0;
        sumar(yyout, $1.es_direccion, $3.es_direccion);
        fprintf(yyout, ";R72:\t<exp> ::= <exp> + <exp>\n");
    }
    /*---------------------------Regla 73-----------------------------------------*/
    | exp TOK_MENOS exp {
        if($1.tipo != INT || $3.tipo != INT) {
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Non compatible types\n", l, pos);
            finish();
            return -1;
        }
        $$.tipo = INT;
        $$.es_direccion = 0;
        restar(yyout, $1.es_direccion, $3.es_direccion);
        fprintf(yyout, ";R73:\t<exp> ::= <exp> - <exp>\n");
    }
    /*---------------------------Regla 74-----------------------------------------*/
    | exp TOK_DIVISION exp {
        if($1.tipo != INT || $3.tipo != INT) {
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Non compatible types\n", l, pos);
            finish();
            return -1;
        }
        $$.tipo = INT;
        $$.es_direccion = 0;
        dividir(yyout, $1.es_direccion, $3.es_direccion);
        fprintf(yyout, ";R74:\t<exp> ::= <exp> / <exp>\n");
    }
    /*---------------------------Regla 75-----------------------------------------*/
    | exp TOK_ASTERISCO exp {
        if($1.tipo != INT || $3.tipo != INT) {
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Non compatible types\n", l, pos);
            finish();
            return -1;
        }
        $$.tipo = INT;
        $$.es_direccion = 0;
        multiplicar(yyout, $1.es_direccion, $3.es_direccion);
        fprintf(yyout, ";R75:\t<exp> ::= <exp> * <exp>\n");
    }
    /*---------------------------Regla 76-----------------------------------------*/
    | TOK_MENOS exp {
        if($2.tipo != INT) {
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Non compatible types\n", l, pos);
            finish();
            return -1;
        }
        $$.tipo=INT;
        $$.es_direccion=0;
        cambiar_signo(yyout, $2.es_direccion);
        fprintf(yyout, ";R76:\t<exp> ::= - <exp>\n");
    }
    /*---------------------------Regla 77-----------------------------------------*/
    | exp TOK_AND exp {
        if($1.tipo != BOOLEAN || $3.tipo != BOOLEAN) {
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Non compatible types\n", l, pos);
            finish();
            return -1;
        }
        
        $$.tipo=BOOLEAN;
        $$.es_direccion=0;
        y(yyout, $1.es_direccion, $3.es_direccion);
        fprintf(yyout, ";R77:\t<exp> ::= <exp> && <exp>\n");
    }
    /*---------------------------Regla 78-----------------------------------------*/
    | exp TOK_OR exp {
        if($1.tipo != BOOLEAN || $3.tipo != BOOLEAN) {
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Non compatible types\n", l, pos);
            finish();
            return -1;
        }
        
        $$.tipo=BOOLEAN;
        $$.es_direccion=0;
        o(yyout, $1.es_direccion, $3.es_direccion);
        fprintf(yyout, ";R78:\t<exp> ::= <exp> || <exp>\n");
    }
    /*---------------------------Regla 79-----------------------------------------*/
    | TOK_NOT exp {
        if($2.tipo != BOOLEAN) {
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Non compatible types\n", l, pos);
            finish();
            return -1;
        }
        $$.tipo=BOOLEAN;
        $$.es_direccion=0;
        no(yyout, $2.es_direccion, num_no);
        num_no++;
        fprintf(yyout, ";R79:\t<exp> ::= ! <exp>\n");
    }
    /*---------------------------Regla 80-----------------------------------------*/
    | TOK_IDENTIFICADOR {
        Simbol *aux = NULL; 
        strcpy($$.lexema, $1.lexema);
        
        aux = searchSimbolInTables(LocalTable, GlobalTable, $1.lexema);
        if (aux == NULL)
        {
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Variable %s not in the table.\n", l, pos,  $1.lexema);
            finish();
            return -1;
        }
        if (aux->categoria==FUNCION || aux->clase==VECTOR)
        {
            fprintf(stderr,"****Error Semantico en la linea %d: Variable %s de clase incorrecta.\n", l, $1.lexema);
            finish();
            return -1;
        }

        $$.tipo = aux->tipo;
        $$.es_direccion = 1; /* ES UNA VARIABLE */
        
        if(LocalTable != NULL){
            if(aux->categoria == VARIABLE){
                escribirVariableLocal(yyout, aux->localVarPos);
            } else if(aux->categoria == PARAMETRO){
                escribirParametro(yyout, aux->paramPos, param_act_num);
            }
        } else {
            escribir_operando(yyout, $1.lexema, $$.es_direccion);
            if(en_explist){
                operandoEnPilaAArgumento(yyout, $$.es_direccion);
            }
        }
        
        fprintf(yyout, ";R80:\t<exp> ::= <identificador>\n");
        
    }    
    /*---------------------------Regla 81-----------------------------------------*/
    | constante {
        char aux[100];
        snprintf(aux,sizeof(aux),"%d",$1.valor_entero);
        escribir_operando(yyout, aux, $1.es_direccion);
        $$.tipo = $1.tipo;
        $$.es_direccion = $1.es_direccion;
        $$.valor_entero = $1.valor_entero;
        fprintf(yyout, ";R81:\t<exp> ::= <constante>\n");
    }
    /*---------------------------Regla 82-----------------------------------------*/
    | TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO {
        $$.tipo = $2.tipo;
        $$.es_direccion = $2.es_direccion;
        fprintf(yyout, ";R82:\t<exp> ::= ( <exp> )\n");
    }
    /*---------------------------Regla 83-----------------------------------------*/
    | TOK_PARENTESISIZQUIERDO comparacion TOK_PARENTESISDERECHO {
        $$.tipo = $2.tipo;
        $$.es_direccion = $2.es_direccion;
        fprintf(yyout, ";R83:\t<exp> ::= ( <comparacion> )\n");
    }
    /*---------------------------Regla 85-----------------------------------------*/
    | elemento_vector {
        $$.tipo = $1.tipo;
        $$.es_direccion = $1.es_direccion;
        fprintf(yyout, ";R85:\t<exp> ::= <elemento_vector>\n");
    }
    /*---------------------------Regla 88-----------------------------------------*/
    | TOK_IDENTIFICADOR en_explist_act TOK_PARENTESISIZQUIERDO lista_expresiones TOK_PARENTESISDERECHO {

        if((aux = isLocal($1.lexema))==NULL){
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Acceso a funcion no declarada (%s).\n", l, pos, $1.lexema);
            finish();
            return -1;
        }

        if(aux->categoria != FUNCION){
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, variable %s no es de categoria funcion.\n", l, pos, $1.lexema);
            return -1;
        }

        if (aux->param != num_parametros_llamada_actual){
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, numero incorrecto de parametros en llamada a funcion.\n", l, pos);
            return -1;
        }

        llamarFuncion(yyout, s->lexema, s->param);
        en_explist=0;
        $$.tipo = aux->tipo;
        $$.es_direccion = 0;
        fprintf(yyout, ";R88:\t<exp> ::= <identificador> ( <lista_expresiones> )\n");
    };

en_explist_act: {
    en_explist = 1;
}

/*---------------------------Regla 89-----------------------------------------*/
lista_expresiones: exp resto_lista_expresiones {
        num_parametros_llamada_actual++;
        fprintf(yyout, ";R89:\t<lista_expresiones ::= <exp> <resto_lista_expresiones>\n");
    }
    /*---------------------------Regla 90-----------------------------------------*/
    | {
        fprintf(yyout, ";R90:\t<lista_expresiones> ::=\n");
        num_parametros_llamada_actual = 0;
    };

/*---------------------------Regla 91-----------------------------------------*/
resto_lista_expresiones: TOK_COMA exp resto_lista_expresiones {
        num_parametros_llamada_actual++;
        fprintf(yyout, ";R91:\t<resto_lista_expresiones ::= , <exp> <resto_lista_expresiones>\n");
    }
    /*---------------------------Regla 92-----------------------------------------*/
    | {
        fprintf(yyout, ";R92:\t<resto_lista_expresiones> ::=\n");
        num_parametros_llamada_actual = 0;
    }

/*---------------------------Regla 93-----------------------------------------*/
comparacion: exp TOK_IGUAL exp {
        if($1.tipo == BOOLEAN || $3.tipo == BOOLEAN){
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Comparacion con operandos boolean.\n", l, pos);
            finish();
            return -1;
        }
        $$.tipo = BOOLEAN;
        $$.es_direccion = 0;

        igual(yyout, $1.es_direccion, $3.es_direccion, num_comp++);
        fprintf(yyout,";R93:\t<comparacion> ::= <exp> == <exp>\n");
    }
    /*---------------------------Regla 94-----------------------------------------*/
    | exp TOK_DISTINTO exp {
        if($1.tipo != INT || $3.tipo != INT){
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Comparacion con operandos boolean.\n", l, pos);
            finish();
            return -1;
        }
        $$.tipo = BOOLEAN;
        $$.es_direccion = 0;

        distinto(yyout, $1.es_direccion, $3.es_direccion, num_comp++);
        fprintf(yyout,";R94:\t<comparacion> ::= <exp> != <exp>\n");
    }
    /*---------------------------Regla 95-----------------------------------------*/
    | exp TOK_MENORIGUAL exp {
        if($1.tipo != INT || $3.tipo != INT){
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Comparacion con operandos boolean.\n", l, pos);
            finish();
            return -1;
        }
        $$.tipo = BOOLEAN;
        $$.es_direccion = 0;

        menor_igual(yyout, $1.es_direccion, $3.es_direccion, num_comp++);
        fprintf(yyout,";R95:\t<comparacion> ::= <exp> <= <exp>\n");
    }
    /*---------------------------Regla 96-----------------------------------------*/
    | exp TOK_MAYORIGUAL exp {
        if($1.tipo != INT || $3.tipo != INT){
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Comparacion con operandos boolean.\n", l, pos);
            finish();
            return -1;
        }
        $$.tipo = BOOLEAN;
        $$.es_direccion = 0;

        mayor_igual(yyout, $1.es_direccion, $3.es_direccion, num_comp++);
        fprintf(yyout,";R96:\t<comparacion> ::= <exp> >= <exp>\n");
    }
    /*---------------------------Regla 97-----------------------------------------*/
    | exp TOK_MENOR exp {
        if($1.tipo != INT || $3.tipo != INT){
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Comparacion con operandos boolean.\n", l, pos);
            finish();
            return -1;
        }
        $$.tipo = BOOLEAN;
        $$.es_direccion = 0;

        menor(yyout, $1.es_direccion, $3.es_direccion, num_comp++);
        fprintf(yyout,";R97:\t<comparacion> ::= <exp> < <exp>\n");
    }
    /*---------------------------Regla 98-----------------------------------------*/
    | exp TOK_MAYOR exp {
        if($1.tipo != INT || $3.tipo != INT){
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Comparacion con operandos boolean.\n", l, pos);
            finish();
            return -1;
        }
        $$.tipo = BOOLEAN;
        $$.es_direccion = 0;

        mayor(yyout, $1.es_direccion, $3.es_direccion, num_comp++);
        fprintf(yyout,";R98:\t<comparacion> ::= <exp> > <exp>\n");
    };

/*---------------------------Regla 99-----------------------------------------*/
constante: constante_logica {
    fprintf(yyout,";R99:\t<constante> ::= <constante_logica>\n");
        $$.tipo = $1.tipo;
        $$.es_direccion = $1.es_direccion;
        $$.valor_entero = $1.valor_entero;
        
    }
    /*---------------------------Regla 100-----------------------------------------*/
    | constante_entera {
        $$.tipo = $1.tipo;
        $$.es_direccion = $1.es_direccion;
        $$.valor_entero = $1.valor_entero;

        fprintf(yyout,";R100:\t<constante> ::= <constante_entera>\n");
        
    };

/*---------------------------Regla 102-----------------------------------------*/
constante_logica: TOK_TRUE {
        $$.tipo = BOOLEAN;
        $$.es_direccion = 0;
        $$.valor_entero = 1;

        fprintf(yyout,";R102:\t<constante_logica> ::= true\n");
    }
    /*---------------------------Regla 103-----------------------------------------*/
    | TOK_FALSE {
        $$.tipo = BOOLEAN;
        $$.es_direccion = 0;
        $$.valor_entero = 0;

        fprintf(yyout,";R103:\t<constante_logica> ::= false\n");
    };

/*---------------------------Regla 104-----------------------------------------*/
constante_entera: TOK_CONSTANTE_ENTERA {
    char aux[15];
    
    $$.tipo = INT;
    $$.es_direccion = 0;
    $$.valor_entero = $1.valor_entero;

    /* escribe código con tu librería para meter en la pila la constante
    push dword $1.valor_entero
    */
    
    fprintf(yyout, ";R104:\t<constante_entera> ::= TOK_CONSTANTE_ENTERA\n");
};
/*---------------------------Regla 108-----------------------------------------*/
identificador: TOK_IDENTIFICADOR {
    Simbol *s=NULL;
    s = searchSimbolInTables(LocalTable, GlobalTable, $1.lexema);
    if (s==NULL) {
        if (clase_actual == ESCALAR) {
            if (LocalTable == NULL) {
                declarar_variable(yyout, $1.lexema, tipo_actual, 1);
            }
            s = simboloinit($1.lexema, VARIABLE, clase_actual, tipo_actual, 0, 0, pos_local_var_act, 0, 0);
        } else {
            if (LocalTable == NULL) {
                declarar_variable(yyout, $1.lexema, tipo_actual, vector_size_act);
            }
            else {
                fprintf(stderr,"****Error semantico en [lin %d, col %d]:: Variable local de tipo no escalar.\n", l, pos);
                finish();
                return -1;
            }
            s = simboloinit($1.lexema, VARIABLE, clase_actual, tipo_actual, vector_size_act, 0, 0, 0, 0);
        }
        /* Creo el simbol */
        if (LocalTable!=NULL){
            loc_var_num++;
            pos_local_var_act++;
        }
        add_node2HashTable(CurrentTable, $1.lexema, sizeof($1.lexema), s);
        fprintf(yyout, ";R108:\t<identificador> ::= TOK_IDENTIFICADOR\n");
    } else {
        fprintf(stderr,"****Error semántico en [lin %d, col %d]: Declaracion duplicada.\n", l, pos);
        finish();
        return -1;
    }
};


%%

void yyerror (const char* err){
    if(err != NULL){
        fprintf(stdout,"****Error sintactico en [lin %d, col %d]\n", l, pos);
    }
    finish();
}

