#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
void makeCombination(std::vector<int>& candidates, int target, int idx, vector<int>& comb, int total, vector<vector<int>>& res) {
        if (total == target) {
            res.push_back(comb);
            return;
        }

        if (total > target || idx >= candidates.size()) {
            return;
        }

        comb.push_back(candidates[idx]);
        makeCombination(candidates, target, idx, comb, total + candidates[idx], res);
        comb.pop_back();
        makeCombination(candidates, target, idx + 1, comb, total, res);
    }