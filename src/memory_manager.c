#include "memory_manager.h"
#include <stdio.h>
#include <string.h>
#include <time.h> 

// Static Memory Pool (Fixed region in RAM)
static uint8_t memory_pool[MEMORY_POOL_SIZE];

// Head pointer for the free list
static Block* free_list_head = NULL;

// Performance measurement
static double last_alloc_time = 0.0;

// Initialize the system
void mem_init() {
    free_list_head = (Block*)memory_pool;
    free_list_head->size = MEMORY_POOL_SIZE - sizeof(Block);
    free_list_head->is_free = 1;
    free_list_head->next = NULL;
    free_list_head->prev = NULL;
}

// Coalescing Function (Merges adjacent free blocks)
void merge_blocks() {
    Block* current = free_list_head;
    while (current != NULL && current->next != NULL) {
        if (current->is_free && current->next->is_free) {
            // Merge sizes
            current->size += sizeof(Block) + current->next->size;
            
            // Update pointers (Remove the middle block from the list)
            current->next = current->next->next;
            if (current->next) {
                current->next->prev = current;
            }
            // Do not advance 'current', the newly formed larger block 
            // might merge with the next one as well.
        } else {
            current = current->next;
        }
    }
}

// Memory Allocation (First-Fit Algorithm)
void* mem_alloc(size_t size) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    if (size == 0) {
        last_alloc_time = 0.0;
        return NULL;
    }

    Block* current = free_list_head;

    while (current != NULL) {
        // Exact size check - NO Padding
        if (current->is_free && current->size >= size) {
            
            // Splitting: If remaining space can hold at least one metadata + 1 byte data, split the block
            if (current->size >= size + sizeof(Block) + 1) {
                Block* new_block = (Block*)((uint8_t*)current + sizeof(Block) + size);
                
                new_block->size = current->size - size - sizeof(Block);
                new_block->is_free = 1;
                new_block->next = current->next;
                new_block->prev = current;

                if (current->next) {
                    current->next->prev = new_block;
                }
                current->next = new_block;

                current->size = size; 
            }
            
            current->is_free = 0; // Mark as allocated

            clock_gettime(CLOCK_MONOTONIC, &end);
            last_alloc_time = (end.tv_sec - start.tv_sec) * 1000.0 + 
                              (end.tv_nsec - start.tv_nsec) / 1000000.0;
            
            // Return the data area to the user
            return (void*)((uint8_t*)current + sizeof(Block));
        }
        current = current->next;
    }

    last_alloc_time = -1.0; // Failure
    return NULL;
}

// Memory Deallocation
void mem_free(void* ptr) {
    if (ptr == NULL) return;

    // Go back to metadata
    Block* block_to_free = (Block*)((uint8_t*)ptr - sizeof(Block));

    // Security bounds check
    if ((uint8_t*)block_to_free < memory_pool || 
        (uint8_t*)block_to_free >= memory_pool + MEMORY_POOL_SIZE) {
        printf("ERROR: Out of bounds memory access!\n");
        return;
    }

    block_to_free->is_free = 1;
    merge_blocks(); // Automatically coalesce
}

// Print Memory Map
void print_memory_map() {
    Block* current = free_list_head;
    int index = 0;
    
    printf("\n--- Memory Map ---\n");
    while (current != NULL) {
        printf("BLOCK %d: %s, Size: %zu | Address: %p\n", 
               index++, 
               current->is_free ? "FREE" : "USED", 
               current->size, 
               (void*)((uint8_t*)current + sizeof(Block)));
        current = current->next;
    }
    printf("------------------------\n");
}

double get_last_allocation_time() {
    return last_alloc_time;
}