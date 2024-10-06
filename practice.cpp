#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        k = nums.size() - k;
        
        return quickSelect(0, nums.size()-1);
    }
    void quickSelect(l, r){
            int pivot = nums[r], p = l;
            for(int i = 0; i<r; i++){
                if(nums[i]<=pivot){
                    swap(nums[p], nums[i]);
                    p++;
                }
                swap(nums[p], nums[r]);
                if(p>k) return quickSort(l, p-1);
                elif(p<k) return quickSort(p+1, r);
                else return nums[p];
            }
        }
};