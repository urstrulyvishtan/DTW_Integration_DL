#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        if (lists.empty())
            return nullptr;

        auto cmp = [](ListNode* a, ListNode* b) {
            return a->val > b->val; // Min-heap based on node value
        };

        std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(cmp)>
            minHeap(cmp);

        // Add the first node of each list to the min-heap
        for (ListNode* list : lists) {
            if (list) {
                minHeap.push(list);
            }
        }

        ListNode dummy;
        ListNode* current = &dummy;

        // While there are nodes in the min-heap
        while (!minHeap.empty()) {
            // Get the smallest node
            ListNode* smallestNode = minHeap.top();
            minHeap.pop();
            current->next = smallestNode; // Attach it to the merged list
            current =
                current->next; // Move to the next position in the merged list

            // If there are more nodes in the list, add the next node to the
            // min-heap
            if (smallestNode->next) {
                minHeap.push(smallestNode->next);
            }
        }

        return dummy.next; // Return the head of the merged list
    }
};