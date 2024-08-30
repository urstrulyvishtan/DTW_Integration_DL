#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> triangle;
        if(numRows == 0){
            return triangle;
        }
        triangle.push_back({1});
        for(int i = 1; i<numRows; ++i)
        {
            vector<int> row(i+1, 1);
            for(int j = 1; j<i; ++j){
                row[j] = triangle[i-1][j-1] + triangle[i-1][j];
            }
            triangle.push_back(row);
        }
        return triangle;
    }
};