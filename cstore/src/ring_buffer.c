#include "cstore/ring_buffer.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

ring_buffer new_ring_buffer(
   unsigned int element_size,
   unsigned int max_elements,
   void* resource)
{
   ring_buffer buff;
   buff.element_size = element_size;
   buff.capacity = max_elements;
   buff.size = 0;
   buff.front = -1;
   buff.back = -1;

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


void* ring_buffer_push(ring_buffer* buf, void* element) {
   assert(buf);

   unsigned char* dest = ring_buffer_soft_push(buf);
   memcpy(dest, element, buf->element_size);
   return dest;
}


void* ring_buffer_soft_push(ring_buffer* buf) {
   assert(buf);

   buf->back = (buf->back == buf->capacity-1) ? 0 : buf->back+1;

   // If the front is not initialized, set it to the back
   if(buf->front == -1) {
      buf->front = buf->back;
      buf->size++;
   }
   // If back of the line wrap around, increment the front
   else if(buf->front == buf->back) {
      buf->front = (buf->front == buf->capacity-1) ? 0 : buf->front+1;
   }
   // If this is not a wrap, increment the size
   else {
      buf->size++;
   }

   return (unsigned char*)buf->resource + buf->back * buf->element_size;
}


int ring_buffer_pop(ring_buffer* buf) {
   assert(buf);
   if(buf->size == 0) {
      return 0;
   }

   buf->front = (buf->front == buf->capacity-1) ? 0 : buf->front+1;
   buf->size--;

   if(buf->size == 0) {
      buf->front = -1;
   }

   return 1;
}
