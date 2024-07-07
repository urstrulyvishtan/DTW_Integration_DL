#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        unordered_map<char, vector<pair<int, int>>> mp;
        int M = board.size();
        int N = board[0].size();
        int totalCells = M*N;
        for(int i = 0; i < M; i++){
            for(int j = 0; j < N; j++){
                mp[board[i][j]].push_back({i,j});
            }
        }
        int startWithA = 0, endWithA = 0;
        for (auto word : words){
            if (word.size() > totalCells){
                continue;
            }
			if (word.front() == 'a'){
				startWithA++;
            }
			if (word.back() == 'a'){
				endWithA++;
            }
		}
        bool reverseSearch = false;
        if(startWithA > endWithA){
            reverseSearch = true;
        }
        vector<string> result;
        bool canFound;
        string wordCopy;
        for(auto word : words){
            vector<int> temp(26, 0);
            canFound = true;
            for(auto ch : word){
                temp[ch-'a']++;
                if(temp[ch-'a'] > mp[ch].size()){
                    canFound = false;
                    break;
                }
            }
            if(!canFound){
                continue;
            }
            wordCopy = word;
            if(reverseSearch){
                reverse(wordCopy.begin(), wordCopy.end());
            }
            for(auto cell : mp[wordCopy[0]]){
                if(processCell(board, cell.first, cell.second, M, N, wordCopy, 0)){
                    result.push_back(word);
                    break;
                }
            }
        }
        return result;
    }
private:
    bool processCell(vector<vector<char>>& board, int i, int j, int M, int N, const string &word, int index){
        if(index == word.size()){
            return true;
        }
        if(i < 0 || i >= board.size() || j < 0 || j >= board[0].size()){
            return false;
        }
        char ch = board[i][j];
        if(board[i][j] != word[index]){
            return false;
        }
        board[i][j] = '#';
        bool result = processCell(board, i+1, j, M, N, word, index+1) ||
        processCell(board, i, j+1, M, N, word, index+1) ||
        processCell(board, i-1, j, M, N, word, index+1) ||
        processCell(board, i, j-1, M, N, word, index+1);
        board[i][j] = ch;
        return result;
    }
};