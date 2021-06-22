#include "read.h"
#include "eval.h"
#include "stakan.h"
#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool prompt = true;

char peek(FILE *i) {
  char c = getc(i);
  ungetc(c, i);
  return c;
}

char* uppercase(char* s) {
  char* start = s;
  while (*s) {
    *s = toupper((unsigned char) *s);
    s++;
  }
  return start;
}

void skip_comment(FILE *i, bool new_style, bool multiline) {
  char c;
  while (1) {
    c = getc(i);
    if (multiline && c == MULTICOMMENT_B) {
        return;
    }
    if ((!new_style && c == MULTICOMMENT_B) || c == '\n') {
      return;
    }
  }
}

bool fetch(FILE *i, char* input) {
  char c;
  char *head = input;
  bool interactive = i == stdin;

  while (1) {
    
    c = getc(i);
    prompt = (interactive && c == '\n');

    if (isspace(c)) {
      break;
    }
    
    if (c == MULTICOMMENT_A || c == COMMENT) {
      skip_comment(
                   i,
                   c == COMMENT, // new_style
                   c != COMMENT && !interactive // multiline
                   );
      break;
    }

    if ((head - input) < TOKEN_SIZE) {
      *head = c;
      head++;
    } else
      break; // truncate if too long
  }

  if (head - input) {
    *head = '\0';
    return true;
  }
  return false;
}

bool parse(char *input, Token *token) {
  char *p;
  cell v = strtold(input, &p);
  if (*p == 0) {
    token->is_word = false;
    token->value = v;
  } else {
    // string was not consumed completely so it is not a number
    token->is_word = true;
    token->word = strdup(uppercase(input));
  }
  return true;
}

bool read(FILE *i, Token *token) {
  char buf[TOKEN_SIZE];
  if (prompt) msg("> ");
  return fetch(i, buf) && parse(buf, token);
}
