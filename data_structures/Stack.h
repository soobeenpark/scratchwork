/* Stack Interface */

#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdlib.h>

#include "LinkedList.h"

/******* Client-defined Interface *******/
// Function to delete the entry.
typedef void elem_free_fn(elem x);

/******* Library Interface *******/
typedef struct stack_header stack;
struct stack_header {
    list *top;
};

// Client side type
typedef stack *stack_t;

// Checks if the stack is empty.
bool stack_empty(stack_t S); // O(1)

// Create new stack.
stack_t stack_new(); // O(1)

// Destroy an existing stack.
void stack_free(stack_t S, elem_free_fn *Fr); // O(1)

// Enqueue element to back of stack.
void push(stack_t S, elem x); // O(1)

// Dequeue from front of stack.
elem pop(stack_t S); // O(1)

// Get top element of stack without popping.
elem peek(stack_t S); // O(1)

#endif /* STACK_H */
