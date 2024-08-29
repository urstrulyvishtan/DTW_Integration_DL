#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    string maximumOddBinaryNumber(string s) {
        int countOnes = count(s.begin(), s.end(), '1');
        int countZeros = s.size() - countOnes;
        string result(countOnes - 1, '1');
        result += string(countZeros, '0');
        result += '1';
        return result;
    }
};