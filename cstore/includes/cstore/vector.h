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

/// @brief Create a new vector on the heap
///
/// @param element_size
/// @return vector
vector new_heap_vector(unsigned int element_size);

/// @brief Get the element at the given index
///
/// @param v
/// @param index
/// @return void*
void* vector_at(vector* v, unsigned int index);

/// @brief Get the first element
///  Same as `vector_at(v, 0)`
///
/// @param v
/// @return void*
void* vector_front(vector* v);

/// @brief Get the last element
///   Same as `vector_at(v, v.size-1)`
/// @param v
/// @return void*
void* vector_back(vector* v);

/// @brief Modify the size of the vector
///   This will copy the old contents of the vector
///    into the resized resource
/// @param v
/// @param new_cap
/// @param resource
void vector_reserve(vector* v, unsigned int new_cap, void* resource);

/// @brief Modify the size of the vector, but let the library
///  figure out the memory management.  This will copy the old contents
///  of the vector into the resized resource
///
/// @param v
/// @param new_cap
void vector_heap_reserve(vector* v, unsigned int new_cap);

/// @brief Shrink the vector down to use exactly
///  enough bytes for the current elements
///
/// @param v
void vector_shrink_to_fit(vector *v);

/// @brief Clear out the vector.
///  This is a lazy clear - the vector will behave
///  as if it has zero capacity, but the memory is not
///  modified or released
///
/// @param v
void vector_clear(vector* v);

/// @brief Add a new element to the vector
///
/// @param v
/// @param element
/// @return void*
void* vector_push_back(vector*v, void* element);

/// @brief Erase elements in the given inclusive range
///
/// @param v
/// @param start_element
/// @param end_element
/// @return int
int vector_erase_range(vector* v, void* start_element, void* end_element);

/// @brief Erase a single element
///
/// @param v
/// @param element
/// @return int
int vector_erase(vector* v, void* element);

/// @brief Erase an inclusive range using indices
///
/// @param v
/// @param start_index
/// @param end_index
/// @return int
int vector_erase_index_range(vector* v, unsigned int start_index, unsigned int end_index);

/// @brief Erase a single element specified by the index
///
/// @param v
/// @param index
/// @return int
int vector_erase_index(vector* v, unsigned int index);

/// @brief Remove the back element from the vector
///
/// @param v
/// @return int
int vector_pop_back(vector* v);

/// @brief Delete the underlying resource used by this vector
///  and clear it's capacity.  To re-use the vector, re-size
///  to specify a resource
///
/// @param v
void vector_delete(vector*v);

#define CREATE_VECTOR_FUNCS(TYPE) \
   vector new_vector_##TYPE(unsigned int max_elements, void* resource) { return new_vector(sizeof(TYPE), max_elements, resource); } \
   vector new_heap_vector_##TYPE() { return new_heap_vector(sizeof(TYPE)); } \
   TYPE * vector_at_##TYPE(vector* v, unsigned int index){ return (TYPE *)vector_at(v, index); } \
   TYPE * vector_front_##TYPE(vector* v){ return (TYPE *)vector_front(v); } \
   TYPE * vector_back_##TYPE(vector* v){ return (TYPE *)vector_back(v); }


#endif // CSTORE_VECTOR_H
