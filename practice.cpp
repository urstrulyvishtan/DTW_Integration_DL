#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    bool checkValidString(string s) {
        int balance = 0, n = s.size();
        for(int i = 0; i<n; ++i){
            if(s[i] == '(' || s[i] == '*'){
                ++balance;
            }else if(s[i] == ')'){
                --balance;
            }
            if(balance<0){
                return false;
            }
        }
        balance = 0;
        for(int i = n - 1; i>=0; --i){
            if(s[i] == ')' || s[i] == '*'){
                ++balance;
            }else if(s[i] == '('){
                --balance;
            }
            if(balance<0){
                return false;
            }
        }
        return true;
    }
};