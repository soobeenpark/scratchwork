/* Queue Implementation
 *
 * Queue implementation using a linked list.
 * A dummy node is used to indicate the location of the end of the list segment.
 */

#include <assert.h>

#include "Queue.h"

/* @brief Checks if the queue is valid (data structure invariant).
 *
 * @param[in] Q: The queue
 * @return: true if valid queue, false otherwise.
 */
bool is_queue(queue *Q) {
    return Q != NULL && is_acyclic(Q->front) && is_segment(Q->front, Q->back);
}

/* @brief Checks if queue is empty.
 *
 * @pre: is_queue(Q)
 * @post: is_queue(Q)
 * @param[in] Q: The queue
 * @return: true if empty, false otherwise.
 */
bool queue_empty(queue *Q) {
    assert(is_queue(Q));
    return Q->front == Q->back;
}

/* @brief Create new queue.
 *
 * @post: is_queue(result)
 * @post: queue_empty(result)
 * @return: The initialized queue.
 */
queue *queue_new() {
    queue *Q = malloc(sizeof(queue));
    Q->front = malloc(sizeof(list)); // Create dummy node
    Q->back = Q->front;
    assert(is_queue(Q));
    assert(queue_empty(Q));
    return Q;
}

/* @brief Destroy an existing queue
 *
 * @pre: is_queue(Q)
 * @post: !is_queue(Q)
 * @param[in] Q: The queue.
 */
void queue_delete(queue *Q) {
    assert(is_queue(Q));

    // Delete all list nodes
    while (Q->front != Q->back) {
        list *to_delete = Q->front;
        Q->front = Q->front->next;
        free(to_delete);
    }
    free(Q->front); // Delete dummy node
    free(Q);        // Delete Queue
}

/* @brief Enqueue element to back of queue
 *
 * Enqueue from the back to ensure O(1) time complexity.
 *
 * @pre: is_queue(Q)
 * @post: is_queue(Q)
 * @post: !queue_empty(Q)
 * @param[in] Q: The queue
 * @param[in] x: The item being inserted.
 */
void enq(queue *Q, ItemType x) {
    assert(is_queue(Q));

    Q->back->data = x;
    Q->back->next = malloc(sizeof(list)); // Create new dummy node
    Q->back = Q->back->next;              // Set new dummy node

    assert(is_queue(Q));
    assert(!queue_empty(Q));
}

/* @brief Dequeue from front of queue
 *
 * Dequeue from the front to ensure O(1) time complexity.
 *
 * @pre: is_queue(Q)
 * @pre: !queue_empty(Q)
 * @post: is_queue(Q)
 * @param[in] Q: The queue
 * @return: The item being removed.
 */
ItemType deq(queue *Q) {
    assert(is_queue(Q));
    assert(!queue_empty(Q));

    ItemType x = Q->front->data;
    list *to_delete = Q->front;
    Q->front = Q->front->next;
    free(to_delete);

    assert(is_queue(Q));
    return x;
}

/* @brief Get front element of queue without dequeing.
 *
 * @pre: is_queue(Q)
 * @pre: !queue_empty(Q)
 * @post: is_queue(Q)
 * @param[in] Q: The queue
 * @return: The item at the front.
 */
ItemType peek(queue_t Q) {
    assert(is_queue(Q));
    return Q->front->data;
}
