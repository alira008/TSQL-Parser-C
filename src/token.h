#ifndef TOKEN_H
#define TOKEN_H
#include <stdlib.h>
#include "common.h"

enum TokenType {
  TOKEN_IDENTIFIER,
  TOKEN_INTEGER,
  TOKEN_NUMBER,
  TOKEN_QUOTED_LITERAL,

  TOKEN_ILLEGAL,
  TOKEN_EOF,
  TOKEN_KEYWORD,

  TOKEN_LEFT_BRACKET,
  TOKEN_RIGHT_BRACKET,
  TOKEN_LEFT_PAREN,
  TOKEN_RIGHT_PAREN,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_COMMA,
  TOKEN_LESS_THAN,
  TOKEN_GREATER_THAN,
  TOKEN_LESS_THAN_EQUAL,
  TOKEN_GREATER_THAN_EQUAL,
  TOKEN_EQUAL,
  TOKEN_NOT_EQUAL,
  TOKEN_ASTERISK,

  // Keywords
  TOKEN_SELECT,
  TOKEN_FROM,
};

typedef struct {
  const char *literal;
  char quote_char;
} QuotedLiteral;

typedef struct {
  const char *literal;
  size_t length;
} Identifier;

typedef struct {
  union {
    QuotedLiteral quoted_literal;
    StringView identifier;
    double number;
    int integer;
  } value;
  enum TokenType type;
} Token;

typedef struct {
  size_t line;
  size_t column;
} Location;

typedef struct {
  Location location;
  Token token;
} TokenWithLocation;

#endif  // !TOKEN_H
