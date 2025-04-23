#include <gtest/gtest.h>
#include <cstddef>

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
ListNode* create_list(size_t n);
ListNode* remove_every_nth_node(ListNode* head, size_t n);

// ---------- HELPERS ----------

// Counts how many nodes are in the list
size_t count_nodes(ListNode* head) {
    size_t count = 0;
    while (head != nullptr) {
        count++;
        head = head->next;
    }
    return count;
}

void delete_list(ListNode* head) {
    while (head != nullptr) {
        ListNode* next = head->next;
        delete head;
        head = next;
    }
}

// ---------- TESTS ----------

TEST(RemoveEveryNthNodeTest, RemovesEvery3rdFrom10) {
    ListNode* head = create_list(10);
    head = remove_every_nth_node(head, 3);

    // Should remove nodes 3, 6, 9 → result = 7 nodes
    EXPECT_EQ(count_nodes(head), 7);

    delete_list(head);
}

TEST(RemoveEveryNthNodeTest, RemovesAllWhenNIs1) {
    ListNode* head = create_list(10);
    head = remove_every_nth_node(head, 1);

    EXPECT_EQ(head, nullptr);
}

TEST(RemoveEveryNthNodeTest, NoRemovalWhenNIs0) {
    ListNode* head = create_list(5);
    ListNode* new_head = remove_every_nth_node(head, 0);

    EXPECT_EQ(count_nodes(new_head), 5);

    delete_list(new_head);
}

TEST(RemoveEveryNthNodeTest, EmptyListInput) {
    ListNode* head = nullptr;
    ListNode* new_head = remove_every_nth_node(head, 3);

    EXPECT_EQ(new_head, nullptr);
}

TEST(RemoveEveryNthNodeTest, RemoveLastNodeOnly) {
    ListNode* head = create_list(4);
    head = remove_every_nth_node(head, 4);

    // Should remove the 4th node, leaving 3 nodes
    EXPECT_EQ(count_nodes(head), 3);

    delete_list(head);
}
