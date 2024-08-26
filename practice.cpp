#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int arrangeCoins(int n) {
        long left = 0, right = n;
        while(left<=right){
            long mid = left + (right - left)/2;
            long current = mid * (mid + 1)/2;
            if(current == n){
                return mid;
            }else if(current<n){
                left = mid + 1;
            }else{
                right = mid - 1;
            }
        }
        return right;
    }
};