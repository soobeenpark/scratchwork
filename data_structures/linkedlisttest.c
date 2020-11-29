#include <assert.h>
#include <limits.h>
#include <stdio.h>

#include "LinkedList.h"

/********** Exercises (15-122 Notes) **********/
// Returns true if sum of all nodes in segment [start, end) equals sum.
bool is_sum(list *start, list *end, int sum) {
    assert(is_segment(start, end));

    int accum = 0;
    while (start != end) {
        accum += *(int *)start->data;
        start = start->next;
    }
    return accum == sum;
}

// Returns length of list semgent.
int lseg_len(list *start, list *end) {
    assert(is_segment(start, end));
    if (start == end)
        return 0;
    return 1 + lseg_len(start->next, end);
}

// Returns ith index element.
elem ith(list *l, int i) {
    while (l != NULL) {
        if (i == 0)
            return l->data;
        l = l->next;
        i--;
    }
    assert(false); // Input param i was too large.
    return NULL;
}

// Returns true if element is in list segment [start, end).
bool is_in_lseg(int x, list *start, list *end) {
    assert(is_segment(start, end));
    if (start == end)
        return false;
    return *(int *)(start->data) == x || is_in_lseg(x, start->next, end);
}

// Returns true if the input list segment is sorted in ascending order.
bool is_sorted_lseg(list *start, list *end) {
    assert(is_segment(start, end));
    int prev_item = INT_MIN;
    while (start != end) {
        if (*(int *)(start->data) < prev_item)
            return false;
        prev_item = *(int *)start->data;
        start = start->next;
    }
    return true;
}

// Binary search on list segment [start, end). O(NlogN) time complexity.
int lseg_binsearch(int x, list *start, list *end) {
    assert(is_segment(start, end));
    assert(is_sorted_lseg(start, end));

    int len = lseg_len(start, end);
    int left = 0;
    int right = len;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (*(int *)(ith(start, mid)) == x) {
            return mid;
        } else if (*(int *)(ith(start, mid)) < x) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return -1;
}

/* Binary search on list segment in O(N) time complexity.
 *
 * The bin search above is O(NlogN) because the loop runs O(logN) times,
 * and each time the ith() function takes O(N) time to walk the list from
 * start to to the mid point.
 *
 * In this version, instead of walking the list each time from the start using
 * ith(), we start walking the list from each updated start of the halved
 * segments.
 *
 * Thus, the amount of walks to find the midpoint is
 * n/2 + n/4 + n/8 + ... + 1 = O(n)
 * and so the algorithm runs in O(n).
 */
int lseg_binsearch_linear(int x, list *start, list *end) {
    assert(is_segment(start, end));
    assert(is_sorted_lseg(start, end));

    int len = lseg_len(start, end);
    int left = 0;
    int right = len;
    while (left < right) {
        list *mid = start;
        int midInd = left + (right - left) / 2;

        // Walk the list from start until mid
        int i = midInd - left;
        while (i > 0) {
            assert(mid != NULL);
            mid = mid->next;
            i--;
        }

        if (*(int *)mid->data == x) {
            return midInd;
        } else if (*(int *)mid->data < x) {
            assert(mid != NULL);
            start = mid->next;
            left = midInd + 1;
        } else {
            end = mid; // Not strictly necessary but added for symmetry
            right = midInd;
        }
    }
    return -1;
}

void free_list_node(list *node) {
    free(node->data);
    free(node);
}

int main() {
    // Create a new linked list
    list *A = malloc(sizeof(list));
    list *B = malloc(sizeof(list));
    list *C = malloc(sizeof(list));
    list *D = malloc(sizeof(list));
    list *E = malloc(sizeof(list));

    // A -> B -> C -> D -> E
    //           |_________|
    A->next = B;
    B->next = C;
    C->next = D;
    D->next = E;
    E->next = C;

    assert(!is_acyclic(A));
    assert(!is_acyclic(B));
    assert(!is_acyclic(C));
    assert(!is_acyclic(D));
    assert(!is_acyclic(E));

    assert(is_segment(A, A));
    assert(is_segment(A, B));
    assert(is_segment(A, C));
    assert(is_segment(A, E));
    assert(!is_segment(NULL, C));
    assert(!is_segment(NULL, NULL));

    // Test is_sum()
    A->data = malloc(sizeof(int));
    *(int *)A->data = 3;
    B->data = malloc(sizeof(int));
    *(int *)B->data = 8;
    C->data = malloc(sizeof(int));
    *(int *)C->data = -1;
    D->data = malloc(sizeof(int));
    *(int *)D->data = 2;
    E->data = malloc(sizeof(int));
    *(int *)E->data = 5;
    assert(is_sum(A, A, 0));
    assert(is_sum(A, B, 3));
    assert(is_sum(B, D, 7));

    // Test lseg_len()
    assert(lseg_len(A, A) == 0);
    assert(lseg_len(A, C) == 2);
    assert(lseg_len(B, E) == 3);

    // Test ith()
    assert(*(int *)ith(A, 0) == 3);
    assert(*(int *)ith(B, 2) == 2); // D node's data

    // Test is_in_lseg()
    assert(is_in_lseg(3, A, E) && is_in_lseg(-1, A, E));
    assert(!is_in_lseg(7, A, E) && !is_in_lseg(0, A, E));

    // Test is_sorted_lseg()
    assert(is_sorted_lseg(D, D) && is_sorted_lseg(C, E) &&
           is_sorted_lseg(A, C));
    assert(!is_sorted_lseg(A, D) && !is_sorted_lseg(A, E));

    // Test lseg_binsearch()
    assert(lseg_binsearch(3, A, C) == 0);
    assert(lseg_binsearch(8, A, C) == 1);
    assert(lseg_binsearch(0, A, C) == -1);
    assert(lseg_binsearch(2, C, E) == 1);
    assert(lseg_binsearch(6, C, E) == -1);

    // Test lseg_binsearch_linear()
    assert(lseg_binsearch_linear(3, A, C) == 0);
    assert(lseg_binsearch_linear(8, A, C) == 1);
    assert(lseg_binsearch_linear(0, A, C) == -1);
    assert(lseg_binsearch_linear(2, C, E) == 1);
    assert(lseg_binsearch_linear(6, C, E) == -1);

    *(int *)A->data = 0;
    *(int *)B->data = 1;
    *(int *)C->data = 2;
    *(int *)D->data = 3;
    *(int *)E->data = 4;
    list *dummy = malloc(sizeof(list));
    dummy->next = NULL;
    E->next = dummy;
    assert(lseg_binsearch(0, A, dummy) == 0);
    assert(lseg_binsearch(1, A, dummy) == 1);
    assert(lseg_binsearch(2, A, dummy) == 2);
    assert(lseg_binsearch(3, A, dummy) == 3);
    assert(lseg_binsearch(4, A, dummy) == 4);
    assert(lseg_binsearch_linear(0, A, dummy) == 0);
    assert(lseg_binsearch_linear(1, A, dummy) == 1);
    assert(lseg_binsearch_linear(2, A, dummy) == 2);
    assert(lseg_binsearch_linear(3, A, dummy) == 3);
    assert(lseg_binsearch_linear(4, A, dummy) == 4);

    free_list_node(A);
    free_list_node(B);
    free_list_node(C);
    free_list_node(D);
    free_list_node(E);
    free_list_node(dummy);

    printf("Testing complete. No bugs found.\n");
}
