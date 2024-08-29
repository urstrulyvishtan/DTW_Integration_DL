#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int maxDepth(string s) {
        int depth = 0;
        int maxDepth = 0;
        for(char c:s){
            if(c=='('){
                depth++;
                maxDepth = max(maxDepth, depth);
            }else if(c==')'){
                depth--;
            }
        }
        return maxDepth;
    }
};