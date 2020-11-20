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
        accum += start->data;
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
ItemType ith(list *l, int i) {
    while (l != NULL) {
        if (i == 0)
            return l->data;
        l = l->next;
        i--;
    }
    assert(false); // Input param i was too large.
    return -1;
}

// Returns true if element is in list segment [start, end).
bool is_in_lseg(int x, list *start, list *end) {
    assert(is_segment(start, end));
    if (start == end)
        return false;
    return start->data == x || is_in_lseg(x, start->next, end);
}

// Returns true if the input list segment is sorted in ascending order.
bool is_sorted_lseg(list *start, list *end) {
    assert(is_segment(start, end));
    int prev_item = INT_MIN;
    while (start != end) {
        if (start->data < prev_item)
            return false;
        prev_item = start->data;
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
        if (ith(start, mid) == x) {
            return mid;
        } else if (ith(start, mid) < x) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return -1;
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
    A->data = 3;
    B->data = 8;
    C->data = -1;
    D->data = 2;
    E->data = 5;
    assert(is_sum(A, A, 0));
    assert(is_sum(A, B, 3));
    assert(is_sum(B, D, 7));

    // Test lseg_len()
    assert(lseg_len(A, A) == 0);
    assert(lseg_len(A, C) == 2);
    assert(lseg_len(B, E) == 3);

    // Test ith()
    assert(ith(A, 0) == 3);
    assert(ith(B, 2) == 2); // D node's data

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

    printf("Testing complete. No bugs found.\n");
}
