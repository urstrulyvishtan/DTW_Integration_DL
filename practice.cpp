#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        unordered_map<string, priority_queue<string, vector<string>, greater<string>>> adj;
        vector<string> result;
        for(auto& ticket:tickets){
            adj[ticket[0]].push(ticket[1]);
        }
        dfs("JFK", adj, result);
        reverse(result.begin(), result.end());
        return result;
    }
private:
    void dfs(const string& airport, unordered_map<string, priority_queue<string, vector<string>, greater<string>>>& adj, vector<string>& result){
        auto& destinations = adj[airport];
        while(!destinations.empty()){
            string next = destinations.top();
            destinations.pop();
            dfs(next, adj, result);
        }
        result.push_back(airport);
    }
};