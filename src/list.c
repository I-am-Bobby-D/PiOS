#include <stdio.h>
#include <list.h>

long buf[256];

//head at buf[0]
struct obj *head = NULL;

void list_add(struct list_element **list_head, struct list_element *new_element){
    if (new_element == NULL){
        return;
    }

    //pointer next @ address of new_element = *list_head
    new_element->next = *list_head;
    //add to head of list
    *list_head = new_element;
}

void list_remove(struct obj *element){
    struct obj **current = &head;

    while (*current != NULL){
        if(*current == element){
            *current = element->next;
            return;
        }
        current = &(*current)->next;
    }
}

int main() {

    struct obj *pObj = (struct obj*)&buf[4];
    struct obj *pObj2 = (struct obj*)&buf[4];

    head = pObj;

    printf("sizeof(pObj) = %ld\n", sizeof(pObj));
    buf[0] = (long)&buf[4];
    buf[4] = 0;

    for(int k = 0; k < 10; k++) {
        printf("[%d @ %p] 0x%lx\n", k, &buf[k], buf[k]);
    }
    return 0;
}
