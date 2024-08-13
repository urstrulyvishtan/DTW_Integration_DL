#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int minExtraChar(string s, vector<string>& dictionary) {
        unordered_set<string> dict(dictionary.begin(), dictionary.end());
        int n = s.size();
        vector<int> dp(n + 1, n); // Initialize with max value, which is the length of the string
        dp[0] = 0;
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                string substr = s.substr(j, i - j);
                if (dict.count(substr)) {
                    dp[i] = min(dp[i], dp[j]);
                } else {
                    dp[i] = min(dp[i], dp[j] + (i - j));
                }
            }
        }
        
        return dp[n];
    }
};