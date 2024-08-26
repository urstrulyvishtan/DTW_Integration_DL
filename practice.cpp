#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    bool isPerfectSquare(int num) {
        if(num<1) return false;
        long long low = 1;
        long long high = num;
        while(low<=high){
            long long mid = low+(high-low)/2;
            long long square = mid * mid;
            if(square == num){
                return true;
            }else if(square<num){
                low = mid+1;
            }else{
                high = mid - 1;
            }
        }
        return false;
    }
};