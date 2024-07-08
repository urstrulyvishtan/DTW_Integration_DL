#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix) {
        vector<vector<int>> result;
        if (matrix.empty() || matrix[0].empty()) return result;

        int rows = matrix.size();
        int cols = matrix[0].size();

        vector<vector<bool>> pacific(rows, vector<bool>(cols, false));
        vector<vector<bool>> atlantic(rows, vector<bool>(cols, false));

        // Perform DFS from the edges of the grid
        for (int i = 0; i < rows; ++i) {
            dfs(matrix, pacific, i, 0);
            dfs(matrix, atlantic, i, cols - 1);
        }

        for (int j = 0; j < cols; ++j) {
            dfs(matrix, pacific, 0, j);
            dfs(matrix, atlantic, rows - 1, j);
        }

        // Collect cells that can reach both oceans
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (pacific[i][j] && atlantic[i][j]) {
                    result.push_back({i, j});
                }
            }
        }

        return result;
    }

private:
    void dfs(vector<vector<int>>& matrix, vector<vector<bool>>& visited, int row, int col) {
        static vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int rows = matrix.size();
        int cols = matrix[0].size();
        
        visited[row][col] = true;

        for (const auto& dir : directions) {
            int newRow = row + dir.first;
            int newCol = col + dir.second;

            if (newRow < 0 || newRow >= rows || newCol < 0 || newCol >= cols || visited[newRow][newCol] || matrix[newRow][newCol] < matrix[row][col]) {
                continue;
            }

            dfs(matrix, visited, newRow, newCol);
        }
    }
};