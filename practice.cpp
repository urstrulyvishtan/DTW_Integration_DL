#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int low = 1;
        int high = *max_element(piles.begin(), piles.end());
        while(low<high){
            int mid = low + (high-low)/2;
            if(canFinish(piles, mid, h)){
                high = mid;
            } else{
                low = mid+1;
            }
        }
        return low;
    }
    bool canFinish(const vector<int>& piles, int k, int h){
        int hours = 0;
        for(int pile:piles){
            hours+=ceil((double)pile/k);
        }
        return hours<=h;
    }
};