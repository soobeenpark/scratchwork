#include <iostream>

#ifndef LISTNODE_H
#define LISTNODE_H

// Define ListNode
// Most interview practice problems I saw only use a Node class as linked list
// interface instead of a full LinkedList wrapper class that includes a Node.
// So I implemented it the same way without using a wrapper class.
struct ListNode {
    // Member methods
    int val;
    ListNode *next;

    // Constructors
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *ptr) : val(x), next(ptr) {}
};

// Print from current node to the end of list.
void printList(ListNode *head) {
    ListNode *curr = head;
    while (curr != nullptr) {
        std::cout << curr->val << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

// Make deep-copy of list.
ListNode *copyList(ListNode *head) {
    if (head == nullptr) {
        return nullptr;
    }
    // Create first node
    ListNode *newHead = new ListNode(head->val);
    head = head->next;

    ListNode *prev = newHead;
    while (head != nullptr) {
        ListNode *curr = new ListNode(head->val);
        prev->next = curr;

        // Update pointers
        prev = curr;
        head = head->next;
    }
    return newHead;
}

// Delete list to prevent memory leak.
void deleteList(ListNode *head) {
    ListNode *curr = head;
    ListNode *prev = curr;
    while (curr != nullptr) {
        curr = curr->next;
        delete prev;
        prev = curr;
    }
}

#endif // LISTNODE_H
