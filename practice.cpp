#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class UnionFind{
public:
    vector<int> parent, rank;
    UnionFind(int n){
        parent.resize(n);
        rank.resize(n, 0);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int u){
        if(u!=parent[u]){
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }
    bool unionSets(int u, int v){
        int rootU = find(u);
        int rootV = find(v);
        if(rootU == rootV) return false;
        if(rank[rootU]>rank[rootV]){
            parent[rootV] = rootU;
        }else if(rank[rootU]<rank[rootV]){
            parent[rootU] = rootV;
        }else{
            parent[rootV] = rootU;
            rank[rootU]++;
        }
        return true;
    }
};
class Solution {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        int m = edges.size();
        for(int i = 0; i<m; ++i){
            edges[i].push_back(i);
        }
        sort(edges.begin(), edges.end(), [](const auto& a, const auto& b){
            return a[2]<b[2];
        });
        auto kruskalMST = [&](int n, vector<vector<int>>& edges, int excludeEdge = -1, int includeEdge = -1) -> int{
            UnionFind uf(n);
            int totalWeight = 0;
            int edgesUsed = 0;
            if(includeEdge!=-1){
                uf.unionSets(edges[includeEdge][0], edges[includeEdge][1]);
                totalWeight += edges[includeEdge][2];
                edgesUsed++;
            }
            for(int i = 0; i<edges.size(); ++i){
                if(i == excludeEdge) continue;
                if(uf.unionSets(edges[i][0], edges[i][1])){
                    totalWeight += edges[i][2];
                    edgesUsed++;
                    if(edgesUsed == n-1) break;
                }
            }
            return edgesUsed == n-1?totalWeight:INT_MAX;
        };
        int originalMSTWeight = kruskalMST(n, edges);
        vector<int> criticalEdges, pseudoCriticalEdges;
        for(int i = 0; i<m; ++i){
            int mstWeightWithoutEdge = kruskalMST(n, edges, i);
            if(mstWeightWithoutEdge>originalMSTWeight){
                criticalEdges.push_back(edges[i][3]);
            }else{
                int mstWeightWithEdge = kruskalMST(n, edges, -1, i);
                if(mstWeightWithEdge == originalMSTWeight){
                    pseudoCriticalEdges.push_back(edges[i][3]);
                }
            }
        }
        return {criticalEdges, pseudoCriticalEdges};
    }
};