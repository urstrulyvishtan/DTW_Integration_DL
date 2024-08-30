#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n>0 &&(n&(n-1)) == 0;
    }
};