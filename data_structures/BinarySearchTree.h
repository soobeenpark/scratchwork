/* Binary Search Tree Dictionary Interface
 *
 * Retains entries in sorted order.
 *
 * O(logn) average insertion, lookup, and removal operations.
 *
 * This binary search tree is not self-balancing, and so the worst-case
 * time complexity for each of those operations are still O(n).
 * Look for AVL Trees or other self-balacing trees that are improved BSTs.
 */

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stdbool.h>
#include <stdlib.h>

/******* Client-defined Interface *******/
typedef void *entry;
typedef void *key;

// Extract key from entry.
typedef key entry_key_fn(entry x);

// Compare two keys for equivalence.
typedef int key_compare_fn(key k1, key k2);

// Function to delete the entry.
typedef void entry_free_fn(entry e);

/******* Library Interface *******/
/*** Binary Search Tree Interface ***/
typedef struct tree_node tree;
struct tree_node {
    entry data; // != NULL
    tree *left;
    tree *right;
};

/*** Dictionary Interface ***/
typedef struct dict_header dict;
struct dict_header {
    int size; // 0 <= size
    tree *root;

    entry_key_fn *entry_key;     // != NULL
    key_compare_fn *key_compare; // != NULL
};

// Client side type
typedef dict *dict_t;

// Create new BST dictionary.
dict_t dict_new(entry_key_fn *entry_key, key_compare_fn *key_compare); // O(1)

// Destroy an existing BST dictionary.
void dict_free(dict_t D, entry_free_fn *Fr); // O(1)

// Lookup entry in BST dictionary.
// If entry exists, that entry is returned. If doesn't exist, NULL is returned.
entry dict_lookup(dict_t D, key k); // O(logn) average

// Insert an entry into the BST dictionary.
void dict_insert(dict_t D, entry x); // O(logn) average

// Removes an entry from the BST dictionary.
void dict_remove(dict *D, key k, entry_free_fn *Fr);

// Find the minimum entry in the BST dictionary.
entry dict_find_min(dict_t D); // O(logn) average

// Get size of dictionary.
int dict_size(dict_t D); // O(1)

#endif /* BINARY_SEARCH_TREE_H */
