#ifndef LEXER_H
#define LEXER_H
#include <stdlib.h>

#include "token.h"

typedef struct Lexer Lexer;

Lexer* lexer_new(const char *input);
Location lexer_location(Lexer *lexer);
Token lexer_next_token(Lexer *lexer);

#endif  // !LEXER
