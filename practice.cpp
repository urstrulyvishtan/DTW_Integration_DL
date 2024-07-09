#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        vector<bool> dp(n+1, false);
        
        dp[0] = true;
        int max_len = 0;
        for(auto i: wordDict) if(i.length() > max_len) max_len = i.length();

        for(int i=1; i<=n; i++) {
            for(int j=i-1; j>=max(i-max_len-1, 0); j--){
                if(dp[j] && find(wordDict.begin(), wordDict.end(), s.substr(j, i-j)) != wordDict.end()){
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n];
    }
};