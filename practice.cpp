#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> combination;
        sort(candidates.begin(), candidates.end());
        backtrack(candidates, target, 0, combination, result);
        return result;
    }
private:
    void backtrack(vector<int>& candidates, int target, int start, vector<int>& combination, vector<vector<int>>& result){
        if(target == 0){
            result.push_back(combination);
            return;
        }
        for(int i = start; i<candidates.size(); ++i){
            if(i>start && candidates[i] == candidates[i-1]) continue;
            if(candidates[i]>target) break;
            combination.push_back(candidates[i]);
            backtrack(candidates, target-candidates[i], i+1, combination, result);
            combination.pop_back();
        }
    }
};