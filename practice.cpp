#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Twitter {
private:
struct Tweet{
    int id;
    int timestamp;
    Tweet(int tweetId, int time) : id(tweetId), timestamp(time){}
};
int time;
unordered_map<int, vector<Tweet>> userTweets;
unordered_map<int, unordered_set<int>> followers;
public:
    Twitter() : time(0){
        
    }
    
    void postTweet(int userId, int tweetId) {
        userTweets[userId].emplace_back(tweetId, time++);
    }
    
    vector<int> getNewsFeed(int userId) {
        vector<int> result;
        priority_queue<pair<int, int>> maxHeap;
        for(auto& tweet : userTweets[userId]){
            maxHeap.push({tweet.timestamp, tweet.id});
        }
        for(auto& followeeId : followers[userId]){
            for(auto& tweet : userTweets[followeeId]){
                maxHeap.push({tweet.timestamp, tweet.id});
            }
        }
        int count = 0;
        while(!maxHeap.empty() && count<10){
            result.push_back(maxHeap.top().second);
            maxHeap.pop();
            count++;
        }
        return result;
    }
    
    void follow(int followerId, int followeeId) {
        if(followerId != followeeId){
            followers[followerId].insert(followeeId);
        }
    }
    
    void unfollow(int followerId, int followeeId) {
        if(followerId != followeeId){
            followers[followerId].erase(followeeId);
        }   
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */