#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) : k(k){
        for(int num : nums){
            add(num);
        }
    }
    
    int add(int val) {
        if(minHeap.size() < k){
            minHeap.push(val);
        } else if(val>minHeap.top()){
            minHeap.push(val);
            if(minHeap.size()>k){
                minHeap.pop();
            }
        }
        return minHeap.top();
    }
private:
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    int k;
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */