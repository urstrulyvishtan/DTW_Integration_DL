#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        unordered_map<int, vector<pair<int, int>>> graph;
        for(const auto& time:times){
            int u = time[0], v = time[1], w = time[2];
            graph[u].emplace_back(v, w);
        }
        vector<int> dist(n+1, INT_MAX);
        dist[k] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.emplace(0, k);
        while(!pq.empty()){
            auto[d, u] = pq.top();
            pq.pop();
            if(d>dist[u]) continue;
            for(const auto& [v, w]:graph[u]){
                if(dist[u]+w < dist[v]){
                    dist[v] = dist[u] + w;
                    pq.emplace(dist[v], v);
                }
            }
        }
        int maxTime = *max_element(dist.begin() + 1, dist.end());
        return maxTime == INT_MAX ? -1:maxTime;
    }
};