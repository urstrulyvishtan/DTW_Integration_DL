#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n=cardPoints.size();
        int sum=0;
        for(int i=0;i<n;i++)
        sum+=cardPoints[i];
        int m=n-k;
        int ans=0,final_ans=INT_MAX;
        int start=0;
        for(int i=0;i<n;i++){
            ans+=cardPoints[i];
            if(i-start+1==m){
                final_ans=min(final_ans,ans);
                ans-=cardPoints[start];
                start++;
            }
        }
        return final_ans==INT_MAX ? sum : sum-final_ans;
    }
};