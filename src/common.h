#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DA_INIT_CAPACITY 8
#define DA_APPEND(da, value)                                 \
  do {                                                       \
    if ((da)->length >= (da)->capacity) {                    \
      if ((da)->capacity == 0) {                             \
        (da)->capacity = DA_INIT_CAPACITY;                   \
      }                                                      \
      (da)->data = (typeof((da)->data))realloc(              \
          (da)->data, (da)->capacity * sizeof(*(da)->data)); \
    }                                                        \
    if ((da)->data != NULL) {                                \
      (da)->data[(da)->length++] = (value);                  \
    }                                                        \
  } while (0)

#define DA_APPEND_MULTI(da, value, amount)                   \
  do {                                                       \
    if ((da)->length + amount > (da)->capacity) {            \
      if ((da)->capacity == 0) {                             \
        (da)->capacity = DA_INIT_CAPACITY;                   \
      }                                                      \
      while ((da)->length + amount > (da)->capacity) {       \
        (da)->capacity = (da)->capacity * 2;                 \
      }                                                      \
      (da)->data = (typeof((da)->data))realloc(              \
          (da)->data, (da)->capacity * sizeof(*(da)->data)); \
    }                                                        \
    if ((da)->data != NULL) {                                \
      memcpy((da)->data + (da)->length, (value),             \
             amount * sizeof(*(da)->data));                  \
      (da)->length += amount;                                \
    }                                                        \
  } while (0)

#ifndef SV_FMT
#define SV_FMT "%.*s"
#endif

#ifndef SV_ARG
#define SV_ARG(sv) (int)(sv).length, (sv).data
#endif

typedef struct {
  const char *data;
  size_t length;
} StringView;

typedef struct {
  char *data;
  size_t length;
  size_t capacity;
} String;

String string_from_cstrn(const char *cstr, size_t length);
String string_from_sv(StringView sv);
String string_from_cstr(const char *cstr);

#define STRING_INIT_CAPACITY 8
#define STRING_APPEND(str, value)                                     \
  do {                                                                \
    if ((str)->length >= (str)->capacity) {                           \
      if ((str)->capacity == 0) {                                     \
        (str)->capacity = STRING_INIT_CAPACITY;                       \
      }                                                               \
      (str)->capacity = (str)->capacity * 2;                          \
      (str)->data = (typeof((str)->data))realloc(                     \
          (str)->data, ((str)->capacity + 1) * sizeof(*(str)->data)); \
    }                                                                 \
    if ((str)->data != NULL) {                                        \
      (str)->data[(str)->length++] = (value);                         \
      (str)->data[(str)->length] = '\0';                              \
    }                                                                 \
  } while (0)

#define STRING_APPEND_MULTI(str, value, amount)                       \
  do {                                                                \
    if ((str)->length + amount > (str)->capacity) {                   \
      if ((str)->capacity == 0) {                                     \
        (str)->capacity = STRING_INIT_CAPACITY;                       \
      }                                                               \
      while ((str)->length + amount > (str)->capacity) {              \
        (str)->capacity = (str)->capacity * 2;                        \
      }                                                               \
      (str)->data = (typeof((str)->data))realloc(                     \
          (str)->data, ((str)->capacity + 1) * sizeof(*(str)->data)); \
    }                                                                 \
    if ((str)->data != NULL) {                                        \
      memcpy((str)->data + (str)->length, (value),                    \
             amount * sizeof(*(str)->data));                          \
      (str)->length += amount;                                        \
      (str)->data[(str)->length] = '\0';                              \
    }                                                                 \
  } while (0)

#define STRING_APPEND_SV(s, sv)                 \
  do {                                          \
    STRING_APPEND_MULTI((s), sv->data, sv->length); \
  } while (0)

#define STRING_APPEND_CSTRN(s, cstr, length) \
  do {                                       \
    const char *cstr_ = (cstr);              \
    STRING_APPEND_MULTI((s), cstr_, length);     \
  } while (0)

#define STRING_APPEND_CSTR(s, cstr)       \
  do {                                    \
    const char *cstr_ = (cstr);           \
    size_t length_ = strlen(cstr_);       \
    STRING_APPEND_MULTI((s), cstr_, length_); \
  } while (0)

#endif  // !COMMON_H
