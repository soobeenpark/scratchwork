#include <assert.h>
#include <stdio.h>

#include "Queue.h"

int main() {
    queue_t q = queue_new();
    assert(queue_empty(q));

    enq(q, 5);
    assert(peek(q) == 5);
    assert(!queue_empty(q));
    enq(q, 2);
    assert(peek(q) == 5);
    assert(!queue_empty(q));
    enq(q, 3);
    assert(peek(q) == 5);
    assert(!queue_empty(q));

    int x = deq(q);
    assert(x == 5);
    assert(peek(q) == 2);
    assert(!queue_empty(q));

    enq(q, 6);
    assert(peek(q) == 2);
    assert(!queue_empty(q));

    x = deq(q);
    assert(x == 2);
    assert(peek(q) == 3);
    assert(!queue_empty(q));

    x = deq(q);
    assert(x == 3);
    assert(peek(q) == 6);
    assert(!queue_empty(q));

    x = deq(q);
    assert(x == 6);
    assert(queue_empty(q));

    queue_free(q);

    printf("Testing complete. No bugs found.\n");
}
