#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class UnionFind{
private:
    vector<int> parent;
    vector<int> rank;

public:
    UnionFind(int size){
        parent.resize(size);
        rank.resize(size, 0);
        for(int i = 0; i<size; ++i){
            parent[i] = i;
        }
    }
    int find(int x){
        if(parent[x]!=x){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    bool unionSets(int x, int y){
        int rootX = find(x);
        int rootY = find(y);
        if(rootX == rootY){
            return false;
        }
        if(rank[rootX]>rank[rootY]){
            parent[rootY] = rootX;
        } else if(rank[rootX] < rank[rootY]){
            parent[rootX] = rootY;
        } else{
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return true;
    }

};
class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        UnionFind uf(n+1);
        for(const auto& edge:edges){
            if(!uf.unionSets(edge[0], edge[1])){
                return edge;
            }
        }
        return{};
    }
};

