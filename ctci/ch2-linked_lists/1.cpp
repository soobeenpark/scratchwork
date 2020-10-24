#include <cassert>
#include <iostream>
#include <unordered_set>

#include "ListNode.cpp"

/* Let n be the length of the list.
 * Time: O(n)
 * Space: O(n)
 */
ListNode* removeDups(ListNode *head) {
    std::unordered_set<int> set;
    
    ListNode *curr = head;
    ListNode *prev = nullptr;
    while (curr != nullptr) {
        int val = curr->val;
        if (set.count(val)) {
            // val already seen!
            assert(prev != nullptr);
            prev->next = curr->next;

            // Delete duplicate node
            ListNode *tmp = curr;
            curr = curr->next;
            delete tmp;
        } else {
            // val first time
            set.insert(val);
            prev = curr;
            curr = curr->next;
        }
    }
    return head;
}

/* Version with no extra space allowed (ie. Space complexity must be O(1)).
 * Runtime suffers as a tradeoff.
 *
 * Let n be the length of the list.
 * Time: O(n^2)
 * Space: O(1)
 */
ListNode* removeDupsNoBuffer(ListNode *head) {
    for (ListNode *curr = head; curr != nullptr; curr = curr -> next) {
        ListNode *runnerPrev = curr;
        ListNode *runner = curr->next;
        while (runner != nullptr) {
            if (runner->val == curr->val) {
                runnerPrev->next = runner->next;

                // Delete duplicate node
                ListNode *tmp = runner;
                runner = runner->next;
                delete tmp;
            } else {
                runnerPrev = runner;
                runner = runner->next;
            }
        }
    }
    return head;
}


int main() {
    // Create Linked List
    ListNode *head1 = new ListNode(1);
    ListNode *trav = head1;
    trav->next = new ListNode(2);
    trav = trav->next;
    trav->next = new ListNode(2);
    trav = trav->next;
    trav->next = new ListNode(2);
    trav = trav->next;
    trav->next = new ListNode(2);
    trav = trav->next;
    trav->next = new ListNode(6);
    trav = trav->next;
    trav->next = new ListNode(5);
    trav = trav->next;
    trav->next = new ListNode(5);
    trav = trav->next;
    trav->next = new ListNode(5);
    trav = trav->next;
    trav->next = new ListNode(2);
    trav = trav->next;

    ListNode *head2 = copyList(head1);

    std::cout << "Testing v1" << std::endl;
    printList(head1); // Before
    removeDups(head1);
    printList(head1); // After
    std::cout << std::endl;

    std::cout << "Testing v2" << std::endl;
    printList(head2); // Before
    removeDupsNoBuffer(head2);
    printList(head2); // After
    std::cout << std::endl;

    deleteList(head1);
    deleteList(head2);
}
