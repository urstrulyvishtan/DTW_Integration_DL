#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    char findTheDifference(string s, string t) {
        char result = 0;
        for(char c:s){
            result^=c;
        }
        for(char c:t){
            result^=c;
        }
        return result;
    }
};