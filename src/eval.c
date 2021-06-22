#include "eval.h"
#include "stack.h"
#include "stakan.h"
#include <stdio.h>
#include <search.h>
#include <errno.h>
#include <stdlib.h>

void eval(Token *token, Stack *s) {
  if (token->is_word) {
    ENTRY search, *result;
    search.key = token->word;
  
    if ((result = hsearch(search, FIND)) != NULL) {
      Word *word = result->data;
      if (word->body_len) {
        // dealing with a runtime-defined word
        eval_body(word->body, word->body_len, s);
      } else {
        // dealing with a native word. just call it
        word->fn(s);
      }
    } else {
      msg("? undefined word"); msg("\n");
    }
  } else {
    spush(s, token->value);
  }
}

void eval_body(Token **body, int body_len, Stack *s) {
  for (int ip = 0; ip < body_len; ip++) {
    eval(body[ip], s);    
  }
}
