#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> result(n, 0);
        stack<int> stk;

        for (int i = 0; i < n; ++i) {
            while (!stk.empty() && temperatures[i] > temperatures[stk.top()]) {
                int idx = stk.top();
                stk.pop();
                result[idx] = i - idx;
            }
            stk.push(i);
        }

        return result;
    }
};