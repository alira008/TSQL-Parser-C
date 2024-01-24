#include "lexer.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "common.h"

struct Lexer {
  const char* input;
  size_t input_length;
  size_t position;
  size_t read_position;
  char ch;
  size_t line;
  size_t column;
};

void lexer_read_char(Lexer* lexer);

Lexer* lexer_new(const char* input) {
  Lexer* lexer = (Lexer*)malloc(sizeof(Lexer));
  memset(lexer, 0, sizeof(Lexer));
  lexer->input_length = strlen(input);
  lexer->input = input;
  lexer->line = 1;
  lexer->ch = '\0';

  lexer_read_char(lexer);
  return lexer;
}

Location lexer_location(Lexer* lexer) {
  Location location = {0};
  location.line = lexer->line;
  location.column = lexer->column;
  return location;
}

char lexer_peek_char(Lexer* lexer) {
  if (lexer->read_position >= lexer->input_length) {
    return '\0';
  }

  return lexer->input[lexer->read_position];
}

bool lexer_is_letter(char ch) { return isalpha(ch) || ch == '_'; }
bool lexer_is_number(char ch) { return isdigit(ch) || ch == '.'; }

void lexer_read_char(Lexer* lexer) {
  // check to see if we're at the end of the input
  if (lexer->read_position >= lexer->input_length) {
    lexer->ch = '\0';
  } else {
    lexer->ch = lexer->input[lexer->read_position];

    // check to see if we're at a newline
    if (lexer->ch == '\n') {
      lexer->line++;
      lexer->column = 1;
    } else {
      lexer->column++;
    }
  }

  // advance the positions
  lexer->position = lexer->read_position;
  lexer->read_position++;
}

StringView lexer_read_identifier(Lexer* lexer) {
  size_t position = lexer->position;
  while (lexer_is_letter(lexer->ch) && lexer_peek_char(lexer) != '\0') {
    lexer_read_char(lexer);
  }

  StringView string_view = {0};
  string_view.data = lexer->input + position;
  string_view.length = lexer->position - position;

  return string_view;
}

StringView lexer_read_number(Lexer* lexer) {
  size_t position = lexer->position;
  while (lexer_is_number(lexer->ch) && lexer_peek_char(lexer) != '\0') {
    lexer_read_char(lexer);
  }

  StringView string_view = {0};
  string_view.data = lexer->input + position;
  string_view.length = lexer->position - position;

  return string_view;
}

StringView lexer_read_quoted_literal(Lexer* lexer, char quote_char) {
  // skip the opening quote
  lexer_read_char(lexer);
  size_t position = lexer->position;

  while (lexer->ch != quote_char && lexer_peek_char(lexer) != quote_char &&
         lexer_peek_char(lexer) != '\0') {
    lexer_read_char(lexer);
  }

  // skip the closing quote
  lexer_read_char(lexer);

  StringView string_view = {0};
  string_view.data = lexer->input + position;
  string_view.length = lexer->position - position;

  return string_view;
}

StringView lexer_read_alias(Lexer* lexer) {
  size_t position = lexer->position;

  while (lexer->ch != ']' && lexer_peek_char(lexer) != '\0') {
    lexer_read_char(lexer);
  }

  StringView string_view = {0};
  string_view.data = lexer->input + position;
  string_view.length = lexer->position - position;

  return string_view;
}

void lexer_skip_whitespace(Lexer* lexer) {
  while (isspace(lexer->ch) && lexer_peek_char(lexer) != '\0') {
    lexer_read_char(lexer);
  }
}

Token lexer_next_token(Lexer* lexer) {
  lexer_skip_whitespace(lexer);

  Token token = {0};

  if (lexer_is_letter(lexer->ch)) {
    StringView string_view = lexer_read_identifier(lexer);

    token.type = TOKEN_IDENTIFIER;
    token.value.identifier.literal = string_view.data;
    token.value.identifier.length = string_view.length;

    lexer_read_char(lexer);
    return token;
  }
  //   else if (lexer_is_number(lexer->ch)) {
  //   StringView string_view = lexer_read_number(lexer);
  //   token.type = TOKEN_NUMBER;
  //
  //   token.value.number = atof(string_view.data);
  // }

  switch (lexer->ch) {
    case '=':
      token.type = TOKEN_EQUAL;
      break;
    case '\0':
      token.type = TOKEN_EOF;
      break;
    default:
      token.type = TOKEN_ILLEGAL;
      break;
  };

  lexer_read_char(lexer);
  return token;
}
