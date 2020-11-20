/* Stack Implementation
 *
 * Stack implementation using a linked list.
 * Instead of a dummy node, a normal NULL-terminated list is used.
 */

#include <assert.h>

#include "Stack.h"

/* @brief Checks if the stack is valid (data structure invariant).
 *
 * @param[in] S: The stack
 * @return: true if valid stack, false otherwise.
 */
bool is_stack(stack *S) {
    return S != NULL && is_acyclic(S->top);
}

/* @brief Checks if stack is empty.
 *
 * @pre: is_stack(S)
 * @post: is_stack(S)
 * @param[in] S: The stack
 * @return: true if empty, false otherwise.
 */
bool stack_empty(stack *S) {
    assert(is_stack(S));
    return S->top == NULL;
}

/* @brief Create new stack.
 *
 * @post: is_stack(result)
 * @post: stack_empty(result)
 * @return: The initialized stack.
 */
stack *stack_new() {
    stack *S = malloc(sizeof(stack));
    S->top = NULL;
    assert(is_stack(S));
    assert(stack_empty(S));
    return S;
}

/* @brief Destroy an existing stack
 *
 * @pre: is_stack(S)
 * @post: !is_stack(S)
 * @param[in] S: The stack.
 */
void stack_delete(stack *S) {
    assert(is_stack(S));

    // Delete all list nodes
    while (S->top != NULL) {
        list *to_delete = S->top;
        S->top = S->top->next;
        free(to_delete);
    }
    free(S); // Delete Stack
    assert(!is_stack(S));
}

/* @brief Push element to top of stack
 *
 * Push from the top to ensure O(1) time complexity.
 *
 * @pre: is_stack(S)
 * @post: is_stack(S)
 * @post: !stack_empty(S)
 * @param[in] S: The stack
 * @param[in] x: The item being inserted.
 */
void push(stack_t S, ItemType x) {
    assert(is_stack(S));

    list *to_insert = malloc(sizeof(list));
    to_insert->data = x;
    to_insert->next = S->top;
    S->top = to_insert;

    assert(is_stack(S));
    assert(!stack_empty(S));
}

/* @brief Pop from top of stack
 *
 * Push from the top to ensure O(1) time complexity.
 *
 * @pre: is_stack(S)
 * @pre: !stack_empty(S)
 * @post: is_stack(S)
 * @param[in] S: The stack
 * @return: The item being removed.
 */
ItemType pop(stack_t S) {
    assert(is_stack(S));
    assert(!stack_empty(S));

    ItemType x = S->top->data;
    list *to_delete = S->top;
    S->top = S->top->next;
    free(to_delete);

    assert(is_stack(S));
    return x;
}

/* @brief Get top element of stack without popping.
 *
 * @pre: is_stack(S)
 * @pre: !stack_empty(S)
 * @post: is_stack(S)
 * @param[in] S: The stack
 * @return: The item at the top.
 */
ItemType peek(stack_t S) {
    assert(is_stack(S));
    return S->top->data;
}
