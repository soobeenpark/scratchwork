/* Priority Queue Interface
 *
 * This priority queue will be bounded (has maximum capacity).
 */

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdbool.h>
#include <stdlib.h>

/******* Client-defined Interface *******/
// Element type
typedef void *elem;

// Returns true if e1 has higher priority than e2, false otherwise.
typedef bool has_higher_priority_fn(elem e1, elem e2);

// Function to delete the elem.
typedef void elem_free_fn(elem x);

/******* Library Interface *******/
// Client side type
typedef int *pq_t;

// Checks if the pq is empty.
bool pq_empty(pq_t Q); // O(1)

// Checks if the pq is full.
bool pq_full(pq_t Q); // O(1)

// Create new pq.
pq_t pq_new(int capacity, has_higher_priority_fn *prio); // O(1)

// Destroy an existing pq.
void pq_free(pq_t Q, elem_free_fn *Fr); // O(1)

// Add elem to pq.
void pq_add(pq_t Q, elem e); // O(logn)

// Remove highest priority element from pq.
elem pq_rem(pq_t Q); // O(logn)

// Get highest priority element in pq without removing.
elem pq_peek(pq_t Q); // O(1)

#endif /* PRIORITY_QUEUE_H */
