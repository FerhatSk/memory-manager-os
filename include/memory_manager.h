#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stddef.h> // For size_t
#include <stdint.h> // For uint8_t

// Memory Pool Size: 20480 Bytes (20 KB)
#define MEMORY_POOL_SIZE 20480

// Doubly Linked List Node Structure
// __attribute__((packed)): Prevents alignment issues in embedded systems.
// This ensures that even if we allocate odd sizes (e.g., 5 bytes), the processor won't crash.
typedef struct __attribute__((packed)) Block {
    size_t size;            // Size of the data part of the block
    int is_free;            // 1: Free, 0: Allocated
    struct Block* next;     // Pointer to the next block
    struct Block* prev;     // Pointer to the previous block
} Block;

// Function Prototypes
void mem_init();
void* mem_alloc(size_t size);
void mem_free(void* ptr);
void print_memory_map();
double get_last_allocation_time();

#endif