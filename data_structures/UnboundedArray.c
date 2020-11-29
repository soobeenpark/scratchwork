/* Unbounded Array Implementation
 *
 * The underlying array doubles in size whenever resizing is necessary.
 * This makes the amortized complexity of adding and removing elements O(1)
 * (but still O(n) worst case time complexity).
 */

#include <assert.h>
#include <limits.h>

#include "UnboundedArray.h"

/* @brief Checks if the uba is valid (data structure invariant).
 *
 * @param[in] A: The uba
 * @return: true if valid uba, false otherwise.
 */
bool is_uba(uba *A) {
    // A->size >= A->limit/4 is there to make sure uba_rem has O(1) amortized
    // cost to remove elements.
    // Tokens must be stored in the second quarter of the array when removing,
    // otherwise each operation is O(n) amortized, not O(1).
    return A != NULL && A->data != NULL && A->limit > 0 &&
           A->size >= A->limit / 4 && A->size < A->limit;
}

/* Get length of the array in use.
 *
 * @pre: is_uba(A)
 * @post: result >= 0 && result < length(A->data)
 * @param[in] A: The uba
 * @return: The size actively being used in the underlying array.
 */
int uba_len(uba *A) {
    assert(is_uba(A));
    assert(A->size >= 0 && A->size < A->limit);
    return A->size;
}

/* Create new unbounded array.
 *
 * @pre: 0 <= size
 * @post: is_uba(result)
 * @post: uba_len(result) == size
 * @return: The initialized uba.
 */
uba_t uba_new(int size) {
    assert(size >= 0);

    uba *A = malloc(sizeof(uba));
    int limit = (size == 0) ? 1 : size * 2;
    A->data = calloc(limit, sizeof(elem));
    A->size = size;
    A->limit = limit;

    assert(is_uba(A));
    return A;
}

/* Destroy an existing unbounded array.
 *
 * @pre: is_uba(A)
 * @post: !is_uba(A)
 * @param[in] A: The uba.
 */
void uba_free(uba *A, elem_free_fn *Fr) {
    assert(is_uba(A));
    if (Fr != NULL)
        (*Fr)(A->data);
    free(A);
}

/* Get an element at index i.
 *
 * @pre: is_uba(A)
 * @pre: i >= 0 && i < uba_len(A)
 * @post: is_uba(A)
 * @param[in] A: The uba.
 * @param[in] i: The index to the array.
 * @return: The element at index i
 */
elem uba_get(uba *A, int i) {
    assert(is_uba(A));
    assert(i >= 0 && i < uba_len(A));

    return A->data[i];
}

/* Set an element at index i with new data.
 *
 * @pre: is_uba(A)
 * @pre: i >= 0 && i < uba_len(A)
 * @post: is_uba(A)
 * @param[in] A: The uba.
 * @param[in] i: The index to the array.
 * @param[in] x: The element to insert at index i
 */
void uba_set(uba *A, int i, elem x) {
    assert(is_uba(A));
    assert(i >= 0 && i < uba_len(A));

    A->data[i] = x;
    assert(is_uba(A));
}

/* Resize the underlying array.
 *
 * @pre: A != NULL  (is_uba(A) would be incorrect b/c size == limit may be true)
 * @pre: 0 <= A->size && A->size < new_limit
 * @post: is_uba(A)   (Restores data structure invariant)
 */
void uba_resize(uba *A, int new_limit) {
    assert(A != NULL);
    assert(0 <= A->size && A->size < new_limit);

    elem *B = malloc(sizeof(elem) * new_limit);

    // Copy items over
    for (int i = 0; i < A->size; i++) {
        assert(i < new_limit);
        assert(0 <= i && i <= A->size); // Loop invariant
        B[i] = A->data[i];
    }
    free(A->data);
    A->limit = new_limit;
    A->data = B;

    assert(is_uba(A));
}

/* Append an element to the end of the array.
 *
 * @pre: is_uba(A)
 * @post: is_uba(A)
 * @post: uba_len(A) > 0
 * @param[in] A: The uba.
 * @param[in] x: The element to append to the end.
 */
void uba_add(uba *A, elem x) {
    assert(is_uba(A));

    A->data[A->size++] = x;

    if (A->size == A->limit) {
        // Need to resize
        assert(A->limit <= INT_MAX / 2); // fail if overflow
        uba_resize(A, A->limit * 2);     // Resize to twice the length
    }

    assert(is_uba(A));
    assert(uba_len(A) > 0);
}

/* Remove the last element from the array.
 *
 * @pre: is_uba(A)
 * @pre: uba_len(A) > 0
 * @post: is_uba(A)
 * @param[in] A: The uba.
 */
elem uba_rem(uba *A) {
    assert(is_uba(A));
    assert(uba_len(A) > 0);

    elem ret = A->data[--A->size];
    if (A->size < A->limit / 4) {
        // Need to resize
        uba_resize(A, A->limit / 4); // Resize when quarter for amortized O(1)
    }
    assert(is_uba(A));
    return ret;
}
