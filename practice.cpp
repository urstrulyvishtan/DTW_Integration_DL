#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        vector<int> pl;
        vector<int> pr;
        for(int i = 0; i<s.length(); i++){
            if(s[i]=='('){
                pl.push_back(i);
            }else if(s[i] == ')'){
                pr.push_back(i);
            }
        }
        int p1=0, r1=0, c=0;
        while(p1<pl.size()&&r1<pr.size()){
            if(pl[p1]>pr[r1]){
                s.erase(s.begin()+pr[r1]-c);
                c++;
                r1++;
            }else{
                p1++;
                r1++;
            }
        }
        while(p1<pl.size()){
            s.erase(s.begin()+pl[p1]-c);
            c++;
            p1++;
        }
        while(r1<pr.size()){
            s.erase(s.begin()+pr[r1]-c);
            c++;
            r1++;
        }
        return s;
    }
};