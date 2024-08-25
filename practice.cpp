#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    string makeGood(string s) {
        std::stack<char> stack;
        for(char ch:s){
            if(!stack.empty() && ((islower(ch) && toupper(ch) == stack.top()) || (isupper(ch) && tolower(ch) == stack.top()))){
                stack.pop();
            }else{
                stack.push(ch);
            }
        }
        std::string result;
        while(!stack.empty()){
            result.push_back(stack.top());
            stack.pop();
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
};