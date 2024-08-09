#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Solution {
public:
    bool isHappy(int n) {
        std::unordered_set<int> seen;
        
        while (n != 1 && seen.find(n) == seen.end()) {
            seen.insert(n);
            n = getNext(n);
        }
        
        return n == 1;
    }
    
private:
    int getNext(int n) {
        int totalSum = 0;
        while (n > 0) {
            int digit = n % 10;
            totalSum += digit * digit;
            n /= 10;
        }
        return totalSum;
    }
};