/* Priority Queue Implementation
 *
 * Priority Queue implementation using heap.
 * Heap is implemented using an underlying array, where the zero index is
 * ignored and the elements are stored starting from index 1.
 */

/*****************************************************************************
 * If DEBUG is defined, these macros are enabled. Used to check contracts    *
 * in debug mode                                                             *
 ****************************************************************************/
#ifdef DEBUG
/* When DEBUG is defined, these form aliases to useful functions */
#define dbg_printf(...) printf(__VA_ARGS__)
#define dbg_requires(expr) assert(expr)
#define dbg_assert(expr) assert(expr)
#define dbg_ensures(expr) assert(expr)
#else
/* When DEBUG is not defined, no code gets generated for these */
/* The sizeof() hack is used to avoid "unused variable" warnings */
#define dbg_printf(...) (sizeof(__VA_ARGS__), -1)
#define dbg_requires(expr) (sizeof(expr), 1)
#define dbg_assert(expr) (sizeof(expr), 1)
#define dbg_ensures(expr) (sizeof(expr), 1)
#endif

#include <assert.h>
#include <limits.h>

#include "PriorityQueue.h"

/* @brief Checks that the heap operations are safe to perform.
 *
 * @param[in] H: The heap.
 * @return true if all heap operations on H are safe.
 */
bool is_heap_safe(heap *H) {
    // Note that H->limit <= INT_MAX/2 to prevent overflow when accessing child
    return H != NULL && H->limit > 1 && H->limit <= INT_MAX / 2 &&
           H->next >= 1 && H->next <= H->limit && H->prio != NULL;
}

/* @brief Checks if the parent and child ordering is valid.
 *
 * @pre: 1 <= parent && parent < H->next (parent in bounds)
 * @pre: 1 <= child && child < H->next (child in bounds)
 * @param[in] H: The heap.
 * @param[in] parent: The position of the parent node.
 * @param[in] child: The position of the child node.
 * @return true if the parent-child ordering doesn't violate ordering invariant.
 */
bool ok_above(heap *H, int parent, int child) {
    dbg_requires(1 <= parent && parent < H->next);
    dbg_requires(1 <= child && child < H->next);

    elem parent_elem = H->data[parent];
    elem child_elem = H->data[child];

    // valid if child elem doesn't have greater priority than parent elem
    return !(*H->prio)(child_elem, parent_elem);
}

/* @brief Checks heap ordering invariant (for all nodes).
 *
 * @pre: is_heap_safe(H)
 * @param[in] H: The heap.
 * @return true if heap ordering invariant is valid.
 */
bool is_heap_ordered(heap *H) {
    for (int child = 2; child < H->next; child++) {
        dbg_assert(2 <= child && child <= H->next); // Loop Invariant
        int parent = child / 2;
        if (!ok_above(H, parent, child)) {
            return false;
        }
    }
    return true;
}

/* @brief Checks if the heap is valid (data structure invariant).
 *
 * @param[in] H: The heap.
 * @return: true if valid heap, false otherwise.
 */
bool is_heap(heap *H) {
    // Note that the shape invariant of the heap is true automatically by
    // the fact that we are implementing the heap using partially-filled arrays.
    return is_heap_safe(H) && is_heap_ordered(H);
}

/* @brief Checks if pq is empty.
 *
 * @pre: is_heap(H)
 * @post: is_heap(H)
 * @param[in] H: The pq.
 * @return true if empty, false otherwise.
 */
bool pq_empty(heap *H) {
    dbg_requires(is_heap(H));
    return H->next == 1;
}

/* @brief Checks if the pq is full.
 *
 * @pre: is_heap(H)
 * @post: is_heap(H)
 * @param[in] H: The pq.
 * @return true if full, false otherwise.
 */
bool pq_full(heap *H) {
    dbg_requires(is_heap(H));
    return H->next == H->limit;
}

/* @brief Create new pq.
 *
 * @pre: 0 < capacity && capacity <= INT_MAX / 2 - 1
 * @pre: prio != NULL
 * @post: is_heap(result)
 * @post: pq_empty(result)
 * @return: The initialized pq.
 */
heap *pq_new(int capacity, has_higher_priority_fn *prio) {
    dbg_requires(0 < capacity && capacity <= INT_MAX / 2 - 1);
    dbg_requires(prio != NULL);

    heap *H = malloc(sizeof(heap));
    H->limit = capacity + 1;
    H->next = 1;
    H->data = calloc(H->limit, sizeof(elem));
    H->prio = prio;

    dbg_ensures(is_heap(H));
    dbg_ensures(pq_empty(H));
    return H;
}

/* @brief Destroy an existing pq
 *
 * @pre: is_heap(H)
 * @post: !is_heap(H)
 * @param[in] H: The pq.
 */
void pq_free(heap *H, elem_free_fn *Fr) {
    dbg_requires(is_heap(H));

    // Delete all elems in heap
    for (int node = 1; node < H->next; node++) {
        if (Fr != NULL) {
            (*Fr)(H->data[node]);
        }
    }
    free(H->data);
    free(H);
}

/* @brief Swap two the parent and child position
 *
 * @pre: is_heap_safe(H)
 * @pre: 2 <= child && child < H->next (child in bounds)
 * @pre: !ok_above(H, child/2, child)
 * @post: ok_above(H, child/2, child)
 */
void swap_up(heap *H, int child) {
    int parent = child / 2;
    dbg_requires(is_heap_safe(H));
    dbg_requires(2 <= child && child < H->next);
    dbg_requires(!ok_above(H, parent, child));

    elem tmp = H->data[parent];
    H->data[parent] = H->data[child];
    H->data[child] = tmp;

    dbg_ensures(ok_above(H, parent, child));
}

/* @brief Weaker loop invariant to ensure correctness of sifting child up
 *        during insertions.
 *
 * @pre: is_heap_safe(H)
 * @pre: 1 <= except && except < H->next
 * @param[in] H: The pq.
 * @param[in] except: The node that is allowed an ordering violation exception
 * (child node perspective).
 * @return true if heap is ordered with possible exception at except, false
 * otherwise.
 */
bool is_heap_except_up(heap *H, int except) {
    dbg_requires(is_heap_safe(H));
    dbg_requires(1 <= except && except < H->next);
    for (int child = 2; child < H->next; child++) {
        int parent = child / 2;
        if (child != except && !ok_above(H, parent, child)) {
            return false;
        }
    }
    return true;
}

bool grandparent_check(heap *H, int i) {
    dbg_assert(is_heap_safe(H));

    if (i == 1) {
        // i is root - no grandparent check needed
        return true;
    }

    int grandchild_left = i * 2;
    int grandchild_right = i * 2 + 1;
    int grandparent = i / 2;

    if (grandchild_left >= H->next) {
        // No grandchildren to cause violations after swap
        return true;
    } else if (grandchild_right == H->next) {
        // Only left grandchild exists
        return ok_above(H, grandparent, grandchild_left);
    } else {
        return grandchild_right < H->next &&
               ok_above(H, grandparent, grandchild_left) &&
               ok_above(H, grandparent, grandchild_right);
    }
}

/* @brief Add elem to pq.
 *
 * @pre: is_heap(H) && !pq_full(H)
 * @post: is_heap(H) && !pq_empty(H)
 * @param[in] H: The pq.
 * @param[in] x: The item being inserted.
 */
void pq_add(heap *H, elem x) {
    assert(is_heap(H) && !pq_full(H));

    // Insert into last position (preserve shape invariant)
    H->data[H->next] = x;
    H->next++;
    dbg_assert(is_heap_safe(H));

    // Restore any ordering violations
    int child = H->next - 1;
    while (child > 1) {
        dbg_assert(child >= 1 && child < H->next); // Loop Invariant
        // The loop invariant below helps to prove the postcondition is_heap(H)
        dbg_assert(is_heap_except_up(H, child)); // Loop Invariant
        // Needed to prove above loop invariant (is_heap_except_up)
        dbg_assert(grandparent_check(H, child)); // Loop Invariant

        int parent = child / 2;
        if (ok_above(H, parent, child)) {
            dbg_ensures(is_heap(H) && !pq_empty(H));
            return; // No more ordering violations
        }
        swap_up(H, child);
        child = parent;
    }

    dbg_ensures(is_heap(H) && !pq_empty(H));
}

/* @brief Helper to determine valid to sift element down.
 *
 * @pre: is_heap_safe(H)
 * @pre: 1 <= except && except < H->next (parent in bounds)
 * @param[in] H: The pq.
 * @param[in] parent: The parent node.
 * @return true if heap satisfies ordering invariant except at parent.
 */
bool is_heap_except_down(heap *H, int except) {
    dbg_requires(is_heap_safe(H));
    dbg_requires(1 <= except && except < H->next);

    for (int child = 2; child < H->next; child++) {
        int parent = child / 2;
        if (parent != except && !ok_above(H, parent, child)) {
            return false;
        }
    }
    return true;
}

/* @brief Sifts element at root down until ordering invariant is satisfied
 *        or a leaf is reached.
 *
 * @pre: is_heap_safe(H)
 * @pre: H->next > 1 && is_heap_except_down(H, 1);
 * @post: is_heap(H)
 */
void sift_down(heap *H) {
    dbg_requires(is_heap_safe(H));
    dbg_requires(H->next > 1 && is_heap_except_down(H, 1));

    int parent = 1;
    while (2 * parent < H->next) {
        dbg_assert(1 <= parent && parent < H->next); // Loop Invariant
        dbg_assert(is_heap_except_down(H, parent));  // Loop Invariant
        dbg_assert(grandparent_check(H, parent));    // Loop Invariant

        int left = parent * 2;
        int right = parent * 2 + 1;
        if (right < H->next) {
            // consider both left and right children
            if (ok_above(H, parent, left) && ok_above(H, parent, right)) {
                // No more violations
                dbg_ensures(is_heap(H));
                return;
            }

            int to_swap = ok_above(H, left, right) ? left : right;
            swap_up(H, to_swap);
            parent = to_swap;
        } else {
            // can consider only has left child
            if (ok_above(H, parent, left)) {
                // No more violations
                dbg_ensures(is_heap(H));
                return;
            }

            swap_up(H, left);
            parent = left;
        }
    }
    // Parent at last level
    dbg_assert(parent < H->next && 2 * parent >= H->next);

    dbg_ensures(is_heap(H));
}

/* @brief Remove highest priority element from pq.
 *
 * @pre: is_heap(H) && !pq_empty(H)
 * @post: is_heap(H) && !pq_full(H)
 * @param[in] H: The pq
 * @return: The item being removed.
 */
elem pq_rem(heap *H) {
    dbg_requires(is_heap(H) && !pq_empty(H));

    elem ret = H->data[1];
    H->next--;

    if (H->next > 1) {
        // Replace last element to root
        H->data[1] = H->data[H->next];
        sift_down(H);
    }
    return ret;

    dbg_ensures(is_heap(H) && !pq_full(H));
}

/* @brief Get highest priority elem in pq without removing.
 *
 * @pre: is_heap(H) && !pq_empty(H)
 * @post: is_heap(H) && !pq_empty(H)
 * @param[in] H: The pq
 * @return: The highest priority item.
 */
elem pq_peek(heap *H) {
    assert(is_heap(H));
    return H->data[1];
}
