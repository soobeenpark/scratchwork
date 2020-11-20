#include <assert.h>
#include <stdio.h>

#include "Stack.h"

int main() {
    stack_t st = stack_new();
    assert(stack_empty(st));

    push(st, 5);
    assert(peek(st) == 5);
    assert(!stack_empty(st));
    push(st, 2);
    assert(peek(st) == 2);
    assert(!stack_empty(st));
    push(st, 3);
    assert(peek(st) == 3);
    assert(!stack_empty(st));
    
    int x = pop(st);
    assert(x == 3);
    assert(peek(st) == 2);
    assert(!stack_empty(st));
    
    push(st, 6);
    assert(peek(st) == 6);
    assert(!stack_empty(st));

    x = pop(st);
    assert(x == 6);
    assert(peek(st) == 2);
    assert(!stack_empty(st));

    x = pop(st);
    assert(x == 2);
    assert(peek(st) == 5);
    assert(!stack_empty(st));

    x = pop(st);
    assert(x == 5);
    assert(stack_empty(st));

    printf("Testing complete\n");
}
