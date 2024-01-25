#ifndef ARENA_H
#define ARENA_H
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct ArenaBlock ArenaBlock;

struct ArenaBlock {
  ArenaBlock *next;
  size_t length;
  size_t capacity;
  uintptr_t blocks[];
};

typedef struct {
  ArenaBlock *head, *tail;
} Arena;

#define ARENA_BLOCK_DEFAULT_CAPACITY 1024

void *arena_alloc(Arena *arena, size_t size);
void arena_free(Arena *arena);

#endif  // !ARENA_H
