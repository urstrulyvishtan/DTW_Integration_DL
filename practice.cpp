#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if(digits.empty()) return {};
        vector<string> result;
        string currentCombination;
        unordered_map<char, string> digitToChar = {
            {'2', "abc"}, {'3', "def"}, {'4', "ghi"},
            {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"},
            {'8', "tuv"}, {'9', "wxyz"}
        };
        backtrack(digits, 0, currentCombination, result, digitToChar);
        return result;
    }
private:
    void backtrack(const string& digits, int index, string& currentCombination, vector<string>& result, const unordered_map<char, string>& digitToChar){
        if(index == digits.size()){
            result.push_back(currentCombination);
            return;
        }
        char digit = digits[index];
        const string& letters = digitToChar.at(digit);
        for(char letter:letters){
            currentCombination.push_back(letter);
            backtrack(digits, index+1, currentCombination, result, digitToChar);
            currentCombination.pop_back();
        }
    }
};