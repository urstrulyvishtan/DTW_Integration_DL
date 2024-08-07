#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    void islandsAndTreasure(vector<vector<int>>& grid) {
        if(rooms.empty()) return;

        int m = rooms.size();
        int n = rooms[0].size();
        queue<pair<int, int>> q;

        for(int i = 0; i<m; ++i){
            for(int j = 0; j<n; ++j){
                if(rooms[i][j] == 0){
                    q.push({i, j});
                }
            }
        }
        vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while(!q.empty()){
            auto [row, col] = q.front();
            q.pop();
            for(const auto& direction:directions){
                int newRow = row+direction[0];
                int newCol = col+direction[1];
                if(newRow<0 ||newRow>=m ||newCol<0 ||newCol>=n ||rooms[newRow][newCol]!=INT_MAX){
                    continue;
                }
                rooms[newRow][newCol] = rooms[row][col] + 1;
                q.push({newRow, newCol});
            }
        }
    }
};
