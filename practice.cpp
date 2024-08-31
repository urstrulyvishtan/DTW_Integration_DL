#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    bool validPalindrome(string s) {
        int left = 0, right = s.size()-1;
        while(left<right){
            if(s[left]!=s[right]){
                return isPalindrome(s, left+1, right)||isPalindrome(s, left, right-1);
            }
            left++;
            right--;
        }
        return true;
    }
private:
    bool isPalindrome(const std::string& s, int left, int right){
        while(left<right){
            if(s[left]!=s[right]) return false;
            left++;
            right--;
        }
        return true;
    }
};