#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int calPoints(vector<string>& ops) {
        vector<int> scores;
        for(const string& op:ops){
            if(op=="C"){
                scores.pop_back();
            }else if(op=="D"){
                scores.push_back(2*scores.back());
            }else if(op=="+"){
                scores.push_back(scores.back()+scores[scores.size()-2]);
            }else{
                scores.push_back(stoi(op));
            }
        }
        int totalScore = 0;
        for(int score:scores){
            totalScore+=score;
        }
        return totalScore;
    }
};