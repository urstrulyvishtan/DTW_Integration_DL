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
    ListNode* reverseList(ListNode* head){
        ListNode* prev = nullptr;
        while(head){
            ListNode* nextNode = head->next;
            head->next = prev;
            prev = head;
            head = nextNode;
        }
        return prev;
    }
    bool isPalindrome(ListNode* head) {
        if(!head||!head->next) return true;
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast&&fast->next){
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode* secondHalf = reverseList(slow);
        ListNode* firstHalf = head;
        ListNode* temp = secondHalf;
        while(temp){
            if(firstHalf->val != temp->val){
                return false;
            }
            firstHalf = firstHalf->next;
            temp = temp->next;
        }
        reverseList(secondHalf);
        return true;
    }
};