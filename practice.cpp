#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<unordered_map>
class TrieNode{
    public:
        std::unordered_map<char, TrieNode*> children;
        bool isEndOfWord;

        TrieNode() : isEndOfWord(false){}
};

class Trie{
    private: 
        TrieNode* root;

        void clear(TrieNode* node){
            for(auto& pair: node->children){
                clear(pair.second);
            }
            delete node;
        }
    
    public:
        Trie(){
            root = new TrieNode();
        }

        void insert(const std::string& word){
            TrieNode* node = root;
            for(char c : word){
                if(node->children.find(c) == node->children.end()){
                    node->children[c] = new TrieNode();

                }
                node = node -> children[c];
            
            }
            node->isEndOfWord = true;

        }
        bool search(const std::string& word){
            TrieNode* node = root;
            for(char c: word){
                if(node->children.find(c) == node->children.end()){
                    return false;
                }
                node = node->children[c];
            }
            return node->isEndOfWord;
        }
        bool startsWith(const std::string& prefix){
            TrieNode* node = root;
            for (char c:prefix){
                if(node->children.find(c) == node->children.end()){
                    return false;
    
                }
                node = node->children[c];

            }
            return true;
        }
        ~Trie(){
            clear(root);
        }


};