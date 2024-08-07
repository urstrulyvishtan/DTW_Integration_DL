#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if(wordSet.find(endWord) == wordSet.end()){
            return 0;
        }
        queue<pair<string, int>> q;
        q.push({beginWord, 1});
        while(!q.empty()){
            auto[word, length] = q.front();
            q.pop();
            if(word == endWord){
                return length;
            }
            for(int i = 0; i<word.length(); ++i){
                string originalWord = word;
                for(char c = 'a'; c<='z'; ++c){
                    word[i] = c;
                    if(wordSet.find(word) != wordSet.end()){
                        q.push({word, length+1});
                        wordSet.erase(word);
                    }
                }
                word[i]=originalWord[i];
            }
        }
        return 0;
    }
};