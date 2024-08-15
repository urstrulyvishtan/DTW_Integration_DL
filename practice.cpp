#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        int n = arr.size();
        int requiredSum = threshold*k;
        int currentSum = 0;
        for(int i = 0; i<k; ++i){
            currentSum+=arr[i];
        }
        int count = 0;
        if(currentSum >= requiredSum){
            count++;
        }
        for(int i = k; i<n; ++i){
            currentSum += arr[i] - arr[i-k];
            if(currentSum >= requiredSum){
                count++;
            }
        }
        return count;
    }
};