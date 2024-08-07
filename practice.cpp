#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int maxArea = 0;
        for(int i = 0; i<grid.size(); ++i){
            for(int j = 0; j<grid[0].size(); ++j){
                if(grid[i][j] == 1){
                    int area = dfs(grid, i, j);
                    maxArea = max(maxArea, area);
                }
            }
        }
        return maxArea;
    }
private:
    int dfs(vector<vector<int>>& grid, int i, int j){
        if(i<0||i>=grid.size()||j<0||j>=grid[0].size()||grid[i][j] == 0){
            return 0;
        }
        grid[i][j] = 0;
        int area = 1;
        area += dfs(grid, i+1, j);
        area += dfs(grid, i-1, j);
        area += dfs(grid, i, j+1);
        area += dfs(grid, i, j-1);
        return area;
    }
};