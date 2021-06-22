#include "stack.h"
#include "stakan.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void sinit(Stack *s) {
  s->base = malloc(sizeof(cell) * STACK_SIZE);
  s->head = -1;
}

bool spop(Stack *s, cell *v) {
  if (sempty(s)) {
    msg("? stack underflow\n");
    return false;
  }

  *v = s->base[s->head];
  s->head--;
  return true;
}

bool speek(Stack *s, cell *v) {
  if (sempty(s)) {
    msg("? stack underflow\n");
    return false;
  }

  *v = s->base[s->head];
  return true;
}

bool spush(Stack *s, cell v) {
  if (sfull(s)) {
    msg("? stack overflow\n");
    return false;
  }

  s->head++;
  s->base[s->head] = v;
  return true;
}

bool sempty(Stack *s) { return s->head == -1; }

bool sfull(Stack *s) { return s->head == STACK_SIZE; }

void sprint(Stack *s) {
  for (int i = 0; i <= s->head; i++) {
    char *p;
    asprintf(&p, "%Lg ", s->base[i]);
    msg(p);
  }
}
