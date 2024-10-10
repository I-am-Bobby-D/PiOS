#include "page.h"
#include "list.h"
#include <stddef.h>
struct ppage physical_page_array[128];
struct ppage *allocd_list = NULL;
struct ppage *free_list = NULL;

//sets pointers to addr, next, prev for each page struct
void init_pfa_list(void) {
    extern struct ppage physical_page_array[];
        for (int i = 0; i < 128; i++) {
        //address calculation
        physical_page_array[i].physical_addr = (void*)(i * 2 * 1024 * 1024);
        physical_page_array[i].next = (i == 127) ? NULL : &physical_page_array[i+1];
        physical_page_array[i].prev = (i == 0) ? NULL : &physical_page_array[i-1];
    }
    //all pages start free
    free_list = &physical_page_array[0];
}

//unlink n pages from free list, returns pointer to struct ppage
struct ppage *allocate_physical_pages(unsigned int npages) {
    extern struct free_list;
    extern struct allocd_list;

    //head and current pointers
    struct ppage *head_free = free_list;
    struct ppage *current_free = free_list;

    //check if enough pages
    for(unsigned int i = 0; i < npages; i++){
        if(current_free == NULL){
            return NULL;
        }
        current_free = current_free->next;

        //free_list[i].next = (i == npages) ? NULL : &physical_page_array[i + 1];
        //free_list[i].prev = (i == 0) ? NULL : &physical_page_array[i - 1];
    }

    struct ppage *current_allocd = allocd_list;
    current_free = free_list;

    for(unsigned int i = 0; i < npages; i++) {
        //ptr to next page in free list
        struct ppage *next_pg_FL = free_list->next;

        if (next_pg_FL){
        //if free_list.next is valid, .prev ptr of next element set to NULL
            next_pg_FL->prev = NULL;
        }
        //free page.next now points to allocd_list
        free_list->next = allocd_list;
        if(allocd_list) {
            //free page (now in allocd_list).prev now points to previous element from free list
            allocd_list->prev = free_list;
        }
    }
    //return &free_pages[0];
    return allocd_list;

}

void free_physical_pages(struct ppage *ppage_list){
    struct ppage *current = ppage_list;
        while(current){

            current->next = free_list;

            if(free_list){
                free_list->prev = current;
            }
            current->prev = NULL;
            free_list = current;

            current = current->next;

        }
}

