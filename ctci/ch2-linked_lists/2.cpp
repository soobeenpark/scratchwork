// Return Kth to Last
// Implement an algorithm to find the kth to last element of a singly linked
// list.

#include <iostream>

#include "ListNode.cpp"

/* Let n be the length of the list.
 * Time: O(n)
 * Space: O(1)
 */
int kthLastIterative(ListNode *head, int k) {
    ListNode *p1 = head;
    ListNode *p2 = head;
    for (int i = 0; i < k; i++) {
        if (p2 == nullptr) {
            return -1; // Bounds check
        }
        p2 = p2->next;
    }

    while (p2 != nullptr) {
        p1 = p1->next;
        p2 = p2->next;
    }

    return p1->val;
}

// Helper for recursive
int kthLastRecursiveHelper(ListNode *head, int k, int &count) {
    if (head == nullptr) {
        return -1;
    }
    int result = kthLastRecursiveHelper(head->next, k, count);
    count++;
    if (count == k) {
        return head->val;
    }
    return result;
}

/* Let n be the length of the list.
 * Time: O(n)
 * Space: O(n)
 */
int kthLastRecursive(ListNode *head, int k) {
    int count = 0;
    return kthLastRecursiveHelper(head, k, count);
}

void test(ListNode *head, int k, int shouldEqual) {
    int resultIterative = kthLastIterative(head, k);
    if (resultIterative != shouldEqual) {
        std::cout << "TEST FAIL - iterative: " << resultIterative
                  << " should eval to " << shouldEqual << std::endl;
    }

    int resultRecursive = kthLastRecursive(head, k);
    if (resultRecursive != shouldEqual) {
        std::cout << "TEST FAIL - recursive: " << resultRecursive
                  << " should eval to " << shouldEqual << std::endl;
    }
}

int main() {
    // Create Linked List
    ListNode *head1 = new ListNode(1);
    ListNode *trav = head1;
    trav->next = new ListNode(1);
    trav = trav->next;
    trav->next = new ListNode(2);
    trav = trav->next;
    trav->next = new ListNode(3);
    trav = trav->next;
    trav->next = new ListNode(5);
    trav = trav->next;
    trav->next = new ListNode(8);
    trav = trav->next;
    trav->next = new ListNode(13);
    trav = trav->next;
    trav->next = new ListNode(21);
    trav = trav->next;
    trav->next = new ListNode(34);
    trav = trav->next;
    trav->next = new ListNode(55);
    trav = trav->next;

    test(head1, 1, 55);
    test(head1, 2, 34);
    test(head1, 3, 21);
    test(head1, 4, 13);
    test(head1, 5, 8);
    test(head1, 6, 5);
    test(head1, 7, 3);
    test(head1, 8, 2);
    test(head1, 9, 1);
    test(head1, 10, 1);
    test(head1, 11, -1);

    std::cout << "Testing complete" << std::endl;
    deleteList(head1);
}
