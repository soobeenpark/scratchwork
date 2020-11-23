#include <assert.h>
#include <limits.h>
#include <stdio.h>

#include "UnboundedArray.h"

int main() {
    uba_t A = uba_new(0);
    assert(uba_len(A) == 0);

    uba_add(A, 1);
    assert(uba_len(A) == 1);
    assert(uba_get(A, 0) == 1);

    uba_add(A, 3);
    assert(uba_len(A) == 2);
    assert(uba_get(A, 0) == 1 && uba_get(A, 1) == 3);

    uba_set(A, 1, 4);
    assert(uba_len(A) == 2);
    assert(uba_get(A, 0) == 1 && uba_get(A, 1) == 4);

    uba_rem(A);
    assert(uba_len(A) == 1);
    assert(uba_get(A, 0) == 1);

    uba_set(A, 0, 10);
    assert(uba_len(A) == 1);
    assert(uba_get(A, 0) == 10);

    uba_rem(A);
    assert(uba_len(A) == 0);

    uba_delete(A);

    printf("Testing complete. No bugs found.\n");
}
