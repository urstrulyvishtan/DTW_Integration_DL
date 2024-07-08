#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    string foreignDictionary(vector<string>& words) {
        unordered_map<char, unordered_set<char>> graph;
        unordered_map<char, int> inDegree;
        queue<char> zeroInDegreeQueue;
        string result;

        for(const string& word: words){
            for(char c:word){
                inDegree[c] = 0;
                graph[c] = unordered_set<char>();

            }
        }
        for(int i = 0; i<words.size()-1; ++i){
            const string& word1 = words[i];
            const string& word2 = words[i+1];
            int len = min(word1.length(), word2.length());
            bool foundOrder = false;
            for(int j = 0; j<len; ++j){
                char parent = word1[j];
                char child = word2[j];
                if(parent!=child){
                    if(graph[parent].find(child) == graph[parent].end()){
                        graph[parent].insert(child);
                        ++inDegree[child];
                    }
                    foundOrder = true;
                    break;
                }
            }
            if(!foundOrder && word1.length() > word2.length()){
                return "";
            }
        }

        for(const auto& entry : inDegree){
            if(entry.second == 0){
                zeroInDegreeQueue.push(entry.first);
            }
        }
        while(!zeroInDegreeQueue.empty()){
            char current = zeroInDegreeQueue.front();
            zeroInDegreeQueue.pop();
            result += current;
            for(char neighbor : graph[current]){
                --inDegree[neighbor];
                if(inDegree[neighbor] == 0){
                    zeroInDegreeQueue.push(neighbor);
                }
            }
        }
        if(result.length()!=inDegree.size()){
            return "";
        }
        return result;
    }
};
