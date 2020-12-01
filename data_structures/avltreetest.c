#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "AVLTree.h"

/******* Client-Defined Types and Operations *******/
/* Word count dictionary */
struct wcount {
    char *word;
    int count;
};

/* Extract key from entry.
 *
 * @pre: x != NULL && hastag(struct wcount*, x)
 * @post: result != NULL && hastag(char *, result)
 * @param[in] x: The entry that contains the whole record to be stored.
 * @return The key that is used to locate the entry.
 */
key entry_key_wcount(entry x) {
    char *key_str = ((struct wcount *)x)->word;
    return (key)key_str;
}

/* Compare two keys.
 *
 * key_compare_wcount(k1, k2) returns
 * -1 if k1 < k2
 *  0 if k1 == k2
 *  1 if k1 > k2
 * where lexicographical string comparison is used.
 *
 * @pre: k1 != NULL && hastag(char *, k1) && k2 != NULL && hastag(char *, k2)
 * @param[in] k1: The first key.
 * @param[in] k2: The second key.
 * @return -1 if k1 < k2, 0 if k1 == k2, 1 if k1 > k2
 */
int key_compare_wcount(key k1, key k2) {
    char *key1_str = (char *)k1;
    char *key2_str = (char *)k2;
    return strcmp(key1_str, key2_str);
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
void increment_wordcount(dict_t D, char *word) {
    entry x = dict_lookup(D, (key)word);
    if (x == NULL) {
        // First time inserting
        struct wcount *e = malloc(sizeof(struct wcount));
        e->word = calloc(strlen(word) + 1, sizeof(char));
        for (size_t i = 0; i < strlen(word); i++) {
            e->word[i] = word[i];
        }
        e->word[strlen(word)] = '\0';
        e->count = 1;
        dict_insert(D, (entry)e);
    } else {
        ((struct wcount *)x)->count++;
    }
}

// Remove the key from the dictionary and decrement the count of the word by 1
// @pre: word must have been previously counted in the hdict.
void decrement_wordcount(dict_t D, char *word) {
    struct wcount *x = (struct wcount *)dict_lookup(D, (key)word);
    assert(x != NULL);
    x->count--;
    if (x->count == 0) {
        dict_remove(D, entry_key_wcount(x), &entry_free_wcount);
    }
}

int main() {
    // Test adding words
    dict_t D = dict_new(&entry_key_wcount, &key_compare_wcount);
    assert(dict_lookup(D, (key) "Hello") == NULL);
    increment_wordcount(D, "Hello");
    entry x = dict_lookup(D, (key) "Hello");
    assert(x != NULL && key_compare_wcount(entry_key_wcount(x), "Hello") == 0);
    assert(((struct wcount *)x)->count == 1);

    increment_wordcount(D, "World");
    x = dict_lookup(D, (key) "World");
    assert(x != NULL && key_compare_wcount(entry_key_wcount(x), "World") == 0);
    assert(((struct wcount *)x)->count == 1);

    increment_wordcount(D, "Hello");
    x = dict_lookup(D, (key) "Hello");
    assert(x != NULL && key_compare_wcount(entry_key_wcount(x), "Hello") == 0);
    assert(((struct wcount *)x)->count == 2);

    increment_wordcount(D, "Me");
    assert(dict_size(D) == 3);
    x = dict_lookup(D, (key) "Me");
    assert(x != NULL && key_compare_wcount(entry_key_wcount(x), "Me") == 0);
    assert(key_compare_wcount(entry_key_wcount(dict_find_min(D)), "Hello") ==
           0);

    increment_wordcount(D, "Apple");
    assert(dict_size(D) == 4);
    x = dict_lookup(D, (key) "Apple");
    assert(x != NULL && key_compare_wcount(entry_key_wcount(x), "Apple") == 0);
    assert(key_compare_wcount(entry_key_wcount(dict_find_min(D)), "Apple") ==
           0);

    increment_wordcount(D, "Party");
    assert(dict_size(D) == 5);
    x = dict_lookup(D, (key) "Party");
    assert(x != NULL && key_compare_wcount(entry_key_wcount(x), "Party") == 0);
    assert(key_compare_wcount(entry_key_wcount(dict_find_min(D)), "Apple") ==
           0);

    // Test removing words
    decrement_wordcount(D, "Apple");
    x = dict_lookup(D, (key) "Apple");
    assert(x == NULL);
    assert(key_compare_wcount(entry_key_wcount(dict_find_min(D)), "Hello") ==
           0);

    decrement_wordcount(D, "Hello");
    x = dict_lookup(D, (key) "Hello");
    assert(x != NULL && key_compare_wcount(entry_key_wcount(x), "Hello") == 0);
    assert(((struct wcount *)x)->count == 1);

    dict_free(D, &entry_free_wcount);

    //////////// Stress Test ////////////
    printf("Beginning stress test... this may take a minute\n");
    printf("RUN WITH -DDEBUG=0 in compilation flags, otherwise too slow!\n");

    D = dict_new(&entry_key_wcount, &key_compare_wcount);
    printf("STRESS TEST: inserting");
    fflush(stdout);

    int iters = 0;
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
                increment_wordcount(D, str);

                iters++;
                assert(iters == dict_size(D));
            }
        }
    }
    assert(iters == dict_size(D));
    assert(key_compare_wcount(entry_key_wcount(dict_find_min(D)), "aaa") == 0);
    assert(key_compare_wcount(entry_key_wcount(dict_lookup(D, "bbb")), "aaa") >
           0);
    assert(key_compare_wcount(entry_key_wcount(dict_lookup(D, "abc")), "xyz") <
           0);
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
                x = dict_lookup(D, (key)str);
                assert(x != NULL && ((struct wcount *)x)->count == 1);

                decrement_wordcount(D, str);
            }
        }
    }
    printf("\n");

    dict_free(D, &entry_free_wcount);

    printf("Testing complete. No bugs found.\n");
}
