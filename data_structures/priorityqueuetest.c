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
    int capacity = 10000;
    pq_t q = pq_new(capacity, has_higher_priority_int);
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

    // STRESS TEST
    // run heapsort on mixed even -> odd array
    printf("Running stress test\n");
    q = pq_new(capacity, has_higher_priority_int);
    printf("Inserting");
    for (int i = 0; i < capacity; i += 2) {
        if (i % 1000 == 0) {
            printf(".");
            fflush(stdout);
        }
        pq_add_int(q, i);
    }
    for (int i = 1; i < capacity; i += 2) {
        if (i % 1000 == 1) {
            printf(".");
            fflush(stdout);
        }
        pq_add_int(q, i);
    }
    assert(pq_full(q));

    printf("\nRemoving");
    int arr[capacity];
    for (int i = 0; i < capacity; i++) {
        if (i % 500 == 0) {
            printf(".");
            fflush(stdout);
        }
        // heapsort
        arr[i] = pq_rem_int(q);
    }
    assert(pq_empty(q));
    for (int i = 1; i < capacity; i++) {
        // check if sorted
        assert(arr[i - 1] < arr[i]);
        assert(arr[i] == i);
    }
    printf("\n");

    printf("Testing complete. No bugs found.\n");
}
