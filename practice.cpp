#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class UnionFind {
public:
    vector<int> parent, rank;
    
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]);
        return parent[u];
    }
    
    bool unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        
        if (rootU == rootV) return false;
        
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
        return true;
    }
};

class Solution {
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        UnionFind aliceUF(n + 1), bobUF(n + 1);
        int removedEdges = 0, aliceEdges = 0, bobEdges = 0;
        
        // Type 3 edges (usable by both Alice and Bob)
        for (const auto& edge : edges) {
            if (edge[0] == 3) {
                bool aliceMerged = aliceUF.unionSets(edge[1], edge[2]);
                bool bobMerged = bobUF.unionSets(edge[1], edge[2]);
                if (!aliceMerged && !bobMerged) {
                    // Both Alice and Bob already connected, so this edge is redundant
                    removedEdges++;
                } else {
                    // Successful merge for both Alice and Bob
                    aliceEdges++;
                    bobEdges++;
                }
            }
        }
        
        // Type 1 edges (only Alice can use)
        for (const auto& edge : edges) {
            if (edge[0] == 1) {
                if (aliceUF.unionSets(edge[1], edge[2])) {
                    aliceEdges++;
                } else {
                    removedEdges++;
                }
            }
        }
        
        // Type 2 edges (only Bob can use)
        for (const auto& edge : edges) {
            if (edge[0] == 2) {
                if (bobUF.unionSets(edge[1], edge[2])) {
                    bobEdges++;
                } else {
                    removedEdges++;
                }
            }
        }
        
        // Check if both Alice and Bob can traverse the entire graph
        if (aliceEdges != n - 1 || bobEdges != n - 1) {
            return -1;
        }
        
        return removedEdges;
    }
};