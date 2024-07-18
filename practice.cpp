#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> deq;
        vector<int> result;

        for(int i = 0; i<nums.size(); ++i){
            if(!deq.empty() && deq.front() == i - k){
                deq.pop_front();
            }
            while(!deq.empty() && nums[deq.back()]<=nums[i]){
                deq.pop_back();
            }
        deq.push_back(i);
        if(i>=k-1){
            result.push_back(nums[deq.front()]);
        }
    }
    return result;
}
        
};