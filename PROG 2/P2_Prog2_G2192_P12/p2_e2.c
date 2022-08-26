 /**
 * @file  p2_e1.c
 * @author Santiago Atrio, Daniel Varela
 * @date 14 Marzo 2020
 * @version 1.0
 * @brief Main
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "stack_fp.h"
#include "types.h"

#define OPERATORS {'+', '-', '*', '/', '%', '^'}

#define MAX_STRING 500

/**
* @brief: Get the postfix expression of an infix expression.
* The infix and postfix strings may not overlap and
* the destination postfix string must be
* large enough to receive the infix expression
* (to be checked before calling this function).
*
* @param in Pointer to the infix expression
* @param suf Pointer to the suffix expression
* @return The function returns OK on success or ERROR
* when any of its parametrs is NULL
**/
Status infix2postfix(char *suf, const char *in);

Bool isOperator(char c);

int prec(char c);

int main() {
  char suf[MAX_STRING], in[MAX_STRING];
  fprintf(stdout, "Input : ");
  fscanf(stdin, "%s", in);
  if (infix2postfix(suf, in) == ERROR) {
    fprintf(stdout, "There was an error when changeing from Infix to Postfix!");
    return 1;
  }
  printf("Output : %s\n", suf);
  return 0;
}

Status infix2postfix(char *suf, const char *in) {
  Stack *s;
  Status check=OK;
  int i=0, j=0;
  char *ele, *ch;

  s = stack_init(char_free, char_copy, char_print);
  if (s == NULL) return ERROR;

  while (i < strlen(in) && check == OK) {
    /*If operator*/
    if (isOperator(in[i]) == TRUE) {
      ele = (char *)stack_top(s);
      while ((stack_isEmpty(s) == FALSE) && ((prec(*ele)) >= (prec(in[i])))) {
        ch = (char *)stack_pop(s);
        suf[j] = *ch;
        j++;
        ele = (char *)stack_top(s);
        char_free(ch);
      }
      check=stack_push(s, in+i);
      i++;
    /*If ( */
    } else if (in[i] == '(') {
        check=stack_push(s, in+i);
        i++;
    /*If ) */
    } else if (in[i] == ')') {
      ele = (char *)stack_top(s);
      while ((stack_isEmpty(s) == FALSE) && (*ele)!='(') {
        ch = (char *)stack_pop(s);
        suf[j] = *ch;
        j++;
        ele = (char *)stack_top(s); 
      }
      char_free(ch);
      if(ele != NULL) char_free(ele);
      stack_pop(s);
      i++;
    /*If other thing*/                      
    } else {
      suf[j] = in[i];
      j++;
      i++;
    }
  }
  if (check == OK) {
    while (stack_isEmpty(s) == FALSE) {
      ch = (char *)stack_pop(s);
      suf[j] = *ch;
      j++;
    }
      char_free(ch);
  }
  stack_free(s);
  suf[j]='\0';
  return check;
}

Bool isOperator(char c) {
  int i;
  char array[6]= OPERATORS;
  for (i=0;i<6;i++) {
    if (array[i]==c) return TRUE;
  }
  return FALSE;
}

int prec(char c) {
  if (c == '+' || c == '-') return 1;
  if (c == '(') return 0;
  return 2;
}