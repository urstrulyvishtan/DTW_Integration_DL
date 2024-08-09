#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class DetectSquares {
public:
    unordered_map<int, unordered_map<int, int>> points;
    DetectSquares() {
        
    }
    
    void add(vector<int> point) {
       points[point[0]][point[1]] ++;
    }
    
    int count(vector<int> point) {
        int x = point[0], y = point[1];
        int countSquares = 0;

        if(points.find(x) == points.end()) return 0;
        for(auto & [py, freq] : points[x]){
            if(py == y) continue;
            int sideLength = abs(py - y);
            if(points.find(x+sideLength) != points.end()){
                countSquares += freq*points[x+sideLength][py]*points[x+sideLength][y];
            }
            if(points.find(x-sideLength)!=points.end()){
                countSquares += freq*points[x-sideLength][py]*points[x-sideLength][y];
            }
        }
        return countSquares;
    }
};

/**
 * Your DetectSquares object will be instantiated and called as such:
 * DetectSquares* obj = new DetectSquares();
 * obj->add(point);
 * int param_2 = obj->count(point);
 */