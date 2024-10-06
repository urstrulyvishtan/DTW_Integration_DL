#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
vector<int> g;
    Solution(vector<int>& w) {
        g.resize(w.size());
        for(int i = 0; i<w.size(); i++){
            if(i == 0){
                g[i] = w[i];
                continue;
            } g[i] = g[i-1]+w[i];
        }
    }
    
    int pickIndex() {
        // random number from 0, w.length-1
        int rand_i = rand()%g.back();
        int index = upper_bound(g.begin(), g.end(), rand_i)-g.begin();
        return index;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */