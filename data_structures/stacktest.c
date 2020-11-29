#include <assert.h>
#include <limits.h>
#include <stdio.h>

#include "Stack.h"

enum SortOrder { ASCENDING = true, DESCENDING = false };

/******* Client-Defined Types and Operations *******/
// Function to delete a queue element.
void elem_free_int(elem x) {
    int *to_delete = (int *)x;
    free(to_delete);
}
/******* End Client-Defined Types and Operations *******/

/********** Exercises (15-122 Notes) **********/
// Returns true if stack sorted in order specified by parameter.
bool is_stack_sorted(stack_t S, bool sort_ascending) {
    stack_t tmp = stack_new();
    bool is_sorted = true;
    int prev_item = sort_ascending ? INT_MAX : INT_MIN;
    while (is_sorted && !stack_empty(S)) {
        elem item = pop(S);
        is_sorted = sort_ascending ? (*(int *)item < prev_item)
                                   : (*(int *)item > prev_item);
        push(tmp, item);
        prev_item = *(int *)item;
    }
    while (!stack_empty(tmp)) {
        push(S, pop(tmp));
    }
    stack_free(tmp, &elem_free_int);
    return is_sorted;
}

// Returns the size of the stack
int stack_size(stack_t S) {
    if (stack_empty(S))
        return 0;
    elem item = pop(S);
    int size = 1 + stack_size(S);
    push(S, item);
    return size;
}

// Sorts the items in the stack in ASCENDING order.
void stack_sort(stack_t S) {
    if (stack_empty(S))
        return;

    // Second stack to hold elements that come from S
    stack_t reversed = stack_new();
    // Third stack to temporary hold elements that come from reversed
    stack_t tmp = stack_new();

    // Insertion sort variant
    while (!stack_empty(S)) {
        assert(is_stack_sorted(reversed, DESCENDING)); // Loop invariant
        elem item = pop(S);
        while (!stack_empty(reversed) &&
               *(int *)peek(reversed) < *(int *)item) {
            assert(is_stack_sorted(tmp, ASCENDING)); // Loop Invariant
            push(tmp, pop(reversed));
        }
        push(reversed, item); // Add item in appropriate position in reversed
        while (!stack_empty(tmp)) {
            push(reversed, pop(tmp));
        }
    }
    assert(stack_empty(S));

    // Push reversed contents back to S
    while (!stack_empty(reversed)) {
        assert(is_stack_sorted(S, ASCENDING)); // Loop Invariant
        push(S, pop(reversed));
    }

    stack_free(reversed, &elem_free_int);
    stack_free(tmp, &elem_free_int);
}

// Helper function for pushing ints onto stack
void push_int(stack_t S, int x) {
    int *ptr = malloc(sizeof(int));
    *ptr = x;
    push(S, (elem)ptr);
}

// Helper function for popping ints from stack
int pop_int(stack_t S) {
    int *ptr = (int *)pop(S);
    int x = *ptr;
    free(ptr);
    return x;
}

// Helper function for peeking ints from stack
int peek_int(stack_t S) {
    return *(int *)peek(S);
}

void test_stack_sort() {
    stack_t st = stack_new();
    push_int(st, 5);
    push_int(st, 2);
    push_int(st, 4);
    push_int(st, 1);

    assert(!is_stack_sorted(st, ASCENDING) && !is_stack_sorted(st, DESCENDING));

    stack_sort(st);
    assert(is_stack_sorted(st, ASCENDING));

    assert(pop_int(st) == 5);
    assert(pop_int(st) == 4);
    assert(pop_int(st) == 2);
    assert(pop_int(st) == 1);
    assert(stack_empty(st));

    stack_free(st, &elem_free_int);
}

int main() {
    stack_t st = stack_new();
    assert(stack_empty(st));

    push_int(st, 5);
    assert(peek_int(st) == 5);
    assert(!stack_empty(st));
    push_int(st, 2);
    assert(peek_int(st) == 2);
    assert(!stack_empty(st));
    push_int(st, 3);
    assert(peek_int(st) == 3);
    assert(!stack_empty(st));
    assert(stack_size(st) == 3);

    int x = pop_int(st);
    assert(x == 3);
    assert(peek_int(st) == 2);
    assert(!stack_empty(st));

    push_int(st, 6);
    assert(peek_int(st) == 6);
    assert(!stack_empty(st));
    assert(stack_size(st) == 3);

    x = pop_int(st);
    assert(x == 6);
    assert(peek_int(st) == 2);
    assert(!stack_empty(st));

    x = pop_int(st);
    assert(x == 2);
    assert(peek_int(st) == 5);
    assert(!stack_empty(st));

    x = pop_int(st);
    assert(x == 5);
    assert(stack_empty(st));

    stack_free(st, &elem_free_int);

    test_stack_sort();

    printf("Testing complete. No bugs found.\n");
}
