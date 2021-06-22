#include "stack.h"
#include "stakan.h"
#include "read.h"
#include "eval.h"
#include "nwords.h"
#include <search.h>
#include <stdio.h>
#include <stdlib.h>

void msg(char *s) {
  while(*s) putc(*s++, stdout);
}

int main(int argc, char* argv[])
{
  Stack s;
  sinit(&s);
  hcreate(MAX_WORDS);
  
  init_nwords();

  msg("Welcome to STAKAN Forth Interpreter 0.8.\n");

  while (1) {
    Token token;
    if (read(stdin, &token)) {
      eval(&token, &s);
    }
  }

  return 0;
}
