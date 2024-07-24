#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty() || matrix[0].empty()) return false;

        int m = matrix.size();
        int n = matrix[0].size();
        int low = 0, high = m*n-1;
        while(low<=high){
            int mid = low+(high-low)/2;
            int midValue = matrix[mid/n][mid%n];
            if(midValue == target){
                return true;
            } else if(midValue<target){
                low = mid+1;
            }else{
                high = mid-1;
            }
        }
        return false;
    }
};