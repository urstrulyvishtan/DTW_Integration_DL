#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    vector<int> partitionLabels(string s) {
        unordered_map<char, int> lastOccurrence;
        for(int i = 0; i<s.size(); ++i){
            lastOccurrence[s[i]] = i;
        }
        vector<int> partitions;
        int start = 0, end =0;
        for(int i = 0; i<s.size(); ++i){
            end = max(end, lastOccurrence[s[i]]);
            if(i == end){
                partitions.push_back(end-start+1);
                start = i+1;
            }
        }
        return partitions;
    }
};