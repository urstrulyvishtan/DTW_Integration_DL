#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        // Sort meetings by start time
        sort(meetings.begin(), meetings.end());
        
        // Priority queue to manage available rooms by room number
        priority_queue<int, vector<int>, greater<int>> availableRooms;
        for (int i = 0; i < n; ++i) {
            availableRooms.push(i);
        }
        
        // Priority queue to manage ongoing meetings by their end time
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> occupiedRooms;
        
        // Vector to keep track of the count of meetings for each room
        vector<int> meetingCount(n, 0);
        
        for (const auto& meeting : meetings) {
            int start = meeting[0];
            int end = meeting[1];
            
            // Free up rooms that have completed their meetings
            while (!occupiedRooms.empty() && occupiedRooms.top().first <= start) {
                availableRooms.push(occupiedRooms.top().second);
                occupiedRooms.pop();
            }
            
            // If there's a room available, assign it to the current meeting
            if (!availableRooms.empty()) {
                int room = availableRooms.top();
                availableRooms.pop();
                meetingCount[room]++;
                occupiedRooms.push({end, room});
            } else {
                // If no room is available, delay the meeting
                auto [nextFreeTime, room] = occupiedRooms.top();
                occupiedRooms.pop();
                meetingCount[room]++;
                occupiedRooms.push({nextFreeTime + (end - start), room});
            }
        }
        
        // Find the room with the most meetings
        int maxMeetings = 0;
        int bestRoom = 0;
        for (int i = 0; i < n; ++i) {
            if (meetingCount[i] > maxMeetings) {
                maxMeetings = meetingCount[i];
                bestRoom = i;
            }
        }
        
        return bestRoom;
    }
};