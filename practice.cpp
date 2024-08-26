#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int mySqrt(int x) {
        if(x<2) return x;
        long low = 1;
        long high = x;
        int result = 0;
        while(low<=high){
            long mid = low+(high-low)/2;
            long square = mid*mid;
            if(square == x){
                return mid;
            }else if(square<x){
                result = mid;
                low = mid + 1;
            }else{
                high = mid - 1;
            }
        }
        return result;
    }
};