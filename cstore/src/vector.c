
#include "cstore/vector.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> // memcpy/memmove


vector new_vector(
   unsigned int element_size,
   unsigned int max_elements,
   void* resource) {

   vector v;
   v.element_size = element_size;
   v.capacity = max_elements;
   v.size = 0;

   if(!resource) {
      v.resource = malloc(element_size * max_elements);
      v.internal_memory = true;
   }
   else {
      v.resource = resource;
      v.internal_memory = false;
   }
   return v;
}


vector new_heap_vector(unsigned int element_size) {
   return new_vector(element_size, DEFAULT_VECTOR_CAPACITY, NULL);
}


void* vector_at(vector* v, unsigned int index) {
   if(index > v->size) {
      return NULL;
   }
   return (uint8_t*)v->resource + (index * v->element_size);
}


void* vector_front(vector* v) {
   if(v->size == 0) {
      return NULL;
   }
   return v->resource;
}


void* vector_back(vector* v) {
   if(v->size == 0) {
      return NULL;
   }
   return (uint8_t*)v->resource + ((v->size-1) * v->element_size);
}


void* vector_data(vector *v) {
   return v->resource;
}


bool vector_empty(vector * v) {
   return v->size == 0;
}


void vector_reserve(vector* v, unsigned int new_cap, void* resource) {
   if(new_cap <= v->capacity) {
      return;
   }

   void* old_resource = v->resource;

   void* new_resource = resource ? resource : malloc(v->element_size * new_cap);

   v->resource = memmove(new_resource, old_resource, v->element_size * v->size);

   // If the last buffer was internally controled, free the memory
   if(v->internal_memory) {
      free(old_resource);
   }
   v->capacity = new_cap;
   v->internal_memory = resource ? false : true;
}


void vector_heap_reserve(vector* v, unsigned int new_cap) {
   vector_reserve(v, new_cap, NULL);
}


unsigned int vector_capacity(vector *v) {
   return v->capacity;
}


void vector_shrink_to_fit(vector *v) {
   v->resource = realloc(v->resource, v->size*v->element_size);
}


void vector_clear(vector* v) {
   v->size = 0;
}


void* vector_push_back(vector* v, void* element) {
   // If there is not enough space in the resource, and it is not internally managed, return NULL
   //    If it is internally managed then reserve to the next size up
   if(v->size == v->capacity) {
      // We don't control the memory, so we can't expand the capacity
      if(false == v->internal_memory) {
         return NULL;
      }
      vector_heap_reserve(v, v->capacity * CAPACITY_EXPANSION_MULTIPLIER);
   }

   void* result;
   // Once there is enough space, copy the element if provided
   //  else, provide an non-initialized value
   if(NULL != element) {
      result = memmove((uint8_t*)v->resource + v->element_size * v->size, element, v->element_size);
   }
   else {
      result = (uint8_t*)v->resource + v->element_size * v->size;
   }

   if(NULL != result) {
      v->size++;
   }

   return result;
}


bool vector_erase_range(vector* v, void* start_element, void* end_element) {
   // Verify the elements we are erasing are part of this vector
   assert(start_element >= v->resource && start_element < (v->resource + (v->capacity * v->element_size)));
   assert(end_element >= v->resource && end_element < (v->resource + (v->capacity * v->end_element)));
   // Verify these are aligned by the type boundaries
   assert((start_element - end_element) % v->element_size == 0);

   // Get the total size of the span
   unsigned int num_elements_to_delete = ((uint8_t*)start_element - (uint8_t*)end_element + v->element_size) / v->element_size;

   // The elements remaining (if any) after the section to erase
   void* first_kept_point = (uint8_t*)end_element + v->element_size;
   unsigned int index_of_first_kept = ((uint8_t*)first_kept_point - (uint8_t*)v->resource) / v->element_size;

   // We know the index of the first
   unsigned int num_elem_to_move = v->size - (index_of_first_kept - 1);

   void* result = memmove(start_element, first_kept_point, num_elem_to_move * v->element_size);

   if(NULL != result) {
      v->size = v->size - num_elements_to_delete;
   }

   // We need to determine how many elements are left
   // If the first kept is not the end of the range, copy it over the beginning
   return result != NULL;
}


bool vector_erase(vector* v, void* element) {
   return vector_erase_range(v, element, element);
}


bool vector_erase_index_range(vector* v, unsigned int start_index, unsigned int end_index) {
   return vector_erase_range(
      v,
      (uint8_t*)v->resource + (start_index * v->element_size),
      (uint8_t*)v->resource + (end_index * v->element_size));
}


bool vector_erase_index(vector* v, unsigned int index) {
   return vector_erase_index_range(v, index, index);
}


bool vector_pop_back(vector* v) {
   if(v->size > 0) {
      v->size--;
      return true;
   }
   return false;
}

void vector_delete(vector* v) {
   free(v->resource);
   v->resource = NULL;
   v->size = 0;
   v->capacity = 0;
}
