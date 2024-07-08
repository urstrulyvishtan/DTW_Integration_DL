#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class Node{
    public:
        int val;
        vector<Node*> neighbors;
        Node() : val(0), neighbors(vector<Node*>()){}
        Node(int _val) : val(_val), neighbors(vector<Node*>()){}
        Node(int _val, vector<Node*> _neighbors) : val(_val), neighbors(_neighbors){}
};
class Solution {    
public:
    Node* cloneGraph(Node* node){
        if (node == nullptr) return nullptr;

        unordered_map<Node*, Node*> visited;
        return clodeNode(node, visited);
    }

private:
    Node* cloneNode(Node* node, unordered_map<Node*, Node*>& visited){
        if(visited.find(node)!=visited.end()){
            return visited[node];
        }

        Node* clone = new Node(node->val);
        visited[node] = clone;

        for(Node* neighbor : node->neighbors){
            clone->neighbors.push_back(cloneNode(neighbor, visited));
        }
        return clone;
    }

};

void printGraph(Node* node, unordered_map<Node*, bool>& visited){
    if(node == nullptr) return;
    visited[node] == true;
    cout << "Node" << node->val << ":";
    for(Node* neighbor : node->neighbors){
        cout<<neighbor->val<<" ";
    }
    cout<<endl;
    for(Node* neighbor : node->neighbors){
        printGraph(neighbor, visited);
    }
}