![CMake](https://github.com/swanav/LinkedList/workflows/CMake/badge.svg)
![CodeQL](https://github.com/swanav/LinkedList/workflows/CodeQL/badge.svg)
[![codecov](https://codecov.io/gh/swanav/LinkedList/branch/main/graph/badge.svg)](https://codecov.io/gh/swanav/LinkedList)
[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2Fswanav%2FLinkedList.svg?type=shield)](https://app.fossa.com/projects/git%2Bgithub.com%2Fswanav%2FLinkedList?ref=badge_shield)

# Linked List

# API Documentation

<hr/>

## <a name='linked_list_Create'></a> Create a Linked List

```c
LinkedListRef* linked_list_Create ();
```
Creates a new Linked List. Allocating memory on the heap.

- **returns** [LinkedList*](#LinkedListRef) Reference to the created LinkedList

<hr/>

## <a href='#linked_list_Drop'></a> Drop a Linked List

```c
void linked_list_Drop ( LinkedListRef** list, FreeMethod freeCallback );
```

Free the complete Linked List and the data it contains.

 - **param** [list](#LinkedListRef) - Reference to the LinkedList.
 - **param** [freeCallback](#FreeMethodCallback) - Callback Method called for each item removed from linked list. 
 - **@warning** Developer __*should*__ free the memory of that item in this callback.

<hr/>

## <a name='linked_list_Insert'></a> Insert an item
```c
void linked_list_Insert ( LinkedListRef** list, void* item );
```

Insert a new Item to the LinkedList

 - **param** [list](#LinkedListRef) - Reference to the LinkedList
 - **param** [item](#) - Reference to the item to be added

<hr/>

## <a name='linked_list_Remove'></a> Remove an item
```c
void* linked_list_Remove ( LinkedListRef** list, void* item );
```

Remove an item from the LinkedList

 - **param** [list](#LinkedListRef) - Reference to the LinkedList
 - **param** [item](#) - Reference to the item to be removed
 - **returns** [void*](#) - Reference to the recently removed item, NULL if item is not found
 - __@warning__ Freeing the allocated memory of the returned pointer is the developer's responsibility.


<hr/>

## <a name='linked_list_Iterate'></a> Iterate all items
```c
void linked_list_Iterate ( LinkedListRef** list, IterateMethod callbackMethod, void* userData );
```

Iterate all items in the LinkedList

 - **param** [list](#LinkedListRef) - Reference to the LinkedList
 - **param** [callbackMethod](IterateMethodCallback) - A callback function which is called for each item  
 - **param** [userData](#) - A pointer which is sent to the callback method. 


<hr/>

## <a name='linked_list_Search'></a> Search for an item
```c
void* linked_list_Search ( LinkedListRef** list, SearchMethod testMethod, void* userData );
```

Search for an item in the LinkedList

 - **param** [list](#LinkedListRef) - Reference to the LinkedList
 - **param** [testMethod](SearchMethodCallback) - A callback function which is called for each item as a comparison test.
 - **param** [userData](#) - A pointer which is sent to the callback method. 
 - **returns** [void*](#) Reference to the item found as a result of the search, NULL if item not found.



# Type Definitions

## <a href='#LinkedListRef'></a> LinkedListRef Structure
```c
struct __linked_list_item_ref {
    void* data;
    struct __linked_list_item_ref* next;
};

typedef struct __linked_list_item_ref LinkedListRef;
```


## <a name='SearchMethodCallback'></a> SearchMethod Callback
```c
typedef bool (*SearchMethod) (void* listItem, void* userData);
```

Callback Method template for search operation in a LinkedList

- **param** [listItem](#) - A test item
- **param** [userData](#) - A pointer as given to `linked_list_Search`
- **returns** [boolean](#) - true if comparison successful, false otherwise


## <a id='IterateMethodCallback'></a> Iterate Method Callback
```c
typedef void (*IterateMethod)(int index, void* listItem, void* userData);
```

Callback Method for each item in the iteration of the linked list
- **param** [index](#) - item index
- **param** [listItem](#) - An item from the linked list
- **param** [userData](#) - A pointer as given to `linked_list_Iterate`


## <a name='FreeMethodCallback'></a> Free Method Callback 

```c
typedef void (*FreeMethod)(void* listItem);
```
Callback Method for each item in the iteration of the linked list
- **param** [listItem](#) - Pointer to the item to be freed. 


## License
[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2Fswanav%2FLinkedList.svg?type=large)](https://app.fossa.com/projects/git%2Bgithub.com%2Fswanav%2FLinkedList?ref=badge_large)
