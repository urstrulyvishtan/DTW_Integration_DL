#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        vector<vector<pair<int, double>>> graph(n);
        for(int i = 0; i<edges.size(); ++i){
            int u = edges[i][0], v=edges[i][1];
            double prob = succProb[i];
            graph[u].emplace_back(v, prob);
            graph[v].emplace_back(u, prob);
        }
        priority_queue<pair<double, int>> pq;
        pq.emplace(1.0, start);

        vector<double> probabilities(n, 0.0);
        probabilities[start] = 1.0;

        while(!pq.empty()){
            double currProb = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            if(node == end){
                return currProb;
            }
            for(auto& neighbor:graph[node]){
                int nextNode = neighbor.first;
                double edgeProb = neighbor.second;
                double newProb = currProb * edgeProb;

                if(newProb > probabilities[nextNode]){
                    probabilities[nextNode] = newProb;
                    pq.emplace(newProb, nextNode);
                }
            }
        }
        return 0.0;
    }
};