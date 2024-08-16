#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int m = heights.size();
        int n = heights[0].size();
        vector<vector<int>> efforts(m, vector<int>(n, INT_MAX));
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
        pq.emplace(0, 0, 0);
        efforts[0][0] = 0;

        vector<int> directions = {0, 1, 0, -1, 0};
        while(!pq.empty()){
            auto[current_effort, x, y] = pq.top();
            pq.pop();
            if(x==m-1 && y == n-1){
                return current_effort;
            }
            for(int i = 0; i<4; ++i){
                int nx = x + directions[i];
                int ny = y + directions[i+1];
                if(nx>=0 && ny>=0 && nx<m && ny<n){
                    int new_effort = max(current_effort, abs(heights[nx][ny] - heights[x][y]));
                    if(new_effort < efforts[nx][ny]){
                        efforts[nx][ny] = new_effort;
                        pq.emplace(new_effort, nx, ny);
                    }
                }
            }
        }
        return 0;
    }
};