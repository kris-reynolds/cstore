#include "cstore/list.h"

#include <stdlib.h>

list new_linked_list(
   unsigned int element_size,
   unsigned int max_elements,
   void* resource) {

   list l = {
      .head = NULL,
      .tail = NULL,
      .element_size = element_size,
      .size = 0,
      .memory_pool = NULL,
      .resource = resource};

   // If the resource was specified, setup the pool
   if(l.resource) {
      l.memory_pool = (pool*)l.resource;
      l.resource = (unsigned char*)resource + sizeof(pool);
      initialize_pool(l.memory_pool, l.element_size + sizeof(ll_node), max_elements, l.resource);
   }

   return l;
}


list new_heap_linked_list(unsigned int element_size) {
   return new_linked_list(element_size, 0, NULL);
}


void* linked_list_soft_push_front(list* l) {
   // Get the node from the right spot
   ll_node* node = l->memory_pool ? pool_allocate(l->memory_pool) : malloc(l->element_size + sizeof(ll_node));

   if(!node) {
      return NULL;
   }

   // The data sits right next to the node in memory
   node->data = (unsigned char*)node + sizeof(ll_node);

   node->next = l->head;
   l->head = node;
   return l->head->data;
}


void* linked_list_soft_push_back(list* l) {
   // Get the node from the right spot
   ll_node* node = l->memory_pool ? pool_allocate(l->memory_pool) : malloc(l->element_size + sizeof(ll_node));

   if(!node) {
      return NULL;
   }

   // The data sits right next to the node in memory
   node->data = (unsigned char*)node + sizeof(ll_node);

   node->next = NULL;
   l->tail->next = node;
   l->tail = node;
   return l->tail->data;
}


int linked_list_remove(list* l, ll_node* node) {
   // Head is really easy to remove
   // For all others we need to iterate over the list
   if(node == l->head) {
      l->head = l->head->next;
   }
   // Iterate over the list with a trailing pointer
   //  to find the node
   else {
      ll_node* first = l->head;
      ll_node* second = l->head->next;

      while(first && second) {
         if(second == node) {
            first->next = second->next;
            break;
         }
         first = first->next;
         second = second->next;
      }

      // If we did not find a match, the remove failed
      if(second == NULL) {
         return 0;
      }
   }

   if(l->memory_pool) {
      pool_deallocate(l->memory_pool, node);
   }
   else {
      free(node);
   }

   return 1;
}


void linked_list_delete(list* l) {
   while(l->head) {
      linked_list_remove(l, l->head);
   }

   if(l->resource) {
      free(l->resource);
   }

   l->head = NULL;
   l->tail = NULL;
   l->size = 0;
   l->memory_pool = NULL;
   l->resource = NULL;
}
