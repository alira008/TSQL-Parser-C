#include <stdio.h>

#include "arena.h"
#include "common.h"
#include "lexer.h"
#include "token.h"

int main(void) {
  Arena arena = {0};
  Lexer lexer = lexer_new(&arena, "=hello world how are you today. lmao");
  Location location = lexer_location(&lexer);

  Token token = lexer_next_token(&lexer);
  while (token.type != TOKEN_EOF) {
    if (token.type == TOKEN_IDENTIFIER) {
      printf("Identifier: " SV_FMT "\n", SV_ARG(token.value.identifier));
    } else if (token.type == TOKEN_NUMBER) {
      printf("%lf\n", token.value.number);
    }
    token = lexer_next_token(&lexer);
  }

  String str = string_from_cstr("hello my boys");
  printf("str: %s\n", str.data);
  STRING_APPEND_CSTR(&str, "lmao");
  printf("str: %s\n", str.data);
  STRING_APPEND_CSTR(&str, " how are you doing today?");
  printf("str: %s\n", str.data);
  free(str.data);

  printf("col: %ld, line: %ld\n", location.column, location.line);

  arena_free(&arena);

  return 0;
}
