#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "stdbool.h"

#ifndef LINKED_LIST_LOGGING
#define LINKED_LIST_LOGGING 0
#endif

#undef NULL
#define NULL 0

/**
 *   Callback Method template for search operation in a LinkedList
 * 
 *  listItem A test item     
 * 
 *  returns true if comparison successful, false otherwise
 */
typedef bool (*SearchMethod) (void* listItem, void* userData);

/**
 *  @brief Iterate Method 
 * 
 */
typedef void (*IterateMethod)(int index, void* listItem, void* userData);

/**
 *  @brief Free Method 
 * 
 */
typedef void (*FreeMethod)(void* listItem);


struct __linked_list_item_ref {
    void* data;
    struct __linked_list_item_ref* next;
};


typedef struct __linked_list_item_ref LinkedListRef;


/**
 * @brief Insert a new Item to the LinkedList
 * 
 * @param list Reference to the LinkedList
 * @param item Reference to the item to be added
 * 
 */
void linked_list_Insert ( LinkedListRef** list, void* item );

/**
 * @brief Iterate all items in the LinkedList
 * 
 * @param list Reference to the LinkedList
 * @param callbackMethod A callback function which is called for each 
 *  item. 
 * 
 */
void linked_list_Iterate ( LinkedListRef** list, IterateMethod callbackMethod, void* userData );

/**
 * @brief Search for an item in the LinkedList
 * 
 * @param list Reference to the LinkedList
 * @param testMethod A callback function which is called for each 
 *  item as a comparison test.
 * 
 * @returns Reference to the item found as a result of the search. 
 *          NULL if item not found.
 * 
 */
void* linked_list_Search ( LinkedListRef** list, SearchMethod testMethod, void* userData );


/**
 * @brief Remove an item from the LinkedList
 * 
 * @warning Freeing the memory is the developer's responsibility.
 * 
 * @param list Reference to the LinkedList
 * @param item Reference to the item to be removed
 *
 * @returns Reference to the recently removed item. 
 *          NULL if item is not found
 */
void* linked_list_Remove ( LinkedListRef** list, void* item );


/**
 * @brief Free the complete LinkedList and the data it contains
 * 
 * @param list Reference to the LinkedList
 * @param freeCallback Callback Method called for each item removed from linked list. Developer can free the memory of that item in this
 */
void linked_list_Drop ( LinkedListRef** list, FreeMethod freeCallback );

#endif // LINKED_LIST_H
