/* Binary Search Tree Dictionary Implementation
 *
 * Implements the BST separate from the Dictionary interface.
 * That way, the details of the BST are abstracted under the Dictionary wrapper.
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

#include "BinarySearchTree.h"

/******* Library Implementation *******/
/* Helper function to call D->entry_key */
key entry_key(dict *D, entry x) {
    return (*D->entry_key)(x);
}

/* Helper function to call D->key_compare */
int key_compare(dict *D, key k1, key k2) {
    return (*D->key_compare)(k1, k2);
}

//////////// BST ////////////
/* Helper used to check if T is a valid tree.
 *
 * @param[in] T: The tree.
 * @return true if valid tree, false otherwise.
 */
bool is_tree(tree *T) {
    if (T == NULL)
        return true;

    return T->data != NULL && is_tree(T->left) && is_tree(T->right);
}

/* Helper used to check if T is ordered
 *
 * Checks valid ordering in O(n) time, where n is number of nodes in tree.
 *
 * @param[in] T: The tree.
 * @param[in] lo: The minimum that all elements in this tree must be gte.
 * @param[in] hi: The maximum that all elements in this tree must be lte.
 * @return true if valid tree, false otherwise.
 */
bool is_ordered(dict *D, tree *T, entry lo, entry hi) {
    if (T == NULL)
        return true;

    entry x = T->data;
    key k = entry_key(D, x);
    return x != NULL &&
           (lo == NULL || key_compare(D, entry_key(D, lo), k) < 0) &&
           (hi == NULL || key_compare(D, k, entry_key(D, hi)) < 0) &&
           (is_ordered(D, T->left, lo, x)) && (is_ordered(D, T->right, x, hi));
}

/* Data Structure Invariant.
 *
 * @param[in] T: The BST.
 * @return: true if valid BST, false otherwise.
 */
bool is_bst(dict *D, tree *T) {
    return is_tree(T) && is_ordered(D, T, NULL, NULL);
}

/* Retrieve entry from BST.
 *
 * @pre: is_bst(T)
 * @post: is_bst(T)
 * @post: entry == NULL || key_compare(entry_key(result), k) == 0
 * @param[in] T: The BST.
 * @param[in] k: The key to search the entry.
 * @return The entry that matches the key if exists, NULL otherwise.
 */
entry bst_lookup(dict *D, tree *T, key k) {
    dbg_requires(is_bst(D, T));
    if (T == NULL)
        return NULL; // Not found!

    int cmp = key_compare(D, k, entry_key(D, T->data));
    if (cmp == 0) {
        return T->data;
    } else if (cmp < 0) {
        return bst_lookup(D, T->left, k);
    } else {
        return bst_lookup(D, T->right, k);
    }
}

/* Helper to create leaf node. */
tree *leaf(entry x) {
    tree *T = malloc(sizeof(tree));
    T->data = x;
    T->left = NULL;
    T->right = NULL;
    return T;
}

/* Insert entry into BST.
 *
 * @pre: is_bst(T)
 * @post: is_bst(T)
 * @post: bst_lookup(entry_key(x)) == x
 * @param[in] T: The BST.
 * @param[in] x: The entry to insert.
 * @return: The current tree node.
 */
tree *bst_insert(dict *D, tree *T, entry x) {
    dbg_requires(is_bst(D, T));

    if (T == NULL)
        return leaf(x);

    key k = entry_key(D, T->data);
    int cmp = key_compare(D, entry_key(D, x), k);
    if (cmp == 0) {
        T->data = x;
    } else if (cmp < 0) {
        T->left = bst_insert(D, T->left, x);
    } else {
        T->right = bst_insert(D, T->right, x);
    }

    dbg_ensures(is_bst(D, T));
    dbg_ensures(bst_lookup(D, T, entry_key(D, x)) == x);
    return T;
}

/* Retireve minimum entry from BST.
 *
 * @pre: is_bst(T)
 * @post: is_bst(T)
 * @param[in] T: The BST.
 * @return The minimum entry stored in the BST.
 */
entry bst_find_min(dict *D, tree *T) {
    dbg_ensures(is_bst(D, T));
    if (T == NULL)
        return NULL;

    while (T->left != NULL) {
        T = T->left;
    }
    dbg_ensures(is_bst(D, T));
    return T->data;
}

/* Deletes instantiated BST.
 *
 * @pre: is_bst(T)
 * @post: !is_bst(T)
 * @param[in] T: The tree.
 */
void bst_free(tree *T, entry_free_fn *Fr) {
    if (T == NULL)
        return;

    bst_free(T->left, Fr);
    bst_free(T->right, Fr);
    if (Fr != NULL)
        (*Fr)(T->data);
    free(T);
}

//////////// Dictionary ////////////
/* @brief Checks if the dict is valid (data structure invariant).
 *
 * @param[in] D: The dict
 * @return: true if valid dict, false otherwise.
 */
bool is_dict(dict *D) {
    return D != NULL && is_bst(D, D->root) && D->size >= 0 &&
           D->entry_key != NULL && D->key_compare != NULL;
}

/* Create new BST dictionary.
 *
 * @post: is_dict(result)
 * @return: The initialized dict.
 */
dict *dict_new(entry_key_fn *entry_key, key_compare_fn *key_compare) {
    dbg_requires(entry_key != NULL && key_compare != NULL);

    dict *D = malloc(sizeof(dict));
    D->size = 0;
    D->root = NULL;

    // Set function pointers
    D->entry_key = entry_key;
    D->key_compare = key_compare;

    dbg_ensures(is_dict(D));
    return D;
}

/* Destroy an existing BST dictionary.
 *
 * @pre: is_dict(D)
 * @post: !is_dict(D)
 * @param[in] D: The dict.
 */
void dict_free(dict *D, entry_free_fn *Fr) {
    dbg_requires(is_dict(D));

    bst_free(D->root, Fr);
    free(D);
}

/* Lookup entry in BST dictionary.
 * If entry exists, that entry is returned. If doesn't exist, NULL is returned.
 *
 * @pre: is_dict(D)
 * @post: is_dict(D)
 * @post: result == NULL || key_equiv(entry_key(result), k)
 * @param[in] D: The dict.
 * @param[in] k: The key to lookup the entry.
 * @return The entry if found, NULL if not found.
 */
entry dict_lookup(dict_t D, key k) {
    dbg_requires(is_dict(D));

    return bst_lookup(D, D->root, k);
}

/* Insert an entry into the BST dictionary.
 *
 * @pre: is_dict(D)
 * @pre: x != NULL
 * @post: is_dict(D)
 * @post: dict_lookup(D, entry_key(x)) == x
 * @post: D->size > 0
 * @param[in] D: The dict.
 * @param[in] x: The entry to insert.
 */
void dict_insert(dict_t D, entry x) {
    dbg_requires(is_dict(D));
    dbg_requires(x != NULL);

    D->root = bst_insert(D, D->root, x);
    D->size++;

    dbg_ensures(is_dict(D));
    dbg_ensures(dict_lookup(D, entry_key(D, x)) == x);
    dbg_ensures(D->size > 0);
}

/* Find the minimum entry in the BST dictionary.
 *
 * @pre: is_dict(D)
 * @post: is_dict(D)
 * @param[in] D: The dict.
 * @param[in] k: The key.
 * @return The minimum entry stored in the dict.
 */
entry dict_find_min(dict_t D) {
    dbg_requires(is_dict(D));

    return bst_find_min(D, D->root);
}

/* Get size of dictionary.
 *
 * @pre: is_dict(D)
 * @post: is_dict(D)
 * @param[in] D: The dict.
 * @return The number of entries stored in the dict.
 */
int dict_size(dict_t D) {
    return D->size;
}
