#include <iostream>
#include <vector>
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

    
    void autocompleteHelper(TrieNode* node, string prefix, vector<string>& suggestions) {
        if (node->isEndOfWord) {
            suggestions.push_back(prefix);
        }

        
        for (char c = 'a'; c <= 'z'; c++) {
            if (node->children[c - 'a']) {
                autocompleteHelper(node->children[c - 'a'], prefix + c, suggestions);
            }
        }
    }

   
    void displayAllWordsHelper(TrieNode* node, string currentWord) {
        if (node->isEndOfWord) {
            cout << currentWord << endl;
        }

       
        for (char c = 'a'; c <= 'z'; c++) {
            if (node->children[c - 'a']) {
                displayAllWordsHelper(node->children[c - 'a'], currentWord + c);
            }
        }
    }

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

   
    vector<string> autocomplete(const string& prefix) {
        TrieNode* node = root;
        vector<string> suggestions;

       
        for (char c : prefix) {
            int index = c - 'a';
            if (!node->children[index]) {
                return suggestions;
            }
            node = node->children[index];
        }

       
        autocompleteHelper(node, prefix, suggestions);
        return suggestions;
    }

    
    void displayAllWords() {
        displayAllWordsHelper(root, ""); 
    }
};

int main() {
    Trie trie;
    int choice;
    string word, prefix;
    vector<string> completions;  // Declare completions vector outside the switch

    while (true) {
        cout << "\n--- Auto-Completion Program ---\n";
        cout << "1. Insert word into Trie\n";
        cout << "2. Auto-complete for a prefix\n";
        cout << "3. Display all words in the Trie\n";
        cout << "4. Exit\n";
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
                cout << "Enter prefix for auto-completion: ";
                cin >> prefix;
                completions = trie.autocomplete(prefix);  // Assign completions inside case 2
                if (completions.empty()) {
                    cout << "No completions found for prefix '" << prefix << "'\n";
                } else {
                    cout << "Auto-completion suggestions for '" << prefix << "':\n";
                    for (const string& suggestion : completions) {
                        cout << suggestion << "\n";
                    }
                }
                break;
            case 3:
                cout << "Displaying all words in the Trie:\n";
                trie.displayAllWords();
                break;
            case 4:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}

