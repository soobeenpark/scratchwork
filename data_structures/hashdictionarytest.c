#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "HashDictionary.h"

// Insert the key into the dictionary and increment the count of the word by 1
// in the entry.
void increment_wordcount(hdict_t H, char *word) {
    entry x = hdict_lookup(H, word);
    if (x == NULL) {
        // First time inserting
        x = malloc(sizeof(struct wcount));
        x->word = calloc(strlen(word) + 1, sizeof(char));
        for (size_t i = 0; i < strlen(word); i++) {
            x->word[i] = word[i];
        }
        x->word[strlen(word)] = '\0';
        x->count = 1;
        hdict_insert(H, x);
    } else {
        x->count++;
    }
}

// Insert the key into the dictionary and increment the count of the word by 1
// in the entry.
// @pre: word must have been previously counted in the hdict.
void decrement_wordcount(hdict_t H, char *word) {
    entry x = hdict_lookup(H, word);
    assert(x != NULL);
    x->count--;
    if (x->count == 0) {
        hdict_remove(H, word);
        free(x->word);
        free(x);
    }
}

int main() {
    // Test constructor initial capacity param and destructor.
    for (int i = 1; i < 2000; i++) {
        hdict_t capacity_test = hdict_new(i);
        hdict_free(capacity_test);
    }

    // Test adding words
    hdict_t H = hdict_new(1);
    assert(hdict_lookup(H, "Hello") == NULL);
    increment_wordcount(H, "Hello");
    entry x = hdict_lookup(H, "Hello");
    assert(x != NULL && key_equiv(entry_key(x), "Hello") && x->count == 1);

    increment_wordcount(H, "World");
    x = hdict_lookup(H, "World");
    assert(x != NULL && key_equiv(entry_key(x), "World") && x->count == 1);

    increment_wordcount(H, "Hello");
    x = hdict_lookup(H, "Hello");
    assert(x != NULL && key_equiv(entry_key(x), "Hello") && x->count == 2);

    increment_wordcount(H, "Me");

    // Test removing words
    decrement_wordcount(H, "World");
    x = hdict_lookup(H, "World");
    assert(x == NULL);

    decrement_wordcount(H, "Hello");
    x = hdict_lookup(H, "Hello");
    assert(x != NULL && key_equiv(entry_key(x), "Hello") && x->count == 1);

    hdict_free(H);

    //////////// Stress Test ////////////
    printf("Beginning stress test... this may take a minute\n");
    H = hdict_new(1);
    for (int first = 'a'; first <= 'z'; first++) {
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
    printf("STRESS TEST: After inserting\n");
    hdict_print(H);

    for (int first = 'a'; first <= 'z'; first++) {
        for (int second = 'a'; second <= 'z'; second++) {
            for (int third = 'a'; third <= 'z'; third++) {
                char str[4];
                str[0] = first;
                str[1] = second;
                str[2] = third;
                str[3] = '\0';
                x = hdict_lookup(H, str);
                assert(x != NULL && x->count == 1);

                decrement_wordcount(H, str);
            }
        }
    }
    printf("STRESS TEST: After deleting\n");
    hdict_print(H);

    hdict_free(H);

    printf("Testing complete. No bugs found.\n");
}
