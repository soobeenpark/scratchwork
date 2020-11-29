/* Hash Dictionary Implementation
 *
 * O(1) average and amortized complexity.
 *
 * The dictionary is implemented as a hash table, with separate chaining to
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

#include "HashDictionary.h"

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
 * up, or at the beginning with an empty hdict.
 *
 * Resizing only when this min load factor is reached ensures O(1) amortized
 * cost for deletions.
 */
const double MIN_LOAD_FACTOR = 0.7;

/******* Library Implementation *******/
/* Helper function to call H->entry_key */
key entry_key(hdict *H, entry x) {
    return (*H->entry_key)(x);
}

/* Helper function to call H->hash */
bool key_equiv(hdict *H, key k1, key k2) {
    return (*H->equiv)(k1, k2);
}

/* Helper function to call H->hash */
int key_hash(hdict *H, key k) {
    return (*H->hash)(k);
}

/* Helper function to retrieve bucket index given the key.
 *
 * @pre: is_dict(H)
 * @post: 0 <= result && result < H->capacity
 */
int index_of_key(hdict *H, key k) {
    return abs(key_hash(H, k) % (H->capacity));
}

/* @brief Checks if the hdict is valid (data structure invariant).
 *
 * @param[in] A: The hdict
 * @return: true if valid hdict, false otherwise.
 */
bool is_hdict(hdict *H) {
    // Go through all entries
    int node_count = 0;
    for (int bucket_ind = 0; bucket_ind < H->capacity; bucket_ind++) {
        if (H->table[bucket_ind] != NULL) {
            chain *c = H->table[bucket_ind];
            while (c != NULL) {
                entry x = c->data;

                // Check each entry in chain node is not NULL
                if (x == NULL)
                    return false;

                // Check there are no duplicate keys
                // (Skip because computationally expensive)

                // Check that each entry's key in the bucket chain hashes
                // to this bucket index
                if (index_of_key(H, entry_key(H, x)) != bucket_ind) {
                    return false;
                }

                // Count number of nodes
                node_count++;

                c = c->next;
            }
        }
    }

    return (H != NULL) && (H->size >= 0) && (H->capacity > 0) &&
           (node_count == H->size) && (H->entry_key != NULL) &&
           (H->hash != NULL) && (H->equiv != NULL);
}

/* Create new hash dictionary.
 *
 * @pre: 0 < initial_capacity
 * @post: is_hdict(result)
 * @return: The initialized hdict.
 */
hdict *hdict_new(int initial_capacity, entry_key_fn *entry_key,
                 key_equiv_fn *equiv, key_hash_fn *hash) {
    dbg_requires(initial_capacity > 0);
    dbg_requires(entry_key != NULL && hash != NULL && equiv != NULL);

    hdict *H = malloc(sizeof(hdict));
    H->size = 0;
    H->capacity = initial_capacity;
    H->table = calloc(initial_capacity, sizeof(chain *));

    // Set function pointers
    H->entry_key = entry_key;
    H->hash = hash;
    H->equiv = equiv;

    dbg_ensures(is_hdict(H));
    return H;
}

/* Destroy an existing hash dictionary.
 *
 * @pre: is_hdict(H)
 * @post: !is_hdict(H)
 * @param[in] H: The hdict.
 */
void hdict_free(hdict *H, entry_free_fn *Fr) {
    dbg_requires(is_hdict(H));

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
 * @pre: H != NULL  (is_hdict(H) would be incorrect b/c load factor may be over)
 * @post: is_hdict(H)   (Restores data structure invariant)
 */
void hdict_resize(hdict *H, int new_capacity) {
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
            entry x = iter->data;
            dbg_assert(x != NULL); // Valid entry shouldn't be NULL

            int new_hash_ind = index_of_key(H, entry_key(H, x));

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
    dbg_ensures(is_hdict(H));
}

/* Lookup entry in hash dictionary.
 * If entry exists, that entry is returned. If doesn't exist, NULL is returned.
 *
 * @pre: is_hdict(H)
 * @post: is_hdict(H)
 * @post: result == NULL || key_equiv(entry_key(result), k)
 * @param[in] H: The hdict.
 * @param[in] k: The key to lookup the entry.
 * @return The entry if found, NULL if not found.
 */
entry hdict_lookup(hdict_t H, key k) {
    dbg_requires(is_hdict(H));

    int ind = index_of_key(H, k);
    // Iterate through chain looking for entry
    for (chain *iter = H->table[ind]; iter != NULL; iter = iter->next) {
        entry x = iter->data;
        if (key_equiv(H, k, entry_key(H, x))) {
            dbg_ensures(is_hdict(H));
            dbg_ensures(x != NULL && key_equiv(H, entry_key(H, x), k));
            return x;
        }
    }

    dbg_ensures(is_hdict(H));
    return NULL;
}

/* Insert an entry into the hash dictionary.
 *
 * @pre: is_hdict(H)
 * @pre: entry != NULL
 * @post: is_hdict(H)
 * @post: hdict_lookup(H, entry_key(x)) == x
 * @post: H->size > 0
 * @param[in] H: The hdict.
 * @param[in] x: The entry to insert.
 */
void hdict_insert(hdict_t H, entry x) {
    dbg_requires(is_hdict(H));
    dbg_requires(x != NULL);

    int ind = index_of_key(H, entry_key(H, x));
    bool found = false;

    // Iterate through chain looking for entry
    for (chain *iter = H->table[ind]; !found && iter != NULL;
         iter = iter->next) {
        entry old = iter->data;
        dbg_assert(old != NULL);
        if (key_equiv(H, entry_key(H, x), entry_key(H, old))) {
            iter->data = x;
            found = true;
        }
    }

    if (!found) {
        // Insert entry into beginning of list
        chain *to_insert = malloc(sizeof(chain));
        to_insert->data = x;
        to_insert->next = H->table[ind];
        H->table[ind] = to_insert;
    }

    H->size++;

    // Resize capacity as necessary
    if ((double)H->size / H->capacity >= MAX_LOAD_FACTOR) {
        hdict_resize(H, 2 * (H->capacity)); // double the capacity
    }
    dbg_ensures(is_hdict(H));
    dbg_ensures(hdict_lookup(H, entry_key(H, x)) == x);
    dbg_ensures(H->size > 0);
}

/* Removes the entry from the hdict.
 *
 * Fails if there is no entry that matches the given key to remove.
 *
 * @pre: is_hdict(H)
 * @pre: hdict_lookup(H, k) != NULL
 * @pre: H->size > 0
 * @post: is_hdict(H)
 * @post: hdict_lookup(H, k) == NULL
 * @post: result != NULL && key_equiv(k, entry_key(result))
 * @param[in] H: The hdict.
 * @param[in] k: The key.
 * @return The entry removed from the hdict.
 */
entry hdict_remove(hdict *H, key k) {
    dbg_requires(is_hdict(H));
    dbg_requires(hdict_lookup(H, k) != NULL);
    dbg_requires(H->size > 0);

    int ind = index_of_key(H, k);
    chain *curr = H->table[ind];
    chain *prev;
    while (curr != NULL) {
        if (key_equiv(H, entry_key(H, curr->data), k)) {
            entry x = curr->data;

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
                hdict_resize(H, new_capacity); // Halve the capacity
            }

            dbg_ensures(is_hdict(H));
            dbg_ensures(hdict_lookup(H, k) == NULL);
            dbg_ensures(x != NULL && key_equiv(H, entry_key(H, x), k));
            return x;
        }

        prev = curr;
        curr = curr->next;
    }

    // Should not reach here
    return NULL;
}
