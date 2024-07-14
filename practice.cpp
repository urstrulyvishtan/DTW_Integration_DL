#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    bool ValidSudoku(vector<vector<char>>& board) {
        std::vector<std::unordered_set<char>> rows(9), cols(9), boxes(9);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            char num = board[i][j];
            if (num != '.') {
                if (rows[i].count(num) || cols[j].count(num) || boxes[(i/3) * 3 + j/3].count(num)) {
                    return false;
                }
                rows[i].insert(num);
                cols[j].insert(num);
                boxes[(i/3) * 3 + j/3].insert(num);
            }
        }
    }
    return true;
}
};