#ifndef CSTORE_BST_H
#define CSTORE_BST_H

#include "cstore/pool.h"

/// @defgroup bst Binary Search Tree
/// @{
/// A binary search tree
/// @}

typedef struct bst_node_t {
   struct bst_node_t* left;
   struct bst_node_t* right;
   void* data;
} bst_node;

typedef struct bst_t {
   bst_node* root;
   unsigned int element_size;
   unsigned int size;
   pool* memory_pool;
   void* resource;
} bst;


/// @brief Creation (resource/pool/etc)

/// @brief add - Adds a new element to the BST

/// @brief find - Gets an element from the BST (or null)

/// @brief balance - Rebalances the tree

/// @brief remove - Removes an element from the BST

#endif
