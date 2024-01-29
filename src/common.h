#ifndef COMMON_H
#define COMMON_H
#include <stdlib.h>

typedef struct {
  const char *data;
  size_t length;
} StringView;

#ifndef SV_FMT
#define SV_FMT "%.*s"
#endif

#ifndef SV_ARG
#define SV_ARG(sv) (int)(sv).length, (sv).data
#endif

#endif // !COMMON_H
