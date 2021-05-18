#ifndef CSTORE_VECTOR_H
#define CSTORE_VECTOR_H


#ifndef NULL
#define NULL 0
#endif

#define DEFAULT_VECTOR_CAPACITY 10
#define CAPACITY_EXPANSION_MULTIPLIER 2

typedef struct vector_t {
   void* resource;
   unsigned int element_size;
   unsigned int capacity;
   unsigned int size;
   int internal_memory;
} vector;


typedef struct vectorT_t {
   vector internal;
   void* (*at)(int);

} vectorT;

/// @brief Create a new vector_t using the given
///        buffer as the underlying resource
/// @param element_size - Size of a single element
/// @param max_elements - Max elements supported by the resource
/// @param resource - Buffer resource to use
/// @return vector_t*
vector new_vector(
   unsigned int element_size,
   unsigned int max_elements,
   void* resource);

vector new_heap_vector(unsigned int element_size);

// Access
void* vector_at(vector* v, unsigned int index);
void* vector_front(vector* v);
void* vector_back(vector* v);
void* vector_data(vector *v);

// Capacity
int vector_empty(vector * v);
void vector_reserve(vector* v, unsigned int new_cap, void* resource);
void vector_heap_reserve(vector* v, unsigned int new_cap);
unsigned int vector_capacity(vector *v);
void vector_shrink_to_fit(vector *v);

// Modifiers
void vector_clear(vector* v);
void* vector_push_back(vector*v, void* element);

int vector_erase_range(vector* v, void* start_element, void* end_element);
int vector_erase(vector* v, void* element);
int vector_erase_index_range(vector* v, unsigned int start_index, unsigned int end_index);
int vector_erase_index(vector* v, unsigned int index);

int vector_pop_back(vector* v);

void vector_delete(vector*v);

#define CREATE_VECTOR_FUNCS(TYPE) \
   vector new_vector_##TYPE(unsigned int max_elements, void* resource) { return new_vector(sizeof(TYPE), max_elements, resource); } \
   vector new_heap_vector_##TYPE() { return new_heap_vector(sizeof(TYPE)); } \
   TYPE * vector_at_##TYPE(vector* v, unsigned int index){ return (TYPE *)vector_at(v, index); } \
   TYPE * vector_front_##TYPE(vector* v){ return (TYPE *)vector_front(v); } \
   TYPE * vector_back_##TYPE(vector* v){ return (TYPE *)vector_back(v); } \
   TYPE * vector_data_##TYPE(vector* v){ return (TYPE *)vector_data(v); }


#endif // CSTORE_VECTOR_H
