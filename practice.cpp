#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
         // Sort intervals by start time
        sort(intervals.begin(), intervals.end());
        
        // Create a vector of pairs to store queries and their original indices
        vector<pair<int, int>> queriesWithIndices;
        for (int i = 0; i < queries.size(); ++i) {
            queriesWithIndices.push_back({queries[i], i});
        }
        
        // Sort queries by value
        sort(queriesWithIndices.begin(), queriesWithIndices.end());
        
        // Min-heap to store intervals by size
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
        
        vector<int> result(queries.size(), -1);
        int i = 0;
        
        // Iterate over each query
        for (auto& query : queriesWithIndices) {
            int q = query.first;
            int idx = query.second;
            
            // Add all intervals that start before or at the current query point
            while (i < intervals.size() && intervals[i][0] <= q) {
                int start = intervals[i][0];
                int end = intervals[i][1];
                int size = end - start + 1;
                minHeap.push({size, end});
                ++i;
            }
            
            // Remove all intervals from the heap that end before the current query point
            while (!minHeap.empty() && minHeap.top().second < q) {
                minHeap.pop();
            }
            
            // If the heap is not empty, the top element is the smallest interval containing the query
            if (!minHeap.empty()) {
                result[idx] = minHeap.top().first;
            }
        }
        
        return result;
    }
};