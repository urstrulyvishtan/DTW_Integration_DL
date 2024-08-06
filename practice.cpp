#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> result;
        vector<string> board(n, string(n, '.')); // Create an empty board
        backtrack(result, board, 0, n);
        return result;
    }

private:
    void backtrack(vector<vector<string>>& result, vector<string>& board, int row, int n) {
        if (row == n) {
            result.push_back(board);
            return;
        }
        for (int col = 0; col < n; ++col) {
            if (isSafe(board, row, col, n)) {
                board[row][col] = 'Q'; // Place the queen
                backtrack(result, board, row + 1, n);
                board[row][col] = '.'; // Remove the queen (backtrack)
            }
        }
    }

    bool isSafe(vector<string>& board, int row, int col, int n) {
        // Check column
        for (int i = 0; i < row; ++i) {
            if (board[i][col] == 'Q') {
                return false;
            }
        }
        // Check diagonal (top-left to bottom-right)
        for (int i = row, j = col; i >= 0 && j >= 0; --i, --j) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }
        // Check diagonal (top-right to bottom-left)
        for (int i = row, j = col; i >= 0 && j < n; --i, ++j) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }
        return true;
    }
};