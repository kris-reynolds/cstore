#ifndef CSTORE_RING_BUFFER_H
#define CSTORE_RING_BUFFER_H

/// @defgroup ring_buffer Ring Buffers
/// @{
/// A circular buffer with a fixed size section
/// of contiguous memory.  When the number of elements
/// exceeds the capacity of the container, the container
/// loops around and overwrites old data in the buffer.
/// @}

#ifndef NULL
#define NULL 0
#endif

typedef struct {
   void* resource;
   unsigned int element_size;
   unsigned int capacity;
   unsigned int size;
   int front;
   int back;
   int internal_memory;
} ring_buffer;

/// @brief Create a ring buffer using the specified resource
///
/// @param element_size
/// @param max_elements
/// @param resource
/// @return ring_buffer
ring_buffer new_ring_buffer(
   unsigned int element_size,
   unsigned int max_elements,
   void* resource);

/// @brief Create a ring buffer, have the library
///   manage the memory
///
/// @param element_size
/// @param max_elements
/// @return ring_buffer
ring_buffer new_heap_ring_buffer(
   unsigned int element_size,
   unsigned int max_elements);

/// @brief Get the element at the front of the line
///  This is the next element to be "popped"
///
/// @param element_size
/// @param max_elements
/// @return void*
void* ring_buffer_front(ring_buffer* buf);

/// @brief Get the element at the back of the line
///  This was the last element to be pushed
/// @return void*
void* ring_buffer_back(ring_buffer* buf);

/// @brief Push an element onto the ring
///  by copying from the passed pointer
///
/// @param element
/// @return int
void* ring_buffer_push(ring_buffer* buf, void* element);

/// @brief Add a new element to the ring,
///  and return a pointer so it can be populated
///
/// @return void*
void* ring_buffer_soft_push(ring_buffer* buf);

/// @brief Removes the element at the front
///  of the line
///
/// @return int
int ring_buffer_pop(ring_buffer* buf);

#endif // CSTORE_RING_BUFFER_H
