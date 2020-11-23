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

    int x = uba_rem(A);
    assert(uba_len(A) == 1);
    assert(uba_get(A, 0) == 1);
    assert(x == 4);

    uba_set(A, 0, 10);
    assert(uba_len(A) == 1);
    assert(uba_get(A, 0) == 10);

    x = uba_rem(A);
    assert(uba_len(A) == 0);
    assert(x == 10);

    uba_delete(A);

    uba_t B = uba_new(0);
    int num_iters = 1000000;
    for (int i = 0; i < num_iters; i++) {
        uba_add(B, i * 2);
        assert(uba_get(B, i) == i * 2);
        assert(uba_len(B) == i + 1);
    }

    for (int i = 0; i < num_iters; i++) {
        uba_set(B, i, i * 3);
        assert(uba_get(B, i) == i * 3);
    }

    for (int i = 0; i < num_iters; i++) {
        int rem = uba_rem(B);
        assert(rem == (num_iters - i - 1) * 3);
        assert(uba_len(B) == (num_iters - i - 1));
    }

    printf("Testing complete. No bugs found.\n");
}
