#include <stdio.h>

#include "arena.h"
#include "lexer.h"
#include "token.h"

int main(void) {
  Arena arena = {0};
  Lexer* lexer = lexer_new(&arena, "=hello world");
  Location location = lexer_location(lexer);

  Token token = lexer_next_token(lexer);
  while (token.type != TOKEN_EOF) {
    if (token.type == TOKEN_IDENTIFIER) {
      printf("Identifier: %s\n", token.value.identifier.literal);
    } else if (token.type == TOKEN_NUMBER) {
      printf("%lf\n", token.value.number);
    }
    token = lexer_next_token(lexer);
  }

  printf("col: %ld, line: %ld\n", location.column, location.line);

  arena_free(&arena);
  free(lexer);

  return 0;
}
