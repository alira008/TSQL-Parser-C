#include "common.h"

String string_from_cstrn(const char *cstr, size_t length) {
  String s = {0};
  s.data = (char *)malloc(length);
  s.length = length;
  s.capacity = length;

  // copy string
  if (memcpy(s.data, cstr, length) == NULL) {
    printf("Was not able to copy string\n");
    free(s.data);
    s.data = NULL;
    s.length = 0;
    s.capacity = 0;
    return s;
  }

  // // set null terminator
  // s.data[length] = '\0';
  return s;
}

String string_from_sv(StringView sv) {
  return string_from_cstrn(sv.data, sv.length);
}
String string_from_cstr(const char *cstr) {
  return string_from_cstrn(cstr, strlen(cstr));
}
