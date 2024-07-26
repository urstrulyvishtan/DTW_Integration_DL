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
 ListNode* reverse(ListNode* start, ListNode* end){
    ListNode* prev = nullptr;
    ListNode* curr = start;
    ListNode* next = nullptr;
    while(curr!=end){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
 }
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(!head || k == 1) return head;
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* curr = head;
        ListNode* prev = dummy;
        ListNode* next = nullptr;

        int count = 0;
        while(curr){
            count++;
            curr = curr->next;
        }
        while(count>=k){
            curr = prev->next;
            next = curr->next;
            for(int i = 1; i<k; ++i){
                curr -> next = next -> next;
                next -> next = prev -> next;
                prev -> next = next;
                next = curr -> next;
            }
            prev = curr;
            count -= k;
        }
        return dummy->next;
    }
};