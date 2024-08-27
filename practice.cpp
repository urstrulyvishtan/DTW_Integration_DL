#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        long long total = 0;
        int left = 0, result = 1;
        for(int right = 0; right<nums.size(); ++right){
            total+=nums[right];
            while((long long)nums[right] * (right-left+1)>total+k){
                total -= nums[left];
                left++;
            }
            result = max(result, right-left+1);
        }
        return result;
    }
};