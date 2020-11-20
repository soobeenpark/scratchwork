/* Linked List Interface
 *
 * A linked list is simply a list node pointer that points to the
 * first node in the list segment.
 * A list segment is a subset of a linked list from start (inclusive) to
 * end (exclusive), written segment [start, end).
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stdlib.h>

typedef int ItemType;

typedef struct list_node list;
struct list_node {
    ItemType data;
    list *next;
};

/* @brief Checks if segment [start, end) is a valid list segment.
 *
 * @pre: is_acyclic(start, end)
 * @param[in] start: The pointer to the start node in the segment.
 * @param[in] end: The pointer to the end node in the segment.
 * @return: true if valid segment, false otherwise.
 */
bool is_segment(list *start, list *end);

/* @brief Checks if there is a cycle in the list starting from start.
 *
 * @param[in] start: The pointer to the start node in the segment.
 * @return: true if there is no cycle in the segment, false otherwise.
 */
bool is_acyclic(list *start);

#endif /* LINKED_LIST_H */
