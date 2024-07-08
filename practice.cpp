#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        unordered_map<int, vector<int>> graph;
        for(const auto& edge : edges){
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        unordered_set<int> visited;
        int componentCount = 0;

        for(int i=0; i<n; ++i){
            if(!visited.count(i)){
            ++componentCount;
            dfs(i, graph, visited);
        }
    }
    return componentCount;
    }
private:
    void dfs(int node, unordered_map<int, vector<int>>& graph, unordered_set<int>& visited){
        if(visited.count(node)) return;
        visited.insert(node);

        for(const int neighbor : graph[node]){
            dfs(neighbor, graph, visited);
        }
    }
};
};