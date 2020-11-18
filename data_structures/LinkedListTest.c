#include <assert.h>
#include <stdio.h>

#include "LinkedList.h"

int main() {
    // Create a new linked list
    list* A = malloc(sizeof(list));
    list* B = malloc(sizeof(list));
    list* C = malloc(sizeof(list));
    list* D = malloc(sizeof(list));
    list* E = malloc(sizeof(list));
    list* F = malloc(sizeof(list));

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

    printf("Testing complete\n");
}
