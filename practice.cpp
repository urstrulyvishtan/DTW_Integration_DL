#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        vector<vector<int>> visited(n, vector<int>(n, 0));
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;
        pq.push({grid[0][0], {0,0}});
        visited[0][0] = 1;
        while(!pq.empty()){
            auto[time, cell] = pq.top(); pq.pop();
            int x = cell.first, y = cell.second;
            if(x==n-1&&y==n-1)return time;
            for(const auto& dir:directions){
                int nx = x+dir[0], ny = y+dir[1];
                if(nx>=0&&nx<n&&ny>=0&&ny<n&&!visited[nx][ny]){
                    visited[nx][ny] = 1;
                    pq.push({max(time, grid[nx][ny]), {nx, ny}});
                }
            }
        }
        return -1;
    }
};