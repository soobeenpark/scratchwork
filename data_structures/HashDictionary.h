/* Hash Dictionary Interface
 *
 * O(1) average and amortized insertion and lookup operations.
 *
 * Client is expected to define the types and operations under the
 * Client-defined Interface portion, so that the hash dictionary can suit their
 * purpose.
 */

#ifndef HASH_DICTIONARY_H
#define HASH_DICTIONARY_H

#include <stdbool.h>
#include <stdlib.h>

/******* Client-defined Interface *******/
typedef void *entry;
typedef void *key;

// Extract key from entry.
typedef key entry_key_fn(entry x);

// Compare two keys for equivalence.
typedef bool key_equiv_fn(key k1, key k2);

// Hash function for key that returns integer.
typedef int key_hash_fn(key k);

// Function to delete the entry.
typedef void entry_free_fn(entry e);

/******* Library Interface *******/
typedef struct chain_node chain;
struct chain_node { // Linked List
    entry data;     // != NULL
    chain *next;
};

typedef struct hdict_header hdict;
struct hdict_header {
    int size;      // 0 <= size
    int capacity;  // 0 < capacity
    chain **table; // length(table) == capacity

    entry_key_fn *entry_key; // != NULL
    key_equiv_fn *equiv;     // != NULL
    key_hash_fn *hash;       // != NULL
};

// Client side type
typedef hdict *hdict_t;

// Create new hash dictionary.
hdict_t hdict_new(int initial_capacity, entry_key_fn *entry_key,
                  key_equiv_fn *equiv,
                  key_hash_fn *hash); // O(1)

// Destroy an existing hash dictionary.
void hdict_free(hdict_t H, entry_free_fn *Fr); // O(1)

// Lookup entry in hash dictionary.
// If entry exists, that entry is returned. If doesn't exist, NULL is returned.
entry hdict_lookup(hdict_t H, key k); // O(1) average

// Insert an entry into the hash dictionary.
void hdict_insert(hdict_t H, entry x); // O(1) average & amortized

// Removes the entry from the hdict.
entry hdict_remove(hdict *H, key k); // O(1) average & amortized.

// Prints the elements and other details of the hdict.
void hdict_print(hdict *H); // O(n)

#endif /* HASH_DICTIONARY_H */
