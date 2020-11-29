#include <assert.h>
#include <stdio.h>

#include "Queue.h"

// Helper function for enqueing ints onto queue
void enq_int(queue_t Q, int x) {
    int *ptr = malloc(sizeof(int));
    *ptr = x;
    enq(Q, (ItemType)ptr);
}

// Helper function for dequeing ints from queue
int deq_int(queue_t Q) {
    int *ptr = (int *)deq(Q);
    int x = *ptr;
    free(ptr);
    return x;
}

// Helper function for peeking ints from queue
int peek_int(queue_t Q) {
    return *(int *)peek(Q);
}

int main() {
    queue_t q = queue_new();
    assert(queue_empty(q));

    enq_int(q, 5);
    assert(peek_int(q) == 5);
    assert(!queue_empty(q));
    enq_int(q, 2);
    assert(peek_int(q) == 5);
    assert(!queue_empty(q));
    enq_int(q, 3);
    assert(peek_int(q) == 5);
    assert(!queue_empty(q));

    int x = deq_int(q);
    assert(x == 5);
    assert(peek_int(q) == 2);
    assert(!queue_empty(q));

    enq_int(q, 6);
    assert(peek_int(q) == 2);
    assert(!queue_empty(q));

    x = deq_int(q);
    assert(x == 2);
    assert(peek_int(q) == 3);
    assert(!queue_empty(q));

    x = deq_int(q);
    assert(x == 3);
    assert(peek_int(q) == 6);
    assert(!queue_empty(q));

    x = deq_int(q);
    assert(x == 6);
    assert(queue_empty(q));

    queue_free(q);

    printf("Testing complete. No bugs found.\n");
}
