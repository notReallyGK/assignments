#include <cstddef>
#include <iostream>

struct ListNode {
    ListNode* next = nullptr;
};

ListNode* create_list(size_t n) {
    if (n == 0) return nullptr;
    ListNode* head = new ListNode();
    ListNode* current = head;
    for (size_t i = 1; i < n; ++i) {
        current->next = new ListNode();
        current = current->next;
    }
    return head;
}

ListNode* remove_every_nth_node(ListNode* head, size_t n) {
    if (head == nullptr || n <= 1) {
        //if a singly linked list is empty or n <=1, then delete everything (or skip if n = 0)
        return (n == 0) ? head : nullptr;
    }

    ListNode* current = head;
    ListNode* prev = nullptr;
    size_t count = 1;

    while (current != nullptr) {
        if (count % n == 0) {
            // remove current node
            if (prev != nullptr) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
            current = current->next;
        } else {
            prev = current;
            current = current->next;
        }
        ++count;
    }

    return head;
}

int main() {
    ListNode* head = create_list(10);
    head = remove_every_nth_node(head, 5); // deleting every n_element
    int index = 1;
    while (head) {
        std::cout << "Node " << index++ << "\n";
        head = head->next;
    }
}
