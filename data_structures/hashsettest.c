#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "HashSet.h"

/******* Client-Defined Types and Operations *******/
/* Hash set of strings */
/* Compare two elements for equivalence.
 *
 * To ensure coherence, two elements considered equivalent should hash
 * to the same value when the hash function elem_hash() is applied.
 *
 * @pre: x != NULL && hastag(char *, x) && y != NULL && hastag(char *, y)
 * @param[in] x: The first elem.
 * @param[in] y: The second elem.
 * @return true if elems are equivalent, false otherwise.
 */
bool elem_equiv_string(elem x, elem y) {
    char *elem1_str = (char *)x;
    char *elem2_str = (char *)y;
    return (strcmp(elem1_str, elem2_str) == 0);
}

/* Hash function for element that returns integer.
 *
 * See note about coherence in elem_equiv().
 *
 * @pre: x != NULL && hastag(char *, k)
 * @param[in] x: The elem to be hashed.
 * @return The integer hash value.
 */
int elem_hash_string(elem x) {
    char *elem_str = (char *)x;
    // Some versions of Java use this as their default string hashing function.
    // Note that this particularhash function doesn't involve psuedo-random
    // number generators.
    int h = 0;
    size_t len = strlen(elem_str);
    for (size_t i = 0; i < len; i++) {
        int ch = elem_str[i]; // Convert to ASCII value
        h *= 31;
        h += ch;
    }
    return h;
}

/* Function to delete the elem.
 *
 * @pre: e != NULL && hastag(struct wcount*, e)
 * @param[in] e: The elem to be freed.
 */
void elem_free_string(elem e) {
    char *to_delete = (char *)e;
    free(to_delete);
}
/******* End Client-Defined Types and Operations *******/

// Insert the word into the hset.
void add_word(hset_t H, char *word) {
    if (!hset_contains(H, (elem)word)) {
        // First time inserting
        char *s = calloc(strlen(word) + 1, sizeof(char));
        for (size_t i = 0; i < strlen(word); i++) {
            s[i] = word[i];
        }
        s[strlen(word)] = '\0';
        hset_insert(H, (elem)s);
    }
}

// Remove the word from the hset.
// @pre: word must have been previously counted in the hset.
void remove_word(hset_t H, char *word) {
    elem_free_string(hset_remove(H, word));
}

int main() {
    // Test constructor initial capacity param and destructor.
    for (int i = 1; i < 2000; i++) {
        hset_t capacity_test =
            hset_new(i, &elem_equiv_string, &elem_hash_string);
        hset_free(capacity_test, &elem_free_string);
    }

    // Test adding words
    hset_t H = hset_new(1, &elem_equiv_string, &elem_hash_string);
    assert(!hset_contains(H, (elem) "Hello"));
    add_word(H, "Hello");
    assert(hset_contains(H, (elem) "Hello"));

    add_word(H, "World");
    assert(hset_contains(H, (elem) "World"));

    add_word(H, "Hello");
    assert(hset_contains(H, (elem) "Hello"));

    add_word(H, "Me");
    assert(hset_contains(H, (elem) "Me"));

    // Test removing words
    remove_word(H, "World");
    assert(!hset_contains(H, (elem) "World"));

    remove_word(H, "Hello");
    assert(!hset_contains(H, (elem) "Hello"));

    hset_free(H, &elem_free_string);

    //////////// Stress Test ////////////
    printf("Beginning stress test... this may take a minute\n");
    H = hset_new(1, &elem_equiv_string, &elem_hash_string);
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
                add_word(H, str);
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
                assert(hset_contains(H, (elem)str));

                remove_word(H, str);
                assert(!hset_contains(H, (elem)str));
            }
        }
    }
    printf("\n");

    hset_free(H, &elem_free_string);

    printf("Testing complete. No bugs found.\n");
}
