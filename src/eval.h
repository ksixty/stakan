#pragma once
#include "stack.h"
#include <search.h>
#include <stdlib.h>

#define MAX_WORDS 1024

typedef void nword; // native word
typedef nword (*nword_ptr)(Stack *s);

typedef struct {
  bool is_word;
  union {
    char* word;
    cell value;
  };
} Token;

typedef struct {
  int body_len;
  union {
    nword_ptr fn;
    Token **body;
  };
} Word;

bool eval(Token* token, Stack *s);
void eval_body(Token **body, int body_len, Stack *s);
void add_nword(char* name, nword_ptr fn);
