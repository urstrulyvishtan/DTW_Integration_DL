#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        generateParanthesisHelper(result, "", 0, 0, n);
        return result;
    }
private:
    void generateParanthesisHelper(vector<string>& result, string current, int open, int close, int n){
        if(current.length() ==  2 * n){
            result.push_back(current);
            return;
        }
        if(open<n){
            generateParanthesisHelper(result, current + '(', open + 1, close, n);
        }
        if(close<open){
            generateParanthesisHelper(result, current +')', open, close+1, n);
        }
    }
};