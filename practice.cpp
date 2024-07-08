#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> inDegree(numCourses, 0);
        vector<vector<int>> adjList(numCourses);

        for(const auto& prerequisite : prerequisites){
            int course = prerequisite[0];
            int prereq = prerequisite[1];
            adjList[prereq].push_back(course);
            ++inDegree[course];
        }
        queue<int> zeroInDegreeQueue;
        for (int i = 0; i<numCourses; ++i){
            if(inDegree[i] == 0){
                zeroInDegreeQueue.push(i);
            }
        }
        int visitedCourses = 0;

        while(!zeroInDegreeQueue.empty()){
            int currentCourse = zeroInDegreeQueue.front();
            zeroInDegreeQueue.pop();
            ++visitedCourses;

            for(int nextCourse : adjList[currentCourse]){
                --inDegree[nextCourse];
                if(inDegree[nextCourse] == 0){
                    zeroInDegreeQueue.push(nextCourse);
                }
            }
        }
        return visitedCourses == numCourses;
    }
};