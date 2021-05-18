#ifndef CSTORE_FIXED_POOL_H
#define CSTORE_FIXED_POOL_H

#ifndef NULL
#define NULL 0
#endif

/// @defgroup memory_pool Pools
/// @{
/// A memory pool implementation. Used to handle pre-allocated
///  memory resources for containers that may use/release
///  memory in a non-contiguous fashion (lists, maps, etc)
/// @}


/// @brief Provides a very simple linked list of free blocks
///
typedef struct free_block_t {
   struct free_block_t *next;
} free_block;

typedef struct {
   unsigned int element_size;
   // We need to fit the free_blocks in the pool too. If the free_block
   //  is larger than the element, that drives the block size
   unsigned int block_size;
   unsigned int capacity;
   free_block* free_head;
   void* blocks;
} pool;

/// @brief Create a new pool
///
/// @param element_size
/// @param num_elements - Max capacity of the pool. Set to 0 for no max.  If there is
///                      no max, then more memory will be allocated as needed
/// @param resource - If num elements is NOT specified, this is not used.  If the
///               number of elements is used, then the resource should be at least
///               element_size*num_elements bytes in size.  If the resource is NULL,
///               and num_elements is specified, the pool will allocate all the memory
///               needed upfront.
/// @return pool
pool new_pool(unsigned int element_size, unsigned int num_elements, void* resource);

/// @brief Initialize a pool
///
/// @param p
/// @param element_size
/// @param num_elements
/// @param resource - If not provided resources are allocated
void initialize_pool(pool* p, unsigned int element_size, unsigned int num_elements, void* resource);

/// @brief Get a single element from the pool
///
/// @param p
/// @return void*
void* pool_allocate(pool* p);

/// @brief Release an element back to the pool
///
/// @param p
/// @param element
void pool_deallocate(pool* p, void* element);

/// @brief Free up all memory blocks
///
/// @param p
void pool_free_all(pool* p);

/// @brief Free all memory held by the pool.  If the pool
///      did not have a max number of elements, then it did not
///      allocate a contigious block of memory upfront.  Therefore
///      this will free all the blocks held by the pool in the "free"
///      list.  It will not free blocks that have not been returned
///      to the pool.
///
/// @param p
void release_pool(pool* p);

#endif // CSTORE_FIXED_POOL_H
