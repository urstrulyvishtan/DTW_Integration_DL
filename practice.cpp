#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> stk;
        for(const string& token:tokens){
            if(isOperand(token)){
                stk.push(stoi(token));
            }else{
                int right = stk.top(); stk.pop();
                int left = stk.top(); stk.pop();
                stk.push(performOperation(left, right, token));
            }
        }
        return stk.top();
    }
    private:
    bool isOperand(const string& token){
        return !token.empty() && (isdigit(token[0]) || (token.size()>1 && token[0] == '-' && isdigit(token[1])));
    }
    int performOperation(int left, int right, const string& op){
        if(op == "+") return left+right;
        if(op == "-") return left-right;
        if(op == "*") return left*right;
        if(op == "/") return left/right;
        throw invalid_argument("Invalid operator");
    }
};