#ifndef LEXER_H
#define LEXER_H
#include <stdlib.h>

#include "token.h"
#include "arena.h"

typedef struct  {
  Arena* arena;
  const char* input;
  size_t input_length;
  size_t position;
  size_t read_position;
  char ch;
  size_t line;
  size_t column;
} Lexer;


Lexer lexer_new(Arena *arena, const char *input);
Location lexer_location(Lexer *lexer);
Token lexer_next_token(Lexer *lexer);

#endif  // !LEXER
