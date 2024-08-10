#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        unordered_map<int, vector<pair<int, int>>> graph;
        for(const auto& flight:flights){
            int u = flight[0], v = flight[1], w = flight[2];
            graph[u].emplace_back(v, w);
        }
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
        pq.emplace(0, src, 0);
        vector<int> dist(n, INT_MAX);
        dist[src] = 0;
        while(!pq.empty()){
            auto[cost, city, stops] = pq.top(); pq.pop();
            if(city == dst){
                return cost;
            }
            if(stops <= k){
                for(const auto& [next_city, price]:graph[city]){
                    int new_cost = cost+price;
                    if(new_cost<dist[next_city]||stops+1 <=k){
                        dist[next_city] = new_cost;
                        pq.emplace(new_cost, next_city, stops+1);
                    }
                }
            }
        }
        return -1;
    }
};