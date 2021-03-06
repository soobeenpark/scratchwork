/* Unbounded Array Interface
 *
 * An unbounded array combines the O(1) access of arrays with the ability to
 * resize the container of linked lists.
 */

#ifndef UNBOUNDED_ARRAY_H
#define UNBOUNDED_ARRAY_H

#include <stdbool.h>
#include <stdlib.h>

/******* Client-defined Interface *******/
typedef void *elem;

// Function to delete the entry.
typedef void elem_free_fn(elem x);

/******* Library Interface *******/

typedef struct uba_header uba;
struct uba_header {
    int size;   // 0 <= size && size < limit
    int limit;  // 0 < limit
    elem *data; // length(data) == limit
};

// Client side type
typedef uba *uba_t;

// Get length of the array in use.
int uba_len(uba_t A); // O(1)

// Create new unbounded array.
uba_t uba_new(int size); // O(1)

// Destroy an existing unbounded array.
void uba_free(uba_t A, elem_free_fn *Fr); // O(1)

// Get an element at index i.
elem uba_get(uba_t A, int i); // O(1)

// Set an element at index i with new data.
void uba_set(uba_t A, int i, elem x); // O(1)

// Append an element to the end of the array.
void uba_add(uba_t A, elem x); // O(1) amortized

// Remove the last element from the array.
elem uba_rem(uba_t A); // O(1) amortized

#endif /* UNBOUNDED_ARRAY_H */
