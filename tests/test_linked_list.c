#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    int data;
};

bool SearchItem(void* item, void* userData) {
    return ((struct node*) item)->key == 7;
}

void ListCallbackMethod(int index, void* item, void* userData) {
    printf("%d %d\n", index, ((struct node*) item)->data);
}

void FreeCallbackMethod(void* item) {
    free(item);
}

int main() {

    LinkedListRef* _list = NULL;
    LinkedListRef** list = &_list;

    struct node* item1 = malloc(sizeof(struct node));
    item1->key = 2;
    item1->data = 1;

    linked_list_Insert(list, item1);

    struct node* item2 = malloc(sizeof(struct node));
    item2->key = 5;
    item2->data = 2;

    linked_list_Insert(list, item2);

    struct node* item3 = malloc(sizeof(struct node));
    item3->key = 8;
    item3->data = 3;

    linked_list_Insert(list, item3);

    struct node* item4 = malloc(sizeof(struct node));
    item4->key = 4;
    item4->data = 4;

    linked_list_Insert(list, item4);

    struct node* item5 = malloc(sizeof(struct node));
    item5->key = 7;
    item5->data = 5;

    linked_list_Insert(list, item5);

    struct node* searchItem = (struct node*) linked_list_Search ( list, SearchItem, NULL );

    if(!searchItem) {
        fprintf(stderr, "Item not found\n");
        return 1;
    }

    struct node* removeItem = (struct node*) linked_list_Remove ( list, searchItem );
    free(removeItem);

    linked_list_Drop ( list, FreeCallbackMethod );

    return 0;
}

