#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class MinStack {
    private:
        stack<int> mainStack;
        stack<int> minStack;
public:
    MinStack() {
        minStack.push(INT_MAX);
    }
    
    void push(int val) {
        mainStack.push(val);
        if(val<=minStack.top()){
            minStack.push(val);
        }
    }
    
    void pop() {
        if(mainStack.empty()) return;
        int top = mainStack.top();
        mainStack.pop();
        if(top == minStack.top()){
            minStack.pop();
        }
    }
    
    int top() {
        if(mainStack.empty()) throw runtime_error("Stack is empty");
        return mainStack.top();
    }
    
    int getMin() {
        if(minStack.empty()) throw runtime_error("Stack is empty");
        return minStack.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */