#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class TimeMap {
private:
unordered_map<string, vector<pair<int, string>>> store;
public:
    
    void set(string key, string value, int timestamp) {
       store[key].emplace_back(timestamp, value); 
    }
    
    string get(string key, int timestamp) {
        if(store.find(key) == store.end()){
            return "";
        }
        const auto& values = store[key];
        int low = 0, high = values.size() - 1;
        while(low<=high){
            int mid = low +(high-low)/2;
            if(values[mid].first == timestamp){
                return values[mid].second;
            }
            else if(values[mid].first<timestamp){
                low = mid+1;
            }else{
                high = mid - 1;
            }
        }
        return (high>=0) ? values[high].second : "";
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */