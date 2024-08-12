#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {
        int maxX = 0, maxY = 0, maxZ = 0;
        
        for (const auto& triplet : triplets) {
            if (triplet[0] <= target[0] && triplet[1] <= target[1] && triplet[2] <= target[2]) {
                maxX = max(maxX, triplet[0]);
                maxY = max(maxY, triplet[1]);
                maxZ = max(maxZ, triplet[2]);
            }
        }
        
        return maxX == target[0] && maxY == target[1] && maxZ == target[2];
    }
};