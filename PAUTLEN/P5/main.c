#include <stdlib.h>
#include <stdio.h>


extern int yyparse();
extern FILE *yyin, *yyout;


int main(int argc, char **argv) {

  if (argc != 3) {
    fprintf(stderr, "Incorrect arguments");
    return -1;
  }

  yyin = fopen(argv[1], "r");
  if (yyin == NULL) {
    fprintf(stderr, "error");
    return -1;
  }

  yyout = fopen(argv[2], "w");
  if (yyout == NULL) {
    fprintf(stderr, "error");
    return -1;
  }

  yyparse();

  fclose(yyin);
  fclose(yyout);

  return 0;
  }
