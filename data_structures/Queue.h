/* Queue Interface */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdlib.h>

#include "LinkedList.h"

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
void queue_delete(queue_t Q); // O(1)

// Enqueue element to back of queue.
void enq(queue_t Q, ItemType x); // O(1)

// Dequeue from front of queue.
ItemType deq(queue_t Q); // O(1)

// Get front element of queue without dequeing.
ItemType peek(queue_t Q); // O(1)

#endif /* QUEUE_H */
