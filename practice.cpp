#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<char, int> taskCounts;
        for(char task:tasks){
            taskCounts[task]++;
        }
        priority_queue<int> maxHeap;
        for(auto& pair : taskCounts){
            maxHeap.push(pair.second);
        }
        int time = 0;
        queue<pair<int, int>> cooldownQueue;
        while(!maxHeap.empty() || !cooldownQueue.empty()){
            time++;
            if(!maxHeap.empty()){
                int currentTaskCount = maxHeap.top();
                maxHeap.pop();
                currentTaskCount--;
                if(currentTaskCount>0){
                    cooldownQueue.push({currentTaskCount, time+n});
                }
            }
            if(!cooldownQueue.empty() && cooldownQueue.front().second == time){
                maxHeap.push(cooldownQueue.front().first);
                cooldownQueue.pop();
            }
        }
        return time;
    }
};