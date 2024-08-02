#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for(int i = 0; i<n; ++i){
            for(int j = i+1; j<n; ++j){
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        for(int i = 0; i<n; ++i){
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
    void printMatrix(const vector<vector<int>>& matrix){
        for(const auto& row:matrix){
            for(int val:row){
                cout<<val<<" ";
            }
            cout<<endl;
        }
    }
};