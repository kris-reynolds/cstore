#include "cstore/ring_buffer.h"

#include <assert.h>
#include <stdlib.h>

ring_buffer new_ring_buffer(
   unsigned int element_size,
   unsigned int max_elements,
   void* resource)
{
   ring_buffer buff;
   buff.element_size = element_size;
   buff.capacity = max_elements;
   buff.size = 0;
   buff.front = 0;
   buff.back = 0;

   if(!resource) {
      buff.resource = malloc(element_size * max_elements);
      buff.internal_memory = 1;
   }
   else {
      buff.resource = resource;
      buff.internal_memory = 0;
   }
   return buff;
}

ring_buffer new_heap_ring_buffer(
   unsigned int element_size,
   unsigned int max_elements)
{
   return new_ring_buffer(element_size, max_elements, NULL);
}


void* ring_buffer_front(ring_buffer* buf) {
   assert(buf);
   assert(buf->size != 0);

   return (unsigned char*)buf->resource + buf->front * buf->element_size;
}

void* ring_buffer_back(ring_buffer* buf) {
   assert(buf);
   assert(buf->size != 0);
   return (unsigned char*)buf->resource + buf->front * buf->element_size;
}

int ring_buffer_push(ring_buffer* buf, void* element);

void* ring_buffer_soft_push(ring_buffer* buf);

int ring_buffer_pop(ring_buffer* buf);
