#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.empty()) return "";
        std::string prefix = strs[0];
        for(int i = 1; i<strs.size(); i++){
            while(strs[i].find(prefix)!=0){
                prefix = prefix.substr(0, prefix.size() - 1);
                if(prefix.empty()) return "";
            }
        }
        return prefix;
    }
};