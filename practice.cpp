#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
#include<unordered_set>
class LRUCache {
private:
struct Node{
    int key, value;
    Node* prev;
    Node* next;
    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr){}
};
unordered_map<int, Node*> cache;
Node* head;
Node* tail;
int capacity;
int size;

void removeNode(Node* node){
    if(node->prev) node->prev->next = node->next;
    if(node->next) node->next->prev = node->prev;
    if(node==head) head = node->next;
    if(node==tail) tail = node->prev;
}
void addNodeToFront(Node* node){
    node->next = head;
    node->prev = nullptr;
    if(head) head->prev = node;
    head = node;
    if(!tail) tail = node;
}
void moveToHead(Node* node){
    removeNode(node);
    addNodeToFront(node);
}
public:
    LRUCache(int capacity) : capacity(capacity), size(0), head(nullptr), tail(nullptr) {}
    
    int get(int key) {
        if(cache.find(key) == cache.end()) return -1;
        Node* node = cache[key];
        moveToHead(node);
        return node->value;
    }
    
    void put(int key, int value) {
        if(cache.find(key)!=cache.end()){
            Node* node = cache[key];
            node->value = value;
            moveToHead(node);
        }else{
            Node* newNode = new Node(key, value);
            if(size<capacity){
                addNodeToFront(newNode);
                cache[key] = newNode;
                size++;
            }else{
                cache.erase(tail->key);
                removeNode(tail);
                addNodeToFront(newNode);
                cache[key] = newNode;
            }
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */