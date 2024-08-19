#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    vector<int> parent, rank;
    
    // Union-Find "Find" operation with path compression
    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]);
        return parent[u];
    }
    
    // Union-Find "Union" operation with rank by union
    void unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
    
    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        int n = vals.size();
        parent.resize(n);
        rank.resize(n, 0);
        iota(parent.begin(), parent.end(), 0); // Initialize Union-Find
        
        // Group edges by the maximum value of the two connected nodes
        vector<vector<pair<int, int>>> adjList(n);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            adjList[u].emplace_back(v, max(vals[u], vals[v]));
            adjList[v].emplace_back(u, max(vals[u], vals[v]));
        }
        
        // Sort nodes by value with indices
        vector<pair<int, int>> nodes;
        for (int i = 0; i < n; ++i)
            nodes.emplace_back(vals[i], i);
        sort(nodes.begin(), nodes.end());
        
        int goodPaths = 0;
        
        for (int i = 0; i < n; ) {
            int value = nodes[i].first;
            vector<int> component;
            
            // Collect nodes with the same value
            while (i < n && nodes[i].first == value) {
                int u = nodes[i].second;
                component.push_back(u);
                for (auto& [v, maxVal] : adjList[u]) {
                    if (vals[v] <= vals[u])
                        unionSets(u, v);
                }
                ++i;
            }
            
            // Count nodes in each component with the same value
            unordered_map<int, int> componentCount;
            for (int u : component)
                componentCount[find(u)]++;
            
            // For each component, count the number of good paths
            for (auto& [root, count] : componentCount) {
                goodPaths += count * (count + 1) / 2; // combination of `count` nodes, including single nodes
            }
        }
        
        return goodPaths;
    }
};