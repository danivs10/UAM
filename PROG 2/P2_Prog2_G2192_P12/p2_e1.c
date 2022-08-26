/**
 * @file  p2_e1.c
 * @author Santiago Atrio, Daniel Varela
 * @date 2 Marzo 2020
 * @version 1.0
 * @brief Main ex1
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "stack_fp.h"
#include "types.h"

#define MAX_STRING 500

extern int errno;

/**
* @brief: Reverse the words of an input string to an output string.
* The words in the input string are separated by a space character.
* The strings may not overlap, and the destination string strout
* must be large enough to receive the inverted expression.
*
* @param strout, Pointer to the output buffer
* @param strin, Pointer to the input expression
* @return The function returns OK or ERROR
**/
Status reverseWords(char *strout, const char *strin);

/**** MAIN FUNCTION ****/
int main(int argc, char *argv[]) {
  char strin[MAX_STRING], strout[MAX_STRING];
  fprintf(stdout, "Input   : ");
  fscanf(stdin, "%[^\n]s", strin);
  reverseWords(strout, strin);
  fprintf(stdout, "Output  : %s\n", strout);
  return OK;
}

Status reverseWords(char *strout, const char *strin) {
  Stack *stackChars;
  int i = 0, j = 0, k = 0;
  char *c=NULL;
  stackChars = stack_init(char_free, char_copy, char_print);
  for (i = 0; i <= strlen(strin); i++) {
    if (strin[i] == ' ' || strin[i] == '\0') {
      for (j = 0; !(stack_isEmpty(stackChars)); j++) {
        c = stack_pop(stackChars);
        strout[k]=(*c);
        k++;
        char_free(c);
      }
      strout[k]= ' ';
      k++;
    } else {
      stack_push(stackChars, strin + i);
    }
  }
  stack_free(stackChars);
  strout[i]='\0';
  return OK;
}