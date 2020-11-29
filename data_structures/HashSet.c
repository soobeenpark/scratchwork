/* Hash Set Implementation
 *
 * O(1) average and amortized complexity.
 *
 * The set is implemented as a hash table, with separate chaining to
 * handle collisions.
 *
 * The underlying array doubles in size whenever resizing is necessary when
 * inserting. The array also halves in size whenever resizing is necessary when
 * deleting. This makes insertion and deletion O(1) average and amortized.
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

/* Library includes */
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "HashSet.h"

/* The maximum load factor (= size / capacity) that a single bucket will hold
 * on average before needing to resize the table to a bigger capacity when
 * inserting. ie. This is the
 * maximum average length of each chain in the bucket.
 *
 * Resizing only when this max load factor is reached ensures O(1) amortized
 * cost for insertions.
 */
const double MAX_LOAD_FACTOR = 4.0;

/* The minimum load factor a single bucket is allowed to hold when deleting.
 *
 * Note that this only minimum is only guaranteed when deleting, and so it is
 * not guaranteed that the load factor be at least this minimum when resizing
 * up, or at the beginning with an empty hset.
 *
 * Resizing only when this min load factor is reached ensures O(1) amortized
 * cost for deletions.
 */
const double MIN_LOAD_FACTOR = 0.7;

/******* Library Implementation *******/
/* Helper function to call H->equiv */
bool elem_equiv(hset *H, elem x, elem y) {
    return (*H->equiv)(x, y);
}

/* Helper function to call H->hash */
int elem_hash(hset *H, elem x) {
    return (*H->hash)(x);
}

/* Helper function to retrieve bucket index given the element.
 *
 * @pre: is_hset(H)
 * @post: 0 <= result && result < H->capacity
 */
int index_of_elem(hset *H, elem x) {
    return abs(elem_hash(H, x) % (H->capacity));
}

/* @brief Checks if the hset is valid (data structure invariant).
 *
 * @param[in] A: The hset.
 * @return: true if valid hset, false otherwise.
 */
bool is_hset(hset *H) {
    // Go through all elements
    int node_count = 0;
    for (int bucket_ind = 0; bucket_ind < H->capacity; bucket_ind++) {
        if (H->table[bucket_ind] != NULL) {
            chain *c = H->table[bucket_ind];
            while (c != NULL) {
                elem x = c->data;

                // Check each elem in chain node is not NULL
                if (x == NULL)
                    return false;

                // Check there are no duplicate elems
                // (Skip because computationally expensive)

                // Check that each elem in the bucket chain hashes
                // to this bucket index
                if (index_of_elem(H, x) != bucket_ind) {
                    return false;
                }

                // Count number of nodes
                node_count++;

                c = c->next;
            }
        }
    }

    return (H != NULL) && (H->size >= 0) && (H->capacity > 0) &&
           (node_count == H->size) && (H->hash != NULL) && (H->equiv != NULL);
}

/* Create new hash set.
 *
 * @pre: 0 < initial_capacity
 * @post: is_hset(result)
 * @return: The initialized hset.
 */
hset *hset_new(int initial_capacity, elem_equiv_fn *equiv, elem_hash_fn *hash) {
    dbg_requires(initial_capacity > 0);
    dbg_requires(hash != NULL && equiv != NULL);

    hset *H = malloc(sizeof(hset));
    H->size = 0;
    H->capacity = initial_capacity;
    H->table = calloc(initial_capacity, sizeof(chain *));

    // Set function pointers
    H->hash = hash;
    H->equiv = equiv;

    dbg_ensures(is_hset(H));
    return H;
}

/* Destroy an existing hash set.
 *
 * @pre: is_hset(H)
 * @post: !is_hset(H)
 * @param[in] H: The hset.
 */
void hset_free(hset *H, elem_free_fn *Fr) {
    dbg_requires(is_hset(H));

    // Free all nodes in each bucket
    for (int bucket_ind = 0; bucket_ind < H->capacity; bucket_ind++) {
        chain *iter = H->table[bucket_ind];
        while (iter != NULL) {
            chain *to_delete = iter;
            iter = iter->next;
            if (Fr != NULL) {
                (*Fr)(to_delete->data);
            }
            free(to_delete);
        }
    }
    free(H->table);
    free(H);
}

/* Resize the underlying array.
 *
 * O(n) operation.
 *
 * @pre: H != NULL  (is_hset(H) would be incorrect b/c load factor may be over)
 * @post: is_hset(H)   (Restores data structure invariant)
 */
void hset_resize(hset *H, int new_capacity) {
    dbg_requires(H != NULL);

    // Set new capacity
    int old_capacity = H->capacity;
    H->capacity = new_capacity;

    // Allocate new array
    chain **new_table = calloc(new_capacity, sizeof(chain *));

    // Rehash every node in old table and insert into new table
    for (int bucket_ind = 0; bucket_ind < old_capacity; bucket_ind++) {
        chain *iter = H->table[bucket_ind];
        while (iter != NULL) {
            elem x = iter->data;
            dbg_assert(x != NULL); // Valid element shouldn't be NULL

            int new_hash_ind = index_of_elem(H, x);

            // Reinsert node into new table
            chain *to_reinsert = iter;
            iter = iter->next;
            to_reinsert->next = new_table[new_hash_ind];
            new_table[new_hash_ind] = to_reinsert;
        }
    }

    // Free old table and replace it with new one
    free(H->table);
    H->table = new_table;
    dbg_ensures(is_hset(H));
}

/* Check if element exists in hash set.
 *
 * @pre: is_hset(H)
 * @post: is_hset(H)
 * @param[in] H: The hset.
 * @param[in] x: The elem to lookup.
 * @return true if elem found, false otherwise.
 */
bool hset_contains(hset_t H, elem x) {
    dbg_requires(is_hset(H));

    int ind = index_of_elem(H, x);
    // Iterate through chain looking for elem
    for (chain *iter = H->table[ind]; iter != NULL; iter = iter->next) {
        elem search = iter->data;
        assert(search != NULL);
        if (elem_equiv(H, search, x)) {
            dbg_ensures(is_hset(H));
            return true;
        }
    }

    dbg_ensures(is_hset(H));
    return false;
}

/* Insert an element into the hash set.
 *
 * @pre: is_hset(H)
 * @pre: x != NULL
 * @post: is_hset(H)
 * @post: hset_contains(H, x)
 * @post: H->size > 0
 * @param[in] H: The hset.
 * @param[in] x: The elem to insert.
 */
void hset_insert(hset_t H, elem x) {
    dbg_requires(is_hset(H));
    dbg_requires(x != NULL);

    int ind = index_of_elem(H, x);

    // Iterate through chain looking for elem
    for (chain *iter = H->table[ind]; iter != NULL; iter = iter->next) {
        elem old = iter->data;
        dbg_assert(old != NULL);
        if (elem_equiv(H, x, old)) {
            // Already in set
            return;
        }
    }

    // Create new elem into beginning of list
    chain *to_insert = malloc(sizeof(chain));
    to_insert->data = x;
    to_insert->next = H->table[ind];
    H->table[ind] = to_insert;

    H->size++;

    // Resize capacity as necessary
    if ((double)H->size / H->capacity >= MAX_LOAD_FACTOR) {
        hset_resize(H, 2 * (H->capacity)); // double the capacity
    }
    dbg_ensures(is_hset(H));
    dbg_ensures(hset_contains(H, x));
    dbg_ensures(H->size > 0);
}

/* Removes the element from the hset.
 *
 * Fails if there is no elem that matches.
 *
 * @pre: is_hset(H)
 * @pre: hset_contains(H, x)
 * @pre: H->size > 0
 * @post: is_hset(H)
 * @post: !hset_contains(H, x)
 * @post: result != NULL && elem_equiv(result, x)
 * @param[in] H: The hset.
 * @param[in] x: The elem to remove.
 * @return The elem removed from the hset.
 */
elem hset_remove(hset *H, elem x) {
    dbg_requires(is_hset(H));
    dbg_requires(hset_contains(H, x));
    dbg_requires(H->size > 0);

    int ind = index_of_elem(H, x);
    chain *curr = H->table[ind];
    chain *prev;
    while (curr != NULL) {
        if (elem_equiv(H, curr->data, x)) {
            elem to_remove = curr->data;

            // Remove chain node from table
            if (curr == H->table[ind]) {
                H->table[ind] = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            H->size--;

            // Resize capacity as necessary
            if ((double)H->size / H->capacity <= MIN_LOAD_FACTOR) {
                int new_capacity = H->capacity > 1 ? (H->capacity) / 2 : 1;
                hset_resize(H, new_capacity); // Halve the capacity
            }

            dbg_ensures(is_hset(H));
            dbg_ensures(!hset_contains(H, x));
            dbg_ensures(x != NULL && elem_equiv(H, to_remove, x));
            return to_remove;
        }

        prev = curr;
        curr = curr->next;
    }

    // Should not reach here
    return NULL;
}
