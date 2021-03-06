#ifndef CSTORE_LIST_H
#define CSTORE_LIST_H

#include "cstore/pool.h"

/// @defgroup lists Linked Lists
/// @{
/// A list of elements in non-contiguous memory
/// @}

#ifndef NULL
#define NULL 0
#endif

typedef struct ll_node_t {
   void* data;
   struct ll_node_t *next;
} ll_node;

typedef struct {
   ll_node *head;
   ll_node *tail;

   unsigned int element_size;
   unsigned int size;
   pool* memory_pool;
   void* resource;

} list;

/// @brief Create a list using the specified resource
///
/// @param element_size
/// @param max_elements
/// @param resource - Should be of at least size element_size * max_elements + sizeof(pool)
/// @return list
/// TODO: There is a lot of hidden logic based on what is feed in (max elements vs resource)
///       We should just create a new builder method that allows the input of a pool or
///       resource.
list new_linked_list(
   unsigned int element_size,
   unsigned int max_elements,
   void* resource);

/// @brief Create a list, have the library
///   manage the memory
///
/// @param element_size
/// @param max_elements
/// @return list
list new_heap_linked_list(
   unsigned int element_size);

/// @brief
///
/// @param l
/// @return void*
void* linked_list_soft_push_front(list* l);

/// @brief
///
/// @param l
/// @return void*
void* linked_list_soft_push_back(list* l);

/// @brief
///
/// @param l
/// @param node
/// @return int
int linked_list_remove(list* l, ll_node* node);

/// @brief
///
/// @param l
void linked_list_delete(list* l);

#endif // CSTORE_LIST_H
