#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int numIslands(std::vector<std::vector<char>>& grid ){
        if(grid.empty()){
            return 0;
        }
        int num_islands = 0;
        int rows = grid.size();
        int cols = grid[0].size();

        for (int i= 0; i<rows; ++i){
            for(int j=0; j<cols; ++j){
                if(grid[i][j] == '1'){
                    ++num_islands;
                    dfs(grid, i, j);
                }
            }
        }
        return num_islands;
    }
    private:
        void dfs(std::vector<std::vector<char>>& grid, int i, int j){
            if(i<0 ||j<0||i>=grid.size()||grid[i][j] == '0'){
                return;
            }
            grid[i][j] = '0';
            dfs(grid, i-1, j);
            dfs(grid, i+1, j);
            dfs(grid, i, j-1);
            dfs(grid, i, j+1);
        }

};