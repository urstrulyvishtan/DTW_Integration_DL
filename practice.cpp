#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        int shift = 0;
        
        // Find the common prefix of left and right
        while (left < right) {
            left >>= 1;
            right >>= 1;
            shift++;
        }
        
        // Shift the common prefix back to its original position
        return left << shift;
    }
};