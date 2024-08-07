#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> inDegree(numCourses, 0);
        for(auto& pre:prerequisites){
            int course = pre[0];
            int prerequisite = pre[1];
            graph[prerequisite].push_back(course);
            inDegree[course]++;
        }
        queue<int> q;
        for(int i = 0; i<numCourses; i++){
            if(inDegree[i] == 0){
                q.push(i);
            }
        }
        vector<int> order;
        while(!q.empty()){
            int current = q.front();
            q.pop();
            order.push_back(current);
            for(int neighbor : graph[current]){
                inDegree[neighbor]--;
                if(inDegree[neighbor] == 0){
                    q.push(neighbor);
                }
            }
        }
        if(order.size() == numCourses){
            return order;
        } else{
            return {};        }
    }
};