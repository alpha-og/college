/*
  Experiment 23
  Garbage collector
  25 Athul Anoop
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_POOL_SIZE 1024 // size of memory pool

typedef struct Block {
  size_t size;        // size of the block
  int free;           // allocation status (1 for free, 0 for allocated)
  struct Block *next; // pointer to the next block
  struct Block *prev; // pointer to the previous block
} Block;

static char memory_pool[MEMORY_POOL_SIZE]; // memory pool
static Block *free_list = NULL;            // head of the free list

// function declarations

void init_memory_pool();
void *custom_malloc(size_t size);
void custom_free(void *ptr);
void collect_garbage();

int main() {
  init_memory_pool(); // initialize memory pool

  // simulate memory allocations
  void *ptr1 = custom_malloc(100);
  void *ptr2 = custom_malloc(200);
  void *ptr3 = custom_malloc(50);

  printf("Allocated blocks:\n");
  printf("Block 1: %p\n", ptr1);
  printf("Block 2: %p\n", ptr2);
  printf("Block 3: %p\n", ptr3);

  // free some blocks
  custom_free(ptr1);
  custom_free(ptr2);

  printf("After freeing:\n");
  collect_garbage(); // show free blocks

  return 0;
}

// function definitions

// function to initialize the memory pool
void init_memory_pool() {
  free_list = (Block *)memory_pool; // set the head of free list
  free_list->size = MEMORY_POOL_SIZE - sizeof(Block); // set block size
  free_list->free = 1;                                // mark as free
  free_list->next = NULL;                             // no next block
  free_list->prev = NULL;                             // no previous block
}

// function to allocate memory
void *custom_malloc(size_t size) {
  Block *current = free_list;

  while (current) {
    if (current->free && current->size >= size) {
      if (current->size > size + sizeof(Block)) {
        Block *new_block = (Block *)((char *)current + sizeof(Block) + size);
        new_block->size = current->size - size - sizeof(Block);
        new_block->free = 1;
        new_block->next = current->next;
        new_block->prev = current;

        if (current->next) {
          current->next->prev = new_block;
        }

        current->next = new_block;
        current->size = size;
      }

      current->free = 0;
      return (char *)current + sizeof(Block);
    }
    current = current->next;
  }

  return NULL;
}

// function to free allocated memory
void custom_free(void *ptr) {
  if (!ptr)
    return; // return if pointer is NULL

  Block *block = (Block *)((char *)ptr - sizeof(Block));
  block->free = 1;

  // coalesce adjacent free blocks
  if (block->next && block->next->free) {
    block->size += sizeof(Block) + block->next->size;
    block->next = block->next->next;
    if (block->next) {
      block->next->prev = block;
    }
  }

  if (block->prev && block->prev->free) {
    block->prev->size += sizeof(Block) + block->size;
    block->prev->next = block->next;
    if (block->next) {
      block->next->prev = block->prev;
    }
    block = block->prev;
  }
}

void collect_garbage() {
  Block *current = free_list;

  while (current) {
    if (current->free) {
      printf("free block size: %zu\n", current->size);
    }
    current = current->next;
  }
}
