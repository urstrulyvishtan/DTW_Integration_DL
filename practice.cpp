#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int result = 0;
        for(int num:nums){
            result ^=num;
        }
        return result;
    }
};