#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "HashDictionary.h"

/******* Client-Defined Types and Operations *******/
/* Word count hash dictionary */
struct wcount {
    char *word;
    int count;
};

/* Extract key from entry.
 *
 * @pre: x != NULL && hastag(struct wcount*, x)
 * @post: result != NULL && hastag(string *, result)
 * @param[in] x: The entry that contains the whole record to be stored.
 * @return The key that is used to locate the entry.
 */
key entry_key_wcount(entry x) {
    char *key_str = ((struct wcount *)x)->word;
    return (key)key_str;
}

/* Compare two keys for equivalence.
 *
 * To ensure coherence, two keys considered equivalent should hash
 * to the same value when the hash function key_hash() is applied.
 *
 * @pre: k1 != NULL && hastag(char *, k1) && k2 != NULL && hastag(char *, k2)
 * @param[in] k1: The first key.
 * @param[in] k2: The second key.
 * @return true if keys are equivalent, false otherwise.
 */
bool key_equiv_wcount(key k1, key k2) {
    char *key1_str = (char *)k1;
    char *key2_str = (char *)k2;
    return (strcmp(key1_str, key2_str) == 0);
}

/* Hash function for key that returns integer.
 *
 * Choice of hash function is crucial in creating correct and efficient O(1)
 * hash table implementation.
 * Especially, hash functions should aim to map keys to the target integer
 * values with a uniform probability distribution, to give the best chance
 * to avoid keys clustering around a particular hash table index.
 *
 * Also see note about coherence in key_equiv().
 *
 * @pre: k != NULL && hastag(string *, k)
 * @param[in] k: The key to be hashed.
 * @return The integer hash value.
 */
int key_hash_wcount(key k) {
    char *key_str = (char *)k;
    // Some versions of Java use this as their default string hashing function.
    // Note that this particularhash function doesn't involve psuedo-random
    // number generators.
    int h = 0;
    size_t len = strlen(key_str);
    for (size_t i = 0; i < len; i++) {
        int ch = key_str[i]; // Convert to ASCII value
        h *= 31;
        h += ch;
    }
    return h;
}

/* Function to delete the entry.
 *
 * @pre: e != NULL && hastag(struct wcount*, e)
 * @param[in] e: The entry to be freed.
 */
void entry_free_wcount(entry e) {
    struct wcount *to_delete = (struct wcount *)e;
    free(to_delete->word);
    free(to_delete);
}
/******* End Client-Defined Types and Operations *******/

// Insert the key into the dictionary and increment the count of the word by 1
// in the entry.
void increment_wordcount(hdict_t H, char *word) {
    entry x = hdict_lookup(H, (key)word);
    if (x == NULL) {
        // First time inserting
        struct wcount *e = malloc(sizeof(struct wcount));
        e->word = calloc(strlen(word) + 1, sizeof(char));
        for (size_t i = 0; i < strlen(word); i++) {
            e->word[i] = word[i];
        }
        e->word[strlen(word)] = '\0';
        e->count = 1;
        hdict_insert(H, (entry)e);
    } else {
        ((struct wcount *)x)->count++;
    }
}

// Insert the key into the dictionary and increment the count of the word by 1
// in the entry.
// @pre: word must have been previously counted in the hdict.
void decrement_wordcount(hdict_t H, char *word) {
    struct wcount *x = (struct wcount *)hdict_lookup(H, (key)word);
    assert(x != NULL);
    x->count--;
    if (x->count == 0) {
        entry_free_wcount(hdict_remove(H, (key)x->word));
    }
}

int main() {
    // Test constructor initial capacity param and destructor.
    for (int i = 1; i < 2000; i++) {
        hdict_t capacity_test = hdict_new(i, &entry_key_wcount,
                                          &key_equiv_wcount, &key_hash_wcount);
        hdict_free(capacity_test, &entry_free_wcount);
    }

    // Test adding words
    hdict_t H =
        hdict_new(1, &entry_key_wcount, &key_equiv_wcount, &key_hash_wcount);
    assert(hdict_lookup(H, (key) "Hello") == NULL);
    increment_wordcount(H, "Hello");
    entry x = hdict_lookup(H, (key) "Hello");
    assert(x != NULL && key_equiv_wcount(entry_key_wcount(x), "Hello"));
    assert(((struct wcount *)x)->count == 1);

    increment_wordcount(H, "World");
    x = hdict_lookup(H, (key) "World");
    assert(x != NULL && key_equiv_wcount(entry_key_wcount(x), "World"));
    assert(((struct wcount *)x)->count == 1);

    increment_wordcount(H, "Hello");
    x = hdict_lookup(H, (key) "Hello");
    assert(x != NULL && key_equiv_wcount(entry_key_wcount(x), "Hello"));
    assert(((struct wcount *)x)->count == 2);

    increment_wordcount(H, "Me");

    // Test removing words
    decrement_wordcount(H, "World");
    x = hdict_lookup(H, (key) "World");
    assert(x == NULL);

    decrement_wordcount(H, "Hello");
    x = hdict_lookup(H, (key) "Hello");
    assert(x != NULL && key_equiv_wcount(entry_key_wcount(x), "Hello"));
    assert(((struct wcount *)x)->count == 1);

    hdict_free(H, &entry_free_wcount);

    //////////// Stress Test ////////////
    printf("Beginning stress test... this may take a minute\n");
    H = hdict_new(1, &entry_key_wcount, &key_equiv_wcount, &key_hash_wcount);
    printf("STRESS TEST: inserting");
    fflush(stdout);
    for (int first = 'a'; first <= 'z'; first++) {
        printf("."); // Status bar
        fflush(stdout);
        for (int second = 'a'; second <= 'z'; second++) {
            for (int third = 'a'; third <= 'z'; third++) {
                char str[4];
                str[0] = first;
                str[1] = second;
                str[2] = third;
                str[3] = '\0';
                increment_wordcount(H, str);
            }
        }
    }
    printf("\n");

    printf("STRESS TEST: deleting");
    fflush(stdout);
    for (int first = 'a'; first <= 'z'; first++) {
        printf("."); // Status bar
        fflush(stdout);
        for (int second = 'a'; second <= 'z'; second++) {
            for (int third = 'a'; third <= 'z'; third++) {
                char str[4];
                str[0] = first;
                str[1] = second;
                str[2] = third;
                str[3] = '\0';
                x = hdict_lookup(H, (key)str);
                assert(x != NULL && ((struct wcount *)x)->count == 1);

                decrement_wordcount(H, str);
            }
        }
    }
    printf("\n");

    hdict_free(H, &entry_free_wcount);

    printf("Testing complete. No bugs found.\n");
}
