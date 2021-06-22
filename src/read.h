#pragma once
#include "stack.h"
#include "eval.h"
#include <stdio.h>
#include <stdbool.h>

#define MULTICOMMENT_A '('
#define MULTICOMMENT_B ')'
#define COMMENT '\\'

#define TOKEN_SIZE 255

char peek(FILE *i);
bool read(FILE *i, Token *token);
