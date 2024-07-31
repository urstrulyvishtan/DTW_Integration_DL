#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if(intervals.empty()){
            return 0;
        }
        sort(intervals.begin(), intervals.end(),[](const vector<int>& a, vector<int>& b){
            return a[1]<b[1];
        });
        int count = 0;
        int lastEnd = intervals[0][1];
        for(int i = 1; i<intervals.size(); ++i){
            if(intervals[i][0] < lastEnd){
                ++count;
            }else{
                lastEnd = intervals[i][1];
            }
        }
        return count;
    }
};