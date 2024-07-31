#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.empty()){
            return {};        }
    
    sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b){
        return a[0]<b[0];
    });
    vector<vector<int>> mergedIntervals;
    mergedIntervals.push_back(intervals[0]);
    for(const auto& interval:intervals){
        if(interval[0]<=mergedIntervals.back()[1]){
            mergedIntervals.back()[1] = max(mergedIntervals.back()[1], interval[1]);
        }else{
            mergedIntervals.push_back(interval);
        }
    }
    return mergedIntervals;
    }
};