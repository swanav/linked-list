#include "linked_list.h"

#include <stdlib.h>

#if LINKED_LIST_LOGGING > 0
#include <stdio.h>
#define LL_LOGE(...) fprintf(stderr, "[linked list]: " __VA_ARGS__)
#else
#define LL_LOGE(...)
#endif



void linked_list_Insert ( LinkedListRef** list, void* item ) {

    if ( !item ) {
        LL_LOGE ( "Item not initialised.\n" );
        return;
    }

    LinkedListRef* newItem = ( LinkedListRef* ) malloc ( sizeof ( LinkedListRef ) );

    if ( !newItem ) {
        LL_LOGE ( "Could not create list item\n" );
        return;
    }

    newItem->data = item;
    newItem->next = *list;
    *list = newItem;
}

void linked_list_Iterate ( LinkedListRef** list, IterateMethod callbackMethod, void* userData ) {

    if ( !*list ) {
        LL_LOGE ( "List Reference not initialised.\n" );
        return;
    }

    if ( !callbackMethod ) {
        LL_LOGE ( "No Callback Method provided.\n" );
        return;
    }

    LinkedListRef* ptr = *list;
    
    int index = 0;

    while ( ptr ) {
        callbackMethod ( index++, ptr->data, userData );
        ptr = ptr->next;
    }

}

void* linked_list_Search ( LinkedListRef** list, SearchMethod testMethod, void* userData ) {

    if ( !*list ) {
        LL_LOGE ( "List Reference not initialised.\n" );
        return NULL;
    }

    if ( !testMethod ) {
        LL_LOGE ( "No Callback Method provided.\n" );
        return NULL;
    }

    LinkedListRef* ptr = *list;

    while ( ptr ) {
        if ( testMethod ( ptr->data, userData ) == true ) {
            return ptr->data;
        }
        ptr = ptr->next;
    }
    return NULL;
}

void* linked_list_Remove ( LinkedListRef** list, void* item ) {

    if ( !*list ) {
        LL_LOGE ( "List Reference not initialised.\n" );
        return NULL;
    }

    if ( !item ) {
        LL_LOGE ( "Item not initialised.\n" );
        return NULL;
    }


    LinkedListRef* prev = *list;

    if ( !prev ) {
        // List is empty
        return NULL;
    }

    LinkedListRef* toRemove = prev->next;
    void* toReturn = NULL;

    // Check the first item
    if ( prev->data == item) {
        *list = prev->next;
        toReturn = prev->data;
        free ( prev );
        return toReturn;
    }


    while ( toRemove ) {
        if ( toRemove->data == item ) {
            prev->next = toRemove->next;
            toReturn = toRemove->data;
            free ( toRemove );
            return toReturn;
        }
        prev = prev->next;
        toRemove = toRemove->next;
    }

    return NULL;
}

void linked_list_Drop ( LinkedListRef** list, FreeMethod freeCallback ) {

    if ( !*list ) {
        LL_LOGE ( "List Reference not initialised.\n" );
        return;
    }

    if ( !freeCallback ) {
        LL_LOGE ( "Free Callback not provided not initialised.\n" );
        return;
    }

    LinkedListRef *ptr = *list, *temp;

    while ( ptr ) {
        temp = ptr;
        ptr = ptr->next;
        freeCallback( temp->data );
        free ( temp );
    }

    *list = NULL;
}
