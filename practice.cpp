#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int lengthOfLastWord(string s) {
        int end = s.size() - 1;
        while(end>=0 && s[end] == ' '){
            end--;
        }
        int start = end;
        while(start >= 0 && s[start]!= ' '){
            start--;
        }
        return end-start;
    }
};