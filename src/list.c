#include <stdio.h>
#include "list.h"

long buf[256];

//head at buf[0]
struct list_element *head = NULL;

void list_add(struct list_element **list_head, struct list_element *new_element){
    if (new_element == NULL){
        return;
    }

    //pointer next @ address of new_element = *list_head
    new_element->next = *list_head;
    //add to head of list
    *list_head = new_element;
}

void list_remove(struct list_element *element){
    struct list_element **current = &head;

    while (*current != NULL){
        if(*current == element){
            *current = element->next;
            return;
        }
        current = &(*current)->next;
    }
}

int main() {

    struct list_element *e0 = (struct list_element*)&buf[4];
    struct list_element *e1 = (struct list_element*)&buf[4];

    struct list_element *current = head;


    printf("sizeof(current) = %ld\n", sizeof(current));
    buf[0] = (long)&buf[4];
    buf[4] = 0;

    for(int k = 0; k < 10; k++) {
        printf("[%d @ %p] 0x%lx\n", k, &buf[k], buf[k]);
    }
    return 0;
}
