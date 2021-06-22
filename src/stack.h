#pragma once
#include <stdbool.h>
#define STACK_SIZE 2048

typedef long double cell;

typedef struct {
  cell* base;
  int head;
} Stack;

void sinit(Stack *s);

bool spop(Stack *s, cell *v);
bool speek(Stack *s, cell *v);
bool spush(Stack *s, cell v);
bool sempty(Stack *s);
bool sfull(Stack *s);

void sprint(Stack *s);
