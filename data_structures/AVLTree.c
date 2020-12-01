/* AVL Tree Dictionary Implementation
 *
 * Implements the AVL Self-Balancing AVL Tree separate from the Dictionary
 * interface. That way, the details of the AVL Tree are abstracted under the
 * Dictionary wrapper.
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

#include "AVLTree.h"

/******* Library Implementation *******/
/* Helper function to call D->entry_key */
key entry_key(dict *D, entry x) {
    return (*D->entry_key)(x);
}

/* Helper function to call D->key_compare */
int key_compare(dict *D, key k1, key k2) {
    return (*D->key_compare)(k1, k2);
}

//////////// AVL Tree ////////////
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

/* Retrieves the height of the tree
 *
 * Must be O(1) to guarantee O(1) rebalancing
 */
int height(tree *T) {
    return T == NULL ? 0 : T->height;
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

/* Helper to check if T contains the true height that it stores.
 *
 * @pre: is_tree(T)
 * @param[in] T: The tree.
 * @return true if the tree's height matches T->height.
 */
bool is_specified_height(tree *T) {
    if (T == NULL)
        return true;

    int lheight = height(T->left);
    int rheight = height(T->right);
    int h = lheight > rheight ? lheight + 1 : rheight + 1;

    return (is_specified_height(T->left) && is_specified_height(T->right) &&
            T->height == h);
}

/* Helper to check if T satisfis the height invariant.
 *
 * @pre: is_tree(T)
 * @param[in] T: The tree.
 * @return true if the tree's height is all balanced.
 */
bool is_balanced(tree *T) {
    if (T == NULL)
        return true;

    int lheight = height(T->left);
    int rheight = height(T->right);

    return (is_balanced(T->left) && is_balanced(T->right) &&
            abs(lheight - rheight) <= 1);
}

/* Data Structure Invariant.
 *
 * @param[in] T: The AVL Tree.
 * @return: true if valid AVL Tree, false otherwise.
 */
bool is_avl(dict *D, tree *T) {
    return is_tree(T) && is_ordered(D, T, NULL, NULL) &&
           is_specified_height(T) && is_balanced(T);
}

/* Retrieve entry from AVL Tree.
 *
 * @pre: is_avl(T)
 * @post: is_avl(T)
 * @post: entry == NULL || key_compare(entry_key(result), k) == 0
 * @param[in] T: The AVL Tree.
 * @param[in] k: The key to search the entry.
 * @return The entry that matches the key if exists, NULL otherwise.
 */
entry avl_lookup(dict *D, tree *T, key k) {
    dbg_requires(is_avl(D, T));
    if (T == NULL)
        return NULL; // Not found!

    int cmp = key_compare(D, k, entry_key(D, T->data));
    if (cmp == 0) {
        return T->data;
    } else if (cmp < 0) {
        return avl_lookup(D, T->left, k);
    } else {
        return avl_lookup(D, T->right, k);
    }
}

/* Helper to create leaf node. */
tree *leaf(entry x) {
    tree *T = malloc(sizeof(tree));
    T->data = x;
    T->left = NULL;
    T->right = NULL;
    T->height = 1;
    return T;
}

/* Fixes height after a rotation is performed */
void fix_height(tree *T) {
    dbg_requires(is_tree(T) && T != NULL);
    dbg_requires(is_specified_height(T->right));
    dbg_requires(is_specified_height(T->left));

    int l = height(T->left);
    int r = height(T->right);
    T->height = l > r ? (l + 1) : (r + 1);

    dbg_ensures(is_specified_height(T));
}

/* Performs a right rotation on the tree node in O(1) */
tree *rotate_right(tree *T) {
    dbg_requires(T != NULL && T->left != NULL);

    tree *left_subtree = T->left;
    T->left = left_subtree->right;
    left_subtree->right = T;

    fix_height(T);
    fix_height(left_subtree);

    return left_subtree;
}

/* Performs a left rotation on the tree node in O(1) */
tree *rotate_left(tree *T) {
    dbg_requires(T != NULL && T->right != NULL);

    tree *right_subtree = T->right;
    T->right = right_subtree->left;
    right_subtree->left = T;

    fix_height(T);
    fix_height(right_subtree);

    return right_subtree;
}

/* Helper function to rebalance the AVL tree's right subtree after insertion.
 * O(1)
 *
 * @pre: T != NULL
 * @pre: is_avl(T->left) && is_avl(T->right)
 * @post: is_avl(T)
 */
tree *rebalance_right(dict *D, tree *T) {
    // Assert that an insertion happened in T's right child
    dbg_requires(T != NULL);
    dbg_requires(is_avl(D, T->left) && is_avl(D, T->right));

    if (height(T->right) - height(T->left) == 2) { // violation
        if (height(T->right->left) > height(T->right->right)) {
            // violation in left inner subtree - right/left double rotation
            T->right = rotate_right(T->right);
        }
        T = rotate_left(T);
    } else {
        // no violation - tree height may have grown by 1
        fix_height(T);
    }

    dbg_ensures(is_avl(D, T));
    return T;
}

/* Helper function to rebalance the AVL tree's left subtree after insertion
 * O(1)
 *
 * @pre: T != NULL
 * @pre: is_avl(T->left) && is_avl(T->right)
 * @post: is_avl(T)
 */
tree *rebalance_left(dict *D, tree *T) {
    // Assert that an insertion happened in T's left child
    dbg_requires(T != NULL);
    dbg_requires(is_avl(D, T->left) && is_avl(D, T->right));

    if (height(T->left) - height(T->right) == 2) { // violation
        if (height(T->left->right) > height(T->left->left)) {
            // violation in right inner subtree - left/right double rotation
            T->left = rotate_left(T->left);
        }
        T = rotate_right(T);
    } else {
        // no violation - tree height may have grown by 1
        fix_height(T);
    }

    dbg_ensures(is_avl(D, T));
    return T;
}

/* Insert entry into AVL Tree.
 *
 * @pre: is_avl(T)
 * @post: is_avl(T)
 * @post: avl_lookup(entry_key(x)) == x
 * @param[in] T: The AVL Tree.
 * @param[in] x: The entry to insert.
 * @return: The current tree node.
 */
tree *avl_insert(dict *D, tree *T, entry x) {
    dbg_requires(is_avl(D, T));

    if (T == NULL)
        return leaf(x);

    dbg_assert(is_avl(D, T->left) && is_avl(D, T->right));

    key k = entry_key(D, T->data);
    int cmp = key_compare(D, entry_key(D, x), k);
    if (cmp == 0) {
        T->data = x;
    } else if (cmp < 0) {
        T->left = avl_insert(D, T->left, x);
        T = rebalance_left(D, T);
    } else {
        T->right = avl_insert(D, T->right, x);
        T = rebalance_right(D, T);
    }

    dbg_ensures(is_avl(D, T));
    dbg_ensures(avl_lookup(D, T, entry_key(D, x)) == x);
    return T;
}

/* Helper to retrieve tree node that contains minimum element in AVL Tree. */
tree *avl_find_min_node(tree *T) {
    if (T == NULL) {
        return NULL;
    }

    while (T->left != NULL) {
        T = T->left;
    }
    return T;
}

/* Retrieve minimum entry from AVL Tree.
 *
 * @pre: is_avl(T)
 * @post: is_avl(T)
 * @param[in] T: The AVL Tree.
 * @return The minimum entry stored in the AVL Tree.
 */
entry avl_find_min(dict *D, tree *T) {
    dbg_requires(is_avl(D, T));

    tree *min_node = avl_find_min_node(T);
    if (min_node == NULL)
        return NULL;

    dbg_ensures(is_avl(D, T));
    return min_node->data;
}

/* Removes entry from AVL Tree.
 *
 * @pre: is_avl(T)
 * @pre: T != NULL && entry_key(avl_lookup(T, k)) == k
 * @post: avl_lookup(T, k) == NULL
 * @param[in] T: The AVL Tree.
 * @param[in] k: The key of the entry to remove.
 * @param[in] Fr: The function to free the entry from memory.
 * @return: The removed entry.
 */
tree *avl_remove(dict *D, tree *T, key k, entry_free_fn *Fr) {
    dbg_requires(is_avl(D, T));
    dbg_requires(entry_key(D, avl_lookup(D, T, k)) == k);

    // Traverse the tree until we reach the node that must be deleted
    if (T == NULL)
        return NULL;

    int cmp = key_compare(D, k, entry_key(D, T->data));
    if (cmp < 0) {
        T->left = avl_remove(D, T->left, k, Fr);
        T = rebalance_right(D, T);
        return T;
    } else if (cmp > 0) {
        T->right = avl_remove(D, T->right, k, Fr);
        T = rebalance_left(D, T);
        return T;
    }

    dbg_assert(cmp == 0);
    // T is now the node to remove
    // Get tree node to return
    tree *to_return;
    if (T->left == NULL && T->right == NULL) {
        // Case 1 - T has no children nodes (T is a leaf)
        to_return = NULL;
    } else if (T->left != NULL && T->right == NULL) {
        // Case 2a - T only has left child
        to_return = T->left;
    } else if (T->left == NULL && T->right != NULL) {
        // Case 2b - T only has right child
        to_return = T->right;
    } else {
        // Case 3 - T has both children nodes
        dbg_assert(T->right != NULL);

        // Find successor to take over T
        // The node with sucessor is guaranteed to have only right child
        tree *successor_node = avl_find_min_node(T->right);
        dbg_assert(successor_node->left == NULL);

        // Swap entries
        entry tmp = T->data;
        T->data = successor_node->data;
        successor_node->data = tmp;

        // Recursive call - removing node now guaranteed to be in
        // Case 1 or 2 after swap
        return avl_remove(D, T->right, k, Fr);
    }

    // Free node and return entry
    entry x = T->data;
    if (*Fr != NULL) {
        (*Fr)(x);
    }
    free(T);

    dbg_ensures(is_avl(D, to_return));
    dbg_ensures(avl_lookup(D, to_return, k) == NULL);
    return to_return;
}

/* Deletes instantiated AVL Tree.
 *
 * @pre: is_avl(T)
 * @post: !is_avl(T)
 * @param[in] T: The tree.
 */
void avl_free(tree *T, entry_free_fn *Fr) {
    if (T == NULL)
        return;

    avl_free(T->left, Fr);
    avl_free(T->right, Fr);
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
    return D != NULL && is_avl(D, D->root) && D->size >= 0 &&
           D->entry_key != NULL && D->key_compare != NULL;
}

/* Create new AVL Tree dictionary.
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

/* Destroy an existing AVL Tree dictionary.
 *
 * @pre: is_dict(D)
 * @post: !is_dict(D)
 * @param[in] D: The dict.
 */
void dict_free(dict *D, entry_free_fn *Fr) {
    dbg_requires(is_dict(D));

    avl_free(D->root, Fr);
    free(D);
}

/* Lookup entry in AVL Tree dictionary.
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

    return avl_lookup(D, D->root, k);
}

/* Insert an entry into the AVL Tree dictionary.
 *
 * @pre: is_dict(D)
 * @pre: x != NULL
 * @post: is_dict(D)
 * @post: dict_lookup(D, entry_key(x)) == x
 * @post: dict_size(D) > 0
 * @param[in] D: The dict.
 * @param[in] x: The entry to insert.
 */
void dict_insert(dict_t D, entry x) {
    dbg_requires(is_dict(D));
    dbg_requires(x != NULL);

    D->root = avl_insert(D, D->root, x);
    D->size++;

    dbg_ensures(is_dict(D));
    dbg_ensures(dict_lookup(D, entry_key(D, x)) == x);
    dbg_ensures(dict_size(D) > 0);
}

/* Removes an entry from the AVL Tree dictionary.
 *
 * @pre: is_dict(D)
 * @pre: entry_key(D, dict_lookup(D, k)) == k
 * @pre: dict_size(D) > 0
 * @post: is_dict(D)
 * @post: dict_lookup(D, k) == NULL
 * @param[in] D: The dict.
 * @param[in] k: The key of the entry to insert.
 */
void dict_remove(dict *D, key k, entry_free_fn *Fr) {
    dbg_requires(is_dict(D));
    dbg_requires(entry_key(D, dict_lookup(D, k)) == k);
    dbg_requires(dict_size(D) > 0);

    D->root = avl_remove(D, D->root, k, Fr);
}

/* Find the minimum entry in the AVL Tree dictionary.
 *
 * @pre: is_dict(D)
 * @post: is_dict(D)
 * @param[in] D: The dict.
 * @param[in] k: The key.
 * @return The minimum entry stored in the dict.
 */
entry dict_find_min(dict_t D) {
    dbg_requires(is_dict(D));

    return avl_find_min(D, D->root);
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
