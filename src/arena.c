#include "arena.h"

ArenaBlock *arena_block_new(size_t capacity) {
  // allocate memory for the block and the array of pointers
  ArenaBlock *block =
      (ArenaBlock *)malloc(sizeof(ArenaBlock) + sizeof(uintptr_t) * capacity);

  // handle allocation failure
  if (block == NULL) return NULL;

  block->next = NULL;
  block->length = 0;
  block->capacity = capacity;
  return block;
}

void arena_block_free(ArenaBlock *block) {
  if (block == NULL) return;
  free(block);
}

void *arena_alloc(Arena *arena, size_t size) {
  // make sure the new allocation is properly aligned
  size_t size_to_allocate = (size + sizeof(uintptr_t) - 1) / sizeof(uintptr_t);

  // check if head is null
  if (arena->tail == NULL) {
    size_t capacity = ARENA_BLOCK_DEFAULT_CAPACITY;
    if (ARENA_BLOCK_DEFAULT_CAPACITY < size_to_allocate)
      capacity = size_to_allocate;
    arena->tail = arena_block_new(capacity);
    arena->head = arena->tail;
  }

  while (arena->tail->length + size_to_allocate > arena->tail->capacity &&
         arena->tail->next != NULL) {
    arena->tail = arena->tail->next;
  }

  if (arena->tail->length + size_to_allocate > arena->tail->capacity) {
    size_t capacity = ARENA_BLOCK_DEFAULT_CAPACITY;
    if (ARENA_BLOCK_DEFAULT_CAPACITY < size_to_allocate)
      capacity = size_to_allocate;
    arena->tail->next = arena_block_new(capacity);
    arena->tail = arena->tail->next;
  }

  // allocate memory from the current block
  void *ptr = &arena->tail->blocks[arena->tail->length];
  arena->tail->length += size;
  return ptr;
}

void arena_free(Arena *arena) {
  ArenaBlock *arena_block = arena->head;
  while (arena_block) {
    ArenaBlock *temp_arena_block = arena_block;
    arena_block = arena_block->next;
    arena_block_free(temp_arena_block);
  }
  arena->head = NULL;
  arena->tail = NULL;
}
