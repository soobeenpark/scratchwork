/* Linked List Implementation */

#include <assert.h>

#include "LinkedList.h"

/* @brief Checks if segment [start, end) is a valid list segment.
 *
 * @pre: is_acyclic(start, end) where end is not in same list as start.
 * @param[in] start: The pointer to the start node in the segment.
 * @param[in] end: The pointer to the end node in the segment.
 * @return: true if valid segment, false otherwise.
 */
bool is_segment(list *start, list *end) {
    list *iter = start;
    while (iter != NULL) {
        if (iter == end) return true;
        iter = iter->next;
    }
    return false;
}

/* @brief Checks if there is a cycle in the list starting from start.
 *
 * @param[in] start: The pointer to the start node in the segment.
 * @return: true if there is no cycle in the segment, false otherwise.
 */
bool is_acyclic(list *start) {
    if (start == NULL) return true;
    list *slow = start;
    list *fast = start->next;
    while (slow != fast) {
        if (fast == NULL || fast->next == NULL) {
            return true;
        }
        assert(slow != NULL);
        slow = slow->next;
        assert(fast->next != NULL);
        fast = fast->next->next;
    }
    return false;
}
