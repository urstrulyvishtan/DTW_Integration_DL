#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int minimumDifference(vector<int>& scores, int k) {
        std::sort(scores.begin(), scores.end());
        int minDiff = INT_MAX;
        for(int i = 0; i<=scores.size()-k; ++i){
            int diff = scores[i+k-1]-scores[i];
            minDiff = std::min(minDiff, diff);
        }
        return minDiff;
    }
};