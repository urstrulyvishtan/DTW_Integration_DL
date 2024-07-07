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

class WordDicitionary{
    private:
        TrieNode* root;
    
    public:
        WordDicitionary(){
            root = new TrieNode();
        }

        void addWord(const std::string& word){
            TrieNode* node = root;
            for(char c: word){
                if(node->children.find(c) == node->children.end()){
                    node->children[c] = new TrieNode();
                }
                node = node->children[c];
            }
            node->isEndOfWord = true;
        }

        bool search(const std::string& word)
        {
            return searchHelper(word, 0, root);
        }

        ~WordDicitionary(){
            clear(root);
        }
    private:
        bool searchHelper(const std::string& word, int index, TrieNode* node){
            if (node == nullptr) {
                return false;
            }
            if (index == word.size()) {
                return node->isEndOfWord;
            }
            char c = word[index];
            if (c == '.') {
                for (auto& child : node->children) {
                    if (searchHelper(word, index + 1, child.second)) {
                        return true;
                    }
                }
                return false;
            } else {
                if (node->children.find(c) == node->children.end()) {
                    return false;
                }
                return searchHelper(word, index + 1, node->children[c]);
            }
        }

        void clear(TrieNode* node){
            for(auto& pair: node->children){
                clear(pair.second);
            }
            delete node;
        }
};