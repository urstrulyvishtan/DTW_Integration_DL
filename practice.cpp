#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> map; // This map stores the value and its last index
        for (int i = 0; i < nums.size(); ++i) {
            if (map.find(nums[i]) != map.end() && i - map[nums[i]] <= k) {
                return true;
            }
            map[nums[i]] = i; // Update the index of the current element
        }
        return false;
    }
};