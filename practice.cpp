#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();

        vector<vector<int>> dp(m, vector<int>(n, 0));
        if (obstacleGrid[m - 1][n - 1] == 1) {
            return 0;
        }
        dp[m - 1][n - 1] = 1;
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (i == m - 1 && j == n - 1) {
                    continue;
                }
                if (obstacleGrid[i][j] == 1) {
                    dp[i][j] = 0;
                } 
                else {
                    long long ans1, ans2;
                    if (i < m - 1)
                        ans1 = dp[i + 1][j];
                    else
                        ans1 = 0;
                    if (j < n - 1)
                        ans2 = dp[i][j + 1];
                    else
                        ans2 = 0;
                    dp[i][j] = ans1 + ans2;
                }
            }
        }
        return dp[0][0];
    }
};