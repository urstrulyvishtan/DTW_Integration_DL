#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> result(n+1, 0);

        for(int i = 1; i<=n; ++i){
            result[i] = result[i>>1]+(i&1);
        }
        return result;
    }
};