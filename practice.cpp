#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int nRows = grid.size();
        int nCols = grid[0].size();
        vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        queue<pair<int, int>> thievesGrids;
        for (int row = 0; row < nRows; row++) {
            for (int col = 0; col < nCols; col++) {
                if (grid[row][col] == 1) {
                    thievesGrids.emplace(row, col);
                    grid[row][col] = 0;  // Mark thief cell with 0
                } else {
                    grid[row][col] = -1; // Mark empty cell with -1
                }
            }
        }

        bfs(grid, thievesGrids, nRows, nCols, directions);
        return calculateSafeness(grid, nRows, nCols, directions);
    }

private:
    void bfs(vector<vector<int>>& grid, queue<pair<int, int>>& thievesGrids, int nRows, int nCols, const vector<pair<int, int>>& directions) {
        while (!thievesGrids.empty()) {
            auto [row, col] = thievesGrids.front();
            thievesGrids.pop();
            int value = grid[row][col];

            for (const auto& direction : directions) {
                int newRow = row + direction.first;
                int newCol = col + direction.second;
                if (inBound(newRow, newCol, nRows, nCols) && grid[newRow][newCol] == -1) {
                    grid[newRow][newCol] = value + 1;
                    thievesGrids.emplace(newRow, newCol);
                }
            }
        }
    }

    int calculateSafeness(vector<vector<int>>& grid, int nRows, int nCols, const vector<pair<int, int>>& directions) {
        priority_queue<tuple<int, int, int>> priorityQueue;
        priorityQueue.emplace(grid[0][0], 0, 0);
        vector<vector<bool>> visited(nRows, vector<bool>(nCols, false));
        visited[0][0] = true;

        while (!priorityQueue.empty()) {
            auto [safeness, row, col] = priorityQueue.top();
            priorityQueue.pop();

            if (row == nRows - 1 && col == nCols - 1) {
                return safeness;
            }

            for (const auto& direction : directions) {
                int newRow = row + direction.first;
                int newCol = col + direction.second;
                if (inBound(newRow, newCol, nRows, nCols) && !visited[newRow][newCol]) {
                    visited[newRow][newCol] = true;
                    priorityQueue.emplace(min(safeness, grid[newRow][newCol]), newRow, newCol);
                }
            }
        }

        return -1;
    }

    bool inBound(int row, int col, int nRows, int nCols) {
        return 0 <= row && row < nRows && 0 <= col && col < nCols;
    }
};