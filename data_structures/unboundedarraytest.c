#include <assert.h>
#include <limits.h>
#include <stdio.h>

#include "UnboundedArray.h"

// Helper function for adding ints to uba
void uba_add_int(uba_t A, int x) {
    int *ptr = malloc(sizeof(int));
    *ptr = x;
    uba_add(A, (ItemType)ptr);
}

// Helper function for removing ints from uba
int uba_rem_int(uba_t A) {
    int *ptr = (int *)uba_rem(A);
    int x = *ptr;
    free(ptr);
    return x;
}

// Helper function for getting item at index from uba
int uba_get_int(uba_t A, int i) {
    return *(int *)uba_get(A, i);
}

// Helper function for setting item at index from uba
void uba_set_int(uba_t A, int i, int x) {
    free(uba_get(A, i));
    int *ptr = malloc(sizeof(int));
    *ptr = x;
    uba_set(A, i, (ItemType)ptr);
}

int main() {
    uba_t A = uba_new(0);
    assert(uba_len(A) == 0);

    uba_add_int(A, 1);
    assert(uba_len(A) == 1);
    assert(uba_get_int(A, 0) == 1);

    uba_add_int(A, 3);
    assert(uba_len(A) == 2);
    assert(uba_get_int(A, 0) == 1 && uba_get_int(A, 1) == 3);

    uba_set_int(A, 1, 4);
    assert(uba_len(A) == 2);
    assert(uba_get_int(A, 0) == 1 && uba_get_int(A, 1) == 4);

    int x = uba_rem_int(A);
    assert(uba_len(A) == 1);
    assert(uba_get_int(A, 0) == 1);
    assert(x == 4);

    uba_set_int(A, 0, 10);
    assert(uba_len(A) == 1);
    assert(uba_get_int(A, 0) == 10);

    x = uba_rem_int(A);
    assert(uba_len(A) == 0);
    assert(x == 10);

    uba_free(A);

    uba_t B = uba_new(0);
    int num_iters = 1000000;
    for (int i = 0; i < num_iters; i++) {
        uba_add_int(B, i * 2);
        assert(uba_get_int(B, i) == i * 2);
        assert(uba_len(B) == i + 1);
    }

    for (int i = 0; i < num_iters; i++) {
        uba_set_int(B, i, i * 3);
        assert(uba_get_int(B, i) == i * 3);
    }

    for (int i = 0; i < num_iters; i++) {
        int rem = uba_rem_int(B);
        assert(rem == (num_iters - i - 1) * 3);
        assert(uba_len(B) == (num_iters - i - 1));
    }
    uba_free(B);

    printf("Testing complete. No bugs found.\n");
}
