#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }
        
        // If (sum + target) is odd or target is out of the possible sum range, return 0
        if ((sum + target) % 2 != 0 || target > sum || target < -sum) {
            return 0;
        }
        
        int subsetSum = (sum + target) / 2;
        
        vector<int> dp(subsetSum + 1, 0);
        dp[0] = 1;  // There's one way to reach sum 0: by choosing nothing
        
        for (int num : nums) {
            for (int i = subsetSum; i >= num; --i) {
                dp[i] += dp[i - num];
            }
        }
        
        return dp[subsetSum];
    }
};