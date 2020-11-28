#include <assert.h>
#include <limits.h>
#include <stdio.h>

#include "Stack.h"

enum SortOrder { ASCENDING = true, DESCENDING = false };

/********** Exercises (15-122 Notes) **********/
// Returns true if stack sorted in order specified by parameter.
bool is_stack_sorted(stack_t S, bool sort_ascending) {
    stack_t tmp = stack_new();
    bool is_sorted = true;
    ItemType prev_item = sort_ascending ? INT_MAX : INT_MIN;
    while (is_sorted && !stack_empty(S)) {
        int item = pop(S);
        is_sorted = sort_ascending ? (item < prev_item) : (item > prev_item);
        push(tmp, item);
        prev_item = item;
    }
    while (!stack_empty(tmp)) {
        push(S, pop(tmp));
    }
    stack_free(tmp);
    return is_sorted;
}

// Returns the size of the stack
int stack_size(stack_t S) {
    if (stack_empty(S))
        return 0;
    int item = pop(S);
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
        int item = pop(S);
        while (!stack_empty(reversed) && peek(reversed) < item) {
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

    stack_free(reversed);
    stack_free(tmp);
}

void test_stack_sort() {
    stack_t st = stack_new();
    push(st, 5);
    push(st, 2);
    push(st, 4);
    push(st, 1);
    assert(!is_stack_sorted(st, ASCENDING) && !is_stack_sorted(st, DESCENDING));

    stack_sort(st);
    assert(is_stack_sorted(st, ASCENDING));
    assert(pop(st) == 5);
    assert(pop(st) == 4);
    assert(pop(st) == 2);
    assert(pop(st) == 1);
    assert(stack_empty(st));

    stack_free(st);
}

int main() {
    stack_t st = stack_new();
    assert(stack_empty(st));

    push(st, 5);
    assert(peek(st) == 5);
    assert(!stack_empty(st));
    push(st, 2);
    assert(peek(st) == 2);
    assert(!stack_empty(st));
    push(st, 3);
    assert(peek(st) == 3);
    assert(!stack_empty(st));
    assert(stack_size(st) == 3);

    int x = pop(st);
    assert(x == 3);
    assert(peek(st) == 2);
    assert(!stack_empty(st));

    push(st, 6);
    assert(peek(st) == 6);
    assert(!stack_empty(st));
    assert(stack_size(st) == 3);

    x = pop(st);
    assert(x == 6);
    assert(peek(st) == 2);
    assert(!stack_empty(st));

    x = pop(st);
    assert(x == 2);
    assert(peek(st) == 5);
    assert(!stack_empty(st));

    x = pop(st);
    assert(x == 5);
    assert(stack_empty(st));

    stack_free(st);

    test_stack_sort();

    printf("Testing complete. No bugs found.\n");
}
