#pragma once
#include "read.h"
#include "stack.h"
#include "eval.h"
#include "stakan.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define DEF_SIZE 128

#define POP(x) cell x; spop(s, &x);
#define PUSH(x) spush(s, x);
#define PEEK(x) cell x; speek(s, &x);

#define NWORD(name) nword name(Stack *s)
#define NWORD_OPERATOR(name, op) NWORD(name) { POP(a); POP(b); PUSH(a op b); }

NWORD_OPERATOR(add, +)
NWORD_OPERATOR(sub, -)
NWORD_OPERATOR(mul, *)
NWORD_OPERATOR(dvd, /)
NWORD_OPERATOR(eq, =)
NWORD_OPERATOR(gt, >)
NWORD_OPERATOR(lt, <)
NWORD_OPERATOR(geq, >=)
NWORD_OPERATOR(leq, <=)

NWORD(dots) {
  sprint(s); msg("ok\n");
}

NWORD(dot) {
  cell a;
  if (spop(s, &a)) {
    char* r;
    asprintf(&r, "\n%Lg ok.\n", a);
    msg(r);
    free(r);
  }
}

NWORD(neg) {
  POP(a);
  PUSH(-a);
}

NWORD(dup) {
  PEEK(a);
  PUSH(a);
}

NWORD(swap) {
  POP(a); POP(b);
  PUSH(b); PUSH(a);
}

NWORD(cei) {
  POP(a);
  PUSH(ceil(a));
}

NWORD(flo) {
  POP(a);
  PUSH(floor(a));
}

NWORD(not) {
  POP(a);
  PUSH(!a);
}

NWORD(over) {
  POP(a); POP(b);
  PUSH(b); PUSH(a); PUSH(b);
}

NWORD(def) {
  ENTRY e;
  Token *token = (Token *)malloc(sizeof(Token));
  size_t len = 0;
  read(stdin, token);
  
  if (!token->is_word) msg("? not a name\n");
  e.key = strdup(token->word);
  e.data = malloc(sizeof(Word));

  Word *word = e.data;
  word->body = malloc(sizeof(Token*) * DEF_SIZE);
  char word_start = '\0';

  while (1) {
    token = (Token *)malloc(sizeof(Token));
    read(stdin, token);
    if (token->is_word && token->word[0] == ';') break;
    word->body[len] = token;
    len++;
  }

  word->body_len = len;
  hsearch(e, ENTER);
}

void add_nword(char* name, nword_ptr fn) {
  ENTRY e;
  e.key = name;
  e.data = malloc(sizeof(Word));
  ((Word *)e.data)->fn = fn;
  hsearch(e, ENTER);
}

void init_nwords() {
    add_nword("+", add);
    add_nword("-", sub);
    add_nword("*", mul);
    add_nword("/", dvd);
    add_nword("=", eq);
    add_nword(">", gt);
    add_nword("<", lt);
    add_nword(">=", geq);
    add_nword("<=", leq);

    add_nword(".S", dots);
    add_nword(".", dot);
    add_nword("!", not);
    add_nword("SWAP", swap);
    add_nword("DUP", dup);
    add_nword("OVER", over);
    add_nword("CEIL", cei);
    add_nword("FLOOR", flo);

    add_nword(":", def);
}
