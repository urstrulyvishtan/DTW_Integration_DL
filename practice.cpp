#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class SummaryRanges {
private:
    std::set<std::pair<int, int>> intervals;
public:
    SummaryRanges() {
        
    }
    
    void addNum(int val) {
        auto it = intervals.lower_bound({val, val});
        if(it != intervals.begin() && std::prev(it)->second + 1 >= val){
            --it;
        }
        int start = val, end = val;
        while(it != intervals.end() && it->first <= end+1){
            start = std::min(start, it->first);
            end = std::max(end, it->second);
            it = intervals.erase(it);
        }
        intervals.insert({start, end});
    }
    std::vector<std::vector<int>> getIntervals(){
        std::vector<std::vector<int>> result;
        for(const auto& interval:intervals){
            result.push_back({interval.first, interval.second});
        }
        return result;
    }
    
    
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(value);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */