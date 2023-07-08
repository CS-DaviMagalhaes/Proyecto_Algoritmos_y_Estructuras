#ifndef PATRICIATRIE_H
#define PATRICIATRIE_H
#include <iostream>
#include <list>
#include <map>
#include "trie.h"
using namespace std;

class TriePatricia : public Trie{
private:
    struct TrieNode{     
        // opcion 1:   TrieNode **children;           
        // opcion 2:   list<pair<char, TrieNode*>> children;        
        // opcion 3:   map<pair<char, TrieNode*>> children;       
        TrieNode **children;           
        string preffix;
        bool endWord; //indica si es final de una palabra
        TrieNode(string preffi){
            endWord = false;
            children = new TrieNode*[ALPHA_SIZE];
            for(int i=0;i<ALPHA_SIZE;i++)
                children[i] = nullptr;
            preffix = preffi;
        }
        TrieNode();
        ~TrieNode() {
            deleteChildren(children);
        }

        void deleteChildren(TrieNode** children) {
            for (int i = 0; i < ALPHA_SIZE; i++) {
                if (children[i] != nullptr) {
                    delete children[i];
                }
            }
            delete[] children;
        }
    };
    TrieNode* root;
    
public:
    TriePatricia(): root(nullptr) {}

    void insert(string key){
        if (root == nullptr) {
            root = new TrieNode("");
        }

        TrieNode* current = root;
        
        for (char c : key) {
            int index = c - 'a';
            if (current->children[index] == nullptr) {
                current->children[index] = new TrieNode(current->preffix + c);
            }            
            current = current->children[index];
        }        
        current->endWord = true;
    }
    
    bool search(string key){
        TrieNode* temp = root;
        int i = 0;
        while (i < key.size()) {
            char letter = key[i];
            if (temp->children[letter - 'a'] == nullptr)
                return false;
            temp = temp->children[letter - 'a'];
            i++;
        }
        if (temp->endWord == true && temp != nullptr)
            return true;
        return false;
    }
    
    void remove(string key) override {
        if (root == nullptr){
            return;}
        bool status = false;
        remove_recursivehelper(root, key, status);
    }

    void remove_recursivehelper(TrieNode* &node, string key, bool &status) {
        if (key.empty()) {
            int ctndhijos = 0;
            for (int i = 0; i < ALPHA_SIZE; i++) {
                if (node->children[i] != nullptr) ctndhijos++;
            }
            if (!ctndhijos) {
                delete node;
                node = nullptr;
            }
            else if (!status) {
                node->endWord = false;
                status = true;
            }
        }
        else if (node != nullptr && node->children[key[0] - 'a'] != nullptr) {
            string new_key = key.substr(1);
            remove_recursivehelper(node->children[key[0] - 'a'], new_key, status);
        }
    }

    void toString_recursive(TrieNode* node, string& result, string sep){
        if(node == nullptr)
            return;
        if(node->endWord){
            result += node-> preffix +sep;
        }
        for(int i=0; i < ALPHA_SIZE; i++){
            if(node->children[i] != nullptr)
                toString_recursive(node->children[i], result, sep);
        }
    }

    string toString(string sep){
        string result;
        toString_recursive(root, result, sep);
        return result;
    }

};

#endif // PATRICIATRIE_H
