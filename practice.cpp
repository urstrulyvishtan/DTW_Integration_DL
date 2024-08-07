#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        if(grid.empty()) return 0;
        int m = grid.size();
        int n = grid[0].size();
        queue<pair<int, int>> q;
        int freshOranges = 0;
        for(int i = 0; i<m; ++i){
            for(int j = 0; j<n; ++j){
                if(grid[i][j] == 2){
                    q.push({i, j});
                }else if (grid[i][j] == 1){
                    freshOranges++;
                }
            }
        }
        if(freshOranges == 0) return 0;
        vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int minutes = 0;
        while(!q.empty()){
            int size = q.size();
            bool rottedAny = false;
            for(int i = 0; i<size; ++i){
                auto[row, col] = q.front();
                q.pop();
                for(const auto& direction:directions){
                    int newRow = row+direction[0];
                    int newCol = col+direction[1];
                    if(newRow<0||newRow>=m||newCol<0||newCol>=n||grid[newRow][newCol] != 1){
                        continue;
                    }
                    grid[newRow][newCol] = 2;
                    q.push({newRow, newCol});
                    freshOranges--;
                    rottedAny = true;
                }
            }
            if(rottedAny){
                minutes++;
            }

        }
        return freshOranges == 0?minutes : -1;
    }
};