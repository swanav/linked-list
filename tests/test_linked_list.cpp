#include <stdio.h>
#include <stdlib.h>

#include "gtest/gtest.h"

extern "C" {
	#include "linked_list.h"
}


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

TEST(linked_list_Insert, ShouldNotInsertNullPointer) {
	LinkedListRef* _list = NULL;
    LinkedListRef** list = &_list;
    linked_list_Insert(list, NULL);
}

TEST(linked_list_Insert, ShouldCreateLinkedListIfEmpty) {
	LinkedListRef* _list = NULL;
    LinkedListRef** list = &_list;
	struct node* item1 = (struct node* ) malloc(sizeof(struct node));
    item1->key = 2;
    item1->data = 1;

    linked_list_Insert(list, item1);
}

TEST(linked_list_Insert, ShouldAddItemToLinkedList) {
	LinkedListRef* _list = NULL;
    LinkedListRef** list = &_list;

	struct node* item1 = (struct node* ) malloc(sizeof(struct node));
    item1->key = 2;
    item1->data = 1;

    linked_list_Insert(list, item1);

	struct node* item2 = (struct node*) malloc(sizeof(struct node));
    item2->key = 5;
    item2->data = 2;

    linked_list_Insert(list, item2);
}

TEST(linked_list_Insert, ShouldReturnGracefullyIfMallocFails) {
	LinkedListRef* _list = NULL;
    LinkedListRef** list = &_list;

	struct node* item1 = (struct node* ) malloc(sizeof(struct node));
    item1->key = 2;
    item1->data = 1;

	// Use some other malloc routine
    linked_list_Insert(list, item1);
}

TEST(linked_list_Iterate, ShouldNotIterateEmptyList) {
	LinkedListRef* _list = NULL;
    LinkedListRef** list = &_list;

	linked_list_Iterate(list, NULL, NULL);
}

TEST(linked_list_Iterate, ShouldNotIterateListWithoutACallbackMethod) {
	LinkedListRef* _list = NULL;
    LinkedListRef** list = &_list;

	struct node* item1 = (struct node* ) malloc(sizeof(struct node));
    item1->key = 2;
    item1->data = 1;
    linked_list_Insert(list, item1);

	linked_list_Iterate(list, NULL, NULL);
}

TEST(linked_list_Iterate, ShouldIterateAValidList) {
	LinkedListRef* _list = NULL;
    LinkedListRef** list = &_list;

	struct node* item1 = (struct node* ) malloc(sizeof(struct node));
    item1->key = 2;
    item1->data = 1;
    linked_list_Insert(list, item1);

	linked_list_Iterate(list, ListCallbackMethod, NULL);
}

TEST(linked_list_Search, ShouldNotSearchEmptyList) {
	LinkedListRef* _list = NULL;
    LinkedListRef** list = &_list;

	linked_list_Search(list, NULL, NULL);
}

TEST(linked_list_Search, ShouldNotSearchListWithoutACallbackMethod) {
	LinkedListRef* _list = NULL;
    LinkedListRef** list = &_list;

	struct node* item1 = (struct node* ) malloc(sizeof(struct node));
    item1->key = 2;
    item1->data = 1;
    linked_list_Insert(list, item1);

	linked_list_Search(list, NULL, NULL);
}

TEST(linked_list_Search, ShouldSearchForItemInList) {
	LinkedListRef* _list = NULL;
    LinkedListRef** list = &_list;

	struct node* item1 = (struct node* ) malloc(sizeof(struct node));
    item1->key = 2;
    item1->data = 1;
    linked_list_Insert(list, item1);

	struct node* item2 = (struct node* ) malloc(sizeof(struct node));
    item2->key = 4;
    item2->data = 7;
    linked_list_Insert(list, item2);

	int searchKey = 2;

	struct node* item3 = (struct node*) linked_list_Search(list, SearchItem, &searchKey);

	EXPECT_EQ(item1, item3);
}

TEST(linked_list_Search, ShouldReturnNullIfItemNotInList) {
	LinkedListRef* _list = NULL;
    LinkedListRef** list = &_list;

	struct node* item1 = (struct node* ) malloc(sizeof(struct node));
    item1->key = 2;
    item1->data = 1;
    linked_list_Insert(list, item1);

	int searchKey = 4;

	struct node* item2 = (struct node*) linked_list_Search(list, SearchItem, &searchKey);

	EXPECT_EQ(item2, nullptr);
}

TEST(linked_list_Remove, ShouldReturnNullIfListEmpty) {
	LinkedListRef* _list = NULL;
    LinkedListRef** list = &_list;

	struct node* item = (struct node*) linked_list_Remove(list, NULL);

	EXPECT_EQ(item, nullptr);
}

TEST(linked_list_Remove, ShouldReturnNullIfSearchItemNull) {
	LinkedListRef* _list = NULL;
    LinkedListRef** list = &_list;

	struct node* item1 = (struct node* ) malloc(sizeof(struct node));
    item1->key = 2;
    item1->data = 1;
    linked_list_Insert(list, item1);

	struct node* item = (struct node*) linked_list_Remove(list, NULL);

	EXPECT_EQ(item, nullptr);
}

TEST(linked_list_Remove, ShouldReturnFirstItemIfItIsAMatch) {
	LinkedListRef* _list = NULL;
    LinkedListRef** list = &_list;

	struct node* item1 = (struct node* ) malloc(sizeof(struct node));
    item1->key = 2;
    item1->data = 1;
    linked_list_Insert(list, item1);

	struct node* item = (struct node*) linked_list_Remove(list, item1);

	EXPECT_EQ(item, item1);
}

TEST(linked_list_Remove, ShouldReturnItemIfItIsAMatch) {
	LinkedListRef* _list = NULL;
    LinkedListRef** list = &_list;

	struct node* item1 = (struct node* ) malloc(sizeof(struct node));
    item1->key = 2;
    item1->data = 1;
    linked_list_Insert(list, item1);

	struct node* item2 = (struct node* ) malloc(sizeof(struct node));
    item2->key = 4;
    item2->data = 7;
    linked_list_Insert(list, item2);

	struct node* item = (struct node*) linked_list_Remove(list, item1);

	EXPECT_EQ(item, item1);
}

TEST(linked_list_Remove, ShouldReturnItemAndRelinkListIfItemRemoved) {
	LinkedListRef* _list = NULL;
    LinkedListRef** list = &_list;

	struct node* item1 = (struct node* ) malloc(sizeof(struct node));
    item1->key = 2;
    item1->data = 1;
    linked_list_Insert(list, item1);

	struct node* item2 = (struct node* ) malloc(sizeof(struct node));
    item2->key = 4;
    item2->data = 7;
    linked_list_Insert(list, item2);

	struct node* item3 = (struct node* ) malloc(sizeof(struct node));
    item2->key = 6;
    item2->data = 5;
    linked_list_Insert(list, item3);

	struct node* item = (struct node*) linked_list_Remove(list, item1);

	EXPECT_EQ(item, item1);
}

TEST(linked_list_Remove, ShouldReturnNullIfItemNotFound) {
	LinkedListRef* _list = NULL;
    LinkedListRef** list = &_list;

	struct node* item1 = (struct node* ) malloc(sizeof(struct node));
    item1->key = 2;
    item1->data = 1;
    linked_list_Insert(list, item1);

	struct node* item2 = (struct node* ) malloc(sizeof(struct node));
    item2->key = 4;
    item2->data = 7;
    linked_list_Insert(list, item2);

	struct node* item3 = (struct node* ) malloc(sizeof(struct node));
    item3->key = 6;
    item3->data = 5;
    linked_list_Insert(list, item3);

	struct node* item4 = (struct node* ) malloc(sizeof(struct node));
    item4->key = 6;
    item4->data = 5;

	struct node* item = (struct node*) linked_list_Remove(list, item4);

	EXPECT_EQ(item, nullptr);
}


TEST(linked_list_Drop, ShouldNotDropEmptyList) {
	LinkedListRef* _list = NULL;
    LinkedListRef** list = &_list;

	linked_list_Drop(list, FreeCallbackMethod);
}

TEST(linked_list_Drop, ShouldNotDropListWithoutFreeCallback) {
	LinkedListRef* _list = NULL;
    LinkedListRef** list = &_list;

	struct node* item1 = (struct node* ) malloc(sizeof(struct node));
    item1->key = 2;
    item1->data = 1;
    linked_list_Insert(list, item1);

	linked_list_Drop(list, NULL);
}

TEST(linked_list_Drop, ShouldDropValidList) {
	LinkedListRef* _list = NULL;
    LinkedListRef** list = &_list;

	struct node* item1 = (struct node* ) malloc(sizeof(struct node));
    item1->key = 2;
    item1->data = 1;
    linked_list_Insert(list, item1);

	linked_list_Drop(list, FreeCallbackMethod);

	EXPECT_EQ(*list, nullptr);
}
