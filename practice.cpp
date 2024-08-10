#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<bool> isMST(n, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
        int totalCost = 0;
        int edgeUsed = 0;
        minHeap.push({0,0});
        while(edgeUsed<n){
            auto[cost, u] = minHeap.top();
            minHeap.pop();
            if(isMST[u]) continue;
            isMST[u] = true;
            totalCost += cost;
            edgeUsed++;
            for(int v = 0; v<n; ++v){
                if(!isMST[v]){
                    int distance = abs(points[u][0] - points[v][0]) + abs(points[u][1] - points[v][1]);
                    minHeap.push({distance, v});
                }
            }
        }
        return totalCost;
    }
};