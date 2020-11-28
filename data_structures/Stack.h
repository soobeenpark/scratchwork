/* Stack Interface */

#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdlib.h>

#include "LinkedList.h"

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
void stack_free(stack_t S); // O(1)

// Enqueue element to back of stack.
void push(stack_t S, ItemType x); // O(1)

// Dequeue from front of stack.
ItemType pop(stack_t S); // O(1)

// Get top element of stack without popping.
ItemType peek(stack_t S); // O(1)

#endif /* STACK_H */
