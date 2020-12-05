#include <assert.h>
#include <stdio.h>

#include "PriorityQueue.h"

/******* Client-Defined Types and Operations *******/
// true if e1 < e2, false otherwise
// (We are saying lower numbers have higher priority)
bool has_higher_priority_int(elem e1, elem e2) {
    int int1 = *(int *)e1;
    int int2 = *(int *)e2;
    return int1 < int2;
}

// Function to delete a queue element.
void elem_free_int(elem x) {
    int *to_delete = (int *)x;
    free(to_delete);
}
/******* End Client-Defined Types and Operations *******/

// Helper function for adding ints into pq
void pq_add_int(pq_t Q, int x) {
    int *ptr = malloc(sizeof(int));
    *ptr = x;
    pq_add(Q, (elem)ptr);
}

// Helper function for removing ints from pq
int pq_rem_int(pq_t Q) {
    int *ptr = (int *)pq_rem(Q);
    int x = *ptr;
    free(ptr);
    return x;
}

// Helper function for peeking ints from pq
int pq_peek_int(pq_t Q) {
    return *(int *)pq_peek(Q);
}

int main() {
    pq_t q = pq_new(10000, has_higher_priority_int);
    assert(pq_empty(q));

    pq_add_int(q, 5);
    assert(pq_peek_int(q) == 5);
    assert(!pq_empty(q));
    pq_add_int(q, 2);
    assert(pq_peek_int(q) == 2);
    assert(!pq_empty(q));
    pq_add_int(q, 3);
    assert(pq_peek_int(q) == 2);
    assert(!pq_empty(q));

    int x = pq_rem_int(q);
    assert(x == 2);
    assert(pq_peek_int(q) == 3);
    assert(!pq_empty(q));

    pq_add_int(q, 6);
    assert(pq_peek_int(q) == 3);
    assert(!pq_empty(q));

    x = pq_rem_int(q);
    assert(x == 3);
    assert(pq_peek_int(q) == 5);
    assert(!pq_empty(q));

    x = pq_rem_int(q);
    assert(x == 5);
    assert(pq_peek_int(q) == 6);
    assert(!pq_empty(q));

    x = pq_rem_int(q);
    assert(x == 6);
    assert(pq_empty(q));

    pq_free(q, &elem_free_int);

    printf("Testing complete. No bugs found.\n");
}
