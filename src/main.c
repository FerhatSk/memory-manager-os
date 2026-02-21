#include <stdio.h>
#include <stdlib.h>
#include "memory_manager.h"

#define MAX_RECORDS 100

// Structure to track user allocated memory
typedef struct {
    void* ptr;
    size_t size;
    int active;
} AllocationRecord;

AllocationRecord records[MAX_RECORDS];

int find_free_slot() {
    for(int i=0; i<MAX_RECORDS; i++) if(!records[i].active) return i;
    return -1;
}

void list_active() {
    printf("\n--- Active/Freeable Blocks ---\n");
    printf("ID\tSize\t\tAddress\n");
    int count = 0;
    for(int i=0; i<MAX_RECORDS; i++) {
        if(records[i].active) {
            printf("[%d]\t%zu bytes\t%p\n", i, records[i].size, records[i].ptr);
            count++;
        }
    }
    if(!count) printf(">> No active blocks to list.\n");
    printf("-------------------------------------\n");
}

int main() {
    mem_init();
    for(int i=0; i<MAX_RECORDS; i++) records[i].active = 0;

    int choice;
    size_t size_req;
    int id_to_free;

    while (1) {
        printf("\n=== MEMORY MANAGEMENT SYSTEM ===\n");
        printf("1 - Allocate Memory\n");
        printf("2 - Free Memory\n");
        printf("3 - Show Memory Map\n");
        printf("4 - Performance Report\n");
        printf("0 - Exit\n");
        printf("Your Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); 
            continue;
        }

        switch (choice) {
            case 1:
                printf("How many bytes to allocate? ");
                scanf("%zu", &size_req);
                int slot = find_free_slot();
                if(slot == -1) {
                    printf(">> ERROR: Tracking list is full.\n");
                    break;
                }
                void* ptr = mem_alloc(size_req);
                if (ptr) {
                    records[slot].ptr = ptr;
                    records[slot].size = size_req;
                    records[slot].active = 1;
                    
                    printf(">> SUCCESS: %zu bytes allocated. Address: %p\n", size_req, ptr);
                    print_memory_map();
                } else {
                    printf(">> ERROR: Insufficient memory!\n");
                }
                break;

            case 2:
                list_active();
                int has_active = 0;
                for(int i=0; i<MAX_RECORDS; i++) if(records[i].active) has_active=1;
                if(!has_active) break;

                printf("Enter the ID of the block to free: ");
                scanf("%d", &id_to_free);
                
                if (id_to_free >= 0 && id_to_free < MAX_RECORDS && records[id_to_free].active) {
                    void* p = records[id_to_free].ptr;
                    printf("Freeing memory...\n");
                    mem_free(p);
                    records[id_to_free].active = 0;
                    
                    printf(">> SUCCESS: Memory freed. Address: %p\n", p);
                    print_memory_map();
                } else {
                    printf(">> ERROR: Invalid ID.\n");
                }
                break;

            case 3:
                print_memory_map();
                break;

            case 4:
                {
                    double t = get_last_allocation_time();
                    printf("\n--- Performance Report ---\n");
                    if(t < 0) printf("Last operation: FAILED\n");
                    else printf("Time taken for last allocation: %.4f ms\n", t);
                }
                break;

            case 0: return 0;
            default: printf("Invalid choice.\n");
        }
    }
}