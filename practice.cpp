#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        // Initialize an empty result string
        string result = "";
        
        // Two pointers to traverse both strings
        int i = 0, j = 0;
        
        // Merge the strings alternately
        while (i < word1.size() && j < word2.size()) {
            result += word1[i++];
            result += word2[j++];
        }
        
        // If there are remaining characters in word1, append them
        while (i < word1.size()) {
            result += word1[i++];
        }
        
        // If there are remaining characters in word2, append them
        while (j < word2.size()) {
            result += word2[j++];
        }
        
        return result;
    }
};