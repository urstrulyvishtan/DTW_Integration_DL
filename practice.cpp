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
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int goodNodes(TreeNode* root) {
        return countGoodNodes(root, INT_MIN);
    }
private:
    int countGoodNodes(TreeNode* node, int maxSoFar){
        if(!node) return 0;
        int count = 0;
        if(node->val >= maxSoFar){
            count = 1;
            maxSoFar = node->val;
        }
        count += countGoodNodes(node->left, maxSoFar);
        count += countGoodNodes(node->right, maxSoFar);
        return count;
    }
};