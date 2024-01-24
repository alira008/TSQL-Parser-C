#include <stdio.h>

#include "token.h"
#include "lexer.h"

int main(void) {
  Lexer* lexer = lexer_new("=hello world");
  Location location = lexer_location(lexer);

  Token token = lexer_next_token(lexer);
  while (token.type != TOKEN_EOF) {
    if (token.type == TOKEN_IDENTIFIER) {
      printf("Identifier: %s\n", token.value.identifier.literal);
    } else if (token.type == TOKEN_NUMBER) {
      printf("%s\n", token.value.number);
    }
    token = lexer_next_token(lexer);
  }

  printf("col: %d, line: %d\n", location.column, location.line);

  free(lexer);

  return 0;
}
