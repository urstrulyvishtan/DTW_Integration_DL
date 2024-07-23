#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> stk;
        int maxArea = 0;
        int index = 0;

        while(index<heights.size()){
            if(stk.empty() || heights[index] >= heights[stk.top()]){
                stk.push(index++);
            }else{
                int topOfStack = stk.top();
                stk.pop();
                int area = heights[topOfStack] *(stk.empty() ? index: index - stk.top() - 1);
                maxArea = max(maxArea, area);
            }
        }
        while(!stk.empty()){
            int topOfStack = stk.top();
            stk.pop();
            int area = heights[topOfStack] * (stk.empty() ? index : index - stk.top() - 1);
            maxArea = max(maxArea, area);
        }
        return maxArea;
    }
};