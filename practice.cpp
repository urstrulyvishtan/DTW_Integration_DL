#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        if (intervals.empty()) {
            return 0;
        }

        vector<int> startTimes, endTimes;
        for (const auto& interval : intervals) {
            startTimes.push_back(interval.start);
            endTimes.push_back(interval.end);
        }

        sort(startTimes.begin(), startTimes.end());
        sort(endTimes.begin(), endTimes.end());

        int startPointer = 0, endPointer = 0;
        int roomsNeeded = 0, maxRooms = 0;

        while (startPointer < startTimes.size()) {
            if (startTimes[startPointer] < endTimes[endPointer]) {
                roomsNeeded++;
                startPointer++;
            } else {
                roomsNeeded--;
                endPointer++;
            }
            maxRooms = max(maxRooms, roomsNeeded);
        }
        
        return maxRooms;
    }
};