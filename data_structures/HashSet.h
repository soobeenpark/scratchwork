/* Hash Set Interface
 *
 * O(1) average and amortized insertion, lookup, and removal operations.
 *
 * Client is expected to define the types and operations under the
 * Client-defined Interface portion, so that the hash set can suit their
 * purpose.
 */

#ifndef HASH_SET_H
#define HASH_SET_H

#include <stdbool.h>
#include <stdlib.h>

/******* Client-defined Interface *******/
typedef void *elem;

// Compare two elements for equivalence.
typedef bool elem_equiv_fn(elem x, elem y);

// Hash function for element that returns integer.
typedef int elem_hash_fn(elem x);

// Function to delete the elem.
typedef void elem_free_fn(elem x);

/******* Library Interface *******/
typedef struct chain_node chain;
struct chain_node { // Linked List
    elem data;      // != NULL
    chain *next;
};

typedef struct hset_header hset;
struct hset_header {
    int size;      // 0 <= size
    int capacity;  // 0 < capacity
    chain **table; // length(table) == capacity

    elem_equiv_fn *equiv; // != NULL
    elem_hash_fn *hash;   // != NULL
};

// Client side type
typedef hset *hset_t;

// Create new hash set.
hset_t hset_new(int initial_capacity, elem_equiv_fn *equiv,
                elem_hash_fn *hash); // O(1)

// Destroy an existing hash set.
void hset_free(hset_t H, elem_free_fn *Fr); // O(1)

// Check if element exists in hash set.
bool hset_contains(hset_t H, elem x); // O(1) average

// Insert an element into the hash set.
void hset_insert(hset_t H, elem x); // O(1) average & amortized

// Removes the element from the hash set.
elem hset_remove(hset *H, elem x); // O(1) average & amortized.

#endif /* HASH_SET_H */
