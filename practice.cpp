#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        vector<pair<int,int>>adj[n];
        for(auto it:flights)
        {
            adj[it[0]].push_back({it[1],it[2]});
        }
        queue<pair<int,pair<int,int>>>q;
            // {stops, {node, distance}}
        q.push({0,{src,0}});
        vector<int>dist(n,INT_MAX);
        dist[src]=0;
        while(!q.empty())
        {
            auto it=q.front();
            q.pop();
            int stops=it.first;
            int node=it.second.first;
            int weight=it.second.second;
            if(stops>K)
                continue;
            for(auto i:adj[node])
            {
                int adjNode=i.first;
                int adjWt=i.second;
                if(weight+adjWt<dist[adjNode])
                {
                    q.push({stops+1,{adjNode,weight+adjWt}});
                    dist[adjNode]=weight+adjWt;
                }
            }
        }
            // destination do not reached under k stops
        if(dist[dst]==INT_MAX)
            return -1;
        return dist[dst];
    }
};