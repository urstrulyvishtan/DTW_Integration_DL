#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        if(hand.size()%groupSize != 0) return false;
        unordered_map<int, int> count;
        for(int card:hand){
            count[card]++;
        }
        sort(hand.begin(), hand.end());
        for(int card:hand){
            if(count[card]>0){
                for(int i = 0; i<groupSize; ++i){
                    if(count[card+i]<=0) return false;
                    count[card+i]--;
                }
            }
        }
        return true;
    }
};