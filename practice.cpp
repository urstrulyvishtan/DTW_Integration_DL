#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        vector<pair<double, int>> cars(n);
        for(int i = 0; i<n; ++i){
            double time = (double)(target-position[i]) / speed[i];
            cars[i] = {time, position[i]};
        }
        sort(cars.begin(), cars.end(), [](const pair<double, int>& a, const pair<double, int>& b){
            return a.second>b.second;
        });
        int fleets = 0;
        double currentFleetTime = 0;
        for(const auto& car:cars){
            if(car.first>currentFleetTime){
                ++fleets;
                currentFleetTime = car.first;
            }
        }
        return fleets;
    }
};