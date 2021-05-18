#include "cstore/pool.h"

#include <assert.h>
#include <stdlib.h>

pool new_pool(unsigned int element_size, unsigned int num_elements, void* resource) {

   pool p;

   initialize_pool(&p, element_size, num_elements, resource);

   return p;
}

void initialize_pool(pool* p, unsigned int element_size, unsigned int num_elements, void* resource) {
   // If the user provides their own resource - the assumption is it is
   //  at least element_size * num_elements bytes in size.  If not then
   //  that is on them to figure out.
   int block_size = element_size < sizeof(free_block) ? sizeof(free_block) : element_size;

   p->element_size = element_size;
   p->block_size = block_size;
   p->capacity = num_elements;
   p->free_head = NULL;
   // Only malloc if a capacity was specified.  If no capacity or no
   //  resource, then we will malloc as needed.  If we have a known
   //  max capacity, allocate the memory now
   p->blocks = (resource || p->capacity == 0) ? resource : malloc(block_size * num_elements);

   if(p->blocks) {
      p->free_head = p->blocks;

      // Starting point
      free_block* next_free = p->free_head;

      // Initialize the free list
      for(int i = 1; i < p->capacity; ++i) {
         next_free->next = (free_block*)((unsigned char*)p->blocks + p->block_size * i);
         next_free = next_free->next;
      }
      next_free->next = NULL;
   }
}

void* pool_allocate(pool* p) {
   assert(p);

   // If we have a fixed size of blocks, and we have no
   //  free blocks, the allocate fails
   if(!p->free_head && p->capacity != 0) {
      return NULL;
   }
   // If there are no free blocks, but the capacity is not fixed,
   //  then create a new block
   else if(!p->free_head) {
      p->free_head = malloc(p->block_size);
      p->free_head->next = NULL;
   }

   // Get the pointer and move the head
   void* ptr = p->free_head;
   p->free_head = p->free_head->next;
   return ptr;
}


void pool_deallocate(pool* p, void* element) {
   assert(p);
   // Make sure the element is actually part of this pool if the pool is using a
   //  continguous memory block
   assert(!p->blocks || (element >= p->blocks && element <= p->blocks + p->block_size * p->capacity));

   // Advertise the block as free
   free_block* old_head = p->free_head;
   p->free_head = element;
   p->free_head->next = old_head;
}


void pool_deallocate_all(pool* p) {

   if(p->blocks) {
      free_block* next_free = p->blocks;
      // Initialize the free list
      for(int i = 1; i < p->capacity; ++i) {
         next_free->next = (free_block*)((unsigned char*)p->blocks + p->block_size * i);
         next_free = next_free->next;
      }
      next_free->next = NULL;
   }
}


void release_pool(pool* p) {
   // If the blocks are specified, free that and clear the members
   // If the blocks are not specified, just free the known "free"
   //  elements.  It is up to the user to free resources not yet
   //  returned to the pool
   if(p->blocks) {
      free(p->blocks);
   }
   // If blocks is not specified, then all the blocks were malloced
   //  as they were needed.  Free everything that has been
   //  returned to the pool so far
   else {
      free_block* next_free = p->free_head;
      while(next_free) {
         free_block* tmp = next_free->next;
         free(next_free);
         next_free = tmp;
      }
   }
   p->blocks = NULL;
   p->capacity = 0;
   p->free_head = NULL;
}
