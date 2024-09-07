#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int findMin(vector<int>& arr) {
        int lo=0,hi=arr.size()-1,min_ele=arr[0];
        while(lo<=hi){
            int mid=lo+(hi-lo)/2;
            if(arr[mid]<=arr[hi]){
                if(arr[mid]<min_ele)min_ele=arr[mid];
                hi=mid-1;
            }
            else lo=mid+1;
        }
        return min_ele;
}   
};