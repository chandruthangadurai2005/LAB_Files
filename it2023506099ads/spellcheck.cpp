#include <iostream>
#include <string>
using namespace std;


struct TrieNode {
    TrieNode* children[26]; 
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};


class Trie {
private:
    TrieNode* root;

public:
    
    Trie() {
        root = new TrieNode();
    }

    
    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (!node->children[index]) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->isEndOfWord = true;
    }

   
    bool search(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (!node->children[index]) {
                return false; 
            }
            node = node->children[index];
        }
        return node->isEndOfWord;
    }
};


int main() {
    Trie trie;
    int choice;
    string word;

    while (true) {
        cout << "\n--- Spell Check Program ---\n";
        cout << "1. Insert word into Trie\n";
        cout << "2. Search for a word\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter word to insert: ";
                cin >> word;
                trie.insert(word);
                cout << "Word '" << word << "' inserted successfully.\n";
                break;
            case 2:
                cout << "Enter word to check: ";
                cin >> word;
                if (trie.search(word)) {
                    cout << word << " is found in the dictionary.\n";
                } else {
                    cout << word << " is not found in the dictionary.\n";
                }
                break;
            case 3:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}

