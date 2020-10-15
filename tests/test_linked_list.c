#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    int data;
};

bool SearchItem(void* item, void* userData) {
	int searchKey = *((int*) userData);
    return ((struct node*) item)->key == searchKey;
}

void ListCallbackMethod(int index, void* listItem, void* userData) {
    struct node* item = (struct node*) listItem;
	printf("%d) %d:%d\n", index, item->key, item->data);
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

	linked_list_Iterate(list, NULL, NULL);

	linked_list_Iterate(list, ListCallbackMethod, NULL);

	int searchKey = 9;
    struct node* searchItem = (struct node*) linked_list_Search ( list, SearchItem, &searchKey );

    if(!searchItem) {
        fprintf(stderr, "Item not found\n");
    }

	searchKey = 2;
	searchItem = (struct node*) linked_list_Search ( list, SearchItem, &searchKey );

	if(searchItem) {
        fprintf(stderr, "Item found: key-> %d, data->%d\n", searchKey, ((struct node*)searchItem)->data );
    }

    struct node* removeItem = (struct node*) linked_list_Remove ( list, searchItem );
    free(removeItem);

	searchKey = 2;
	searchItem = (struct node*) linked_list_Search ( list, NULL, &searchKey );

	if(!searchItem) {
        fprintf(stderr, "Item not found\n");
    }

	linked_list_Remove ( list, NULL );


    linked_list_Drop ( list, NULL );


    linked_list_Drop ( list, FreeCallbackMethod );

    LinkedListRef* _list_empty = NULL;
    LinkedListRef** list_empty = &_list_empty;

	linked_list_Drop ( list_empty, NULL );

	linked_list_Insert ( list_empty, NULL );

	linked_list_Iterate ( list_empty, NULL, NULL );

	linked_list_Search ( list_empty, NULL, NULL );

	linked_list_Remove ( list_empty, NULL );

    return 0;
}

