#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        if (edges.size()!=n-1){
            return false;
        }

        unordered_map<int, vector<int>> graph;
        for(const auto& edge : edges){
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        unordered_set<int> visited;

        if(!dfs(0,-1, graph, visited)){
            return false;
        }
        return visited.size() == n;
    }
private:
    bool dfs(int node, int parent, unordered_map<int, vector<int>>& graph, unordered_set<int>& visited){
        if(visited.count(node)){
            return false;
        }

        visited.insert(node);
        for(const int neighbor : graph[node]){
            if(neighbor!=parent){
                if(!dfs(neighbor, node, graph, visited)){
                    return false;
                }
            }
        }
        return true;
    }
};