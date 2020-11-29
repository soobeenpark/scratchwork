/* Queue Interface */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdlib.h>

#include "LinkedList.h"

/******* Client-defined Interface *******/
// Function to delete the entry.
typedef void elem_free_fn(elem x);

/******* Library Interface *******/
typedef struct queue_header queue;
struct queue_header {
    list *front;
    list *back;
};

// Client side type
typedef queue *queue_t;

// Checks if the queue is empty.
bool queue_empty(queue_t Q); // O(1)

// Create new queue.
queue_t queue_new(); // O(1)

// Destroy an existing queue.
void queue_free(queue_t Q, elem_free_fn *Fr); // O(1)

// Enqueue element to back of queue.
void enq(queue_t Q, elem x); // O(1)

// Dequeue from front of queue.
elem deq(queue_t Q); // O(1)

// Get front element of queue without dequeing.
elem peek(queue_t Q); // O(1)

#endif /* QUEUE_H */
