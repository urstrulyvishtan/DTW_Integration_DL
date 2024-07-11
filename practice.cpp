#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int maxReach = 0;

        for(int i = 0; i<nums.size(); ++i){
            if(i>maxReach){
                return false;
            }
            maxReach = max(maxReach, i+nums[i]);
        }
        return maxReach >= nums.size() - 1;
    }
};