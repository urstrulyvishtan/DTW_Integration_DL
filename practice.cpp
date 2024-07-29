#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        std::priority_queue<int> maxHeap(stones.begin(), stones.end());
        while(maxHeap.size() > 1){
            int first = maxHeap.top(); maxHeap.pop();
            int second = maxHeap.top(); maxHeap.pop();

            if(first!=second){
                maxHeap.push(first - second);
            }
        }
        return maxHeap.empty() ? 0:maxHeap.top();
    }
};