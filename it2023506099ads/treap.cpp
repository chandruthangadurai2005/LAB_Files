#include <iostream>

using namespace std;

struct TreapNode {
    int key, priority;
    TreapNode *left, *right;

    TreapNode(int key, int priority) {
        this->key = key;
        this->priority = priority;
        this->left = this->right = nullptr;
    }
};

TreapNode* rightRotate(TreapNode* y) {
    TreapNode* x = y->left;
    TreapNode* T = x->right;
    x->right = y;
    y->left = T;
    return x;
}

TreapNode* leftRotate(TreapNode* x) {
    TreapNode* y = x->right;
    TreapNode* T = y->left;
    y->left = x;
    x->right = T;
    return y;
}

TreapNode* insert(TreapNode* root, int key, int priority) {
    if (!root) return new TreapNode(key, priority);

    if (key < root->key) {
        root->left = insert(root->left, key, priority);
        if (root->left->priority > root->priority)
            root = rightRotate(root);
    } 
    else if (key > root->key) {
        root->right = insert(root->right, key, priority);
        if (root->right->priority > root->priority)
            root = leftRotate(root);
    }

    return root;
}

TreapNode* deleteNode(TreapNode* root, int key) {
    if (!root) return root;

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } 
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } 
    else {
        if (!root->left) {
            TreapNode* temp = root->right;
            delete root;
            return temp;
        } 
        else if (!root->right) {
            TreapNode* temp = root->left;
            delete root;
            return temp;
        } 
        else {
            if (root->left->priority > root->right->priority) {
                root = rightRotate(root);
                root->right = deleteNode(root->right, key);
            } 
            else {
                root = leftRotate(root);
                root->left = deleteNode(root->left, key);
            }
        }
    }
    return root;
}

bool search(TreapNode* root, int key) {
    if (!root) return false;
    if (root->key == key) return true;
    if (key < root->key) return search(root->left, key);
    return search(root->right, key);
}

void inorder(TreapNode* root) {
    if (root) {
        inorder(root->left);
        cout << "(" << root->key << ", " << root->priority << ") ";
        inorder(root->right);
    }
}

int main() {
    TreapNode* root = nullptr;
    int choice, key, priority;

    do {
        cout << "\nMenu\n";
        cout << "1. Insert\n2. Delete\n3. Search\n4. Print Inorder\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key and priority: ";
                cin >> key >> priority;
                root = insert(root, key, priority);
                break;
            case 2:
                cout << "Enter key to delete: ";
                cin >> key;
                root = deleteNode(root, key);
                break;
            case 3:
                cout << "Enter key to search: ";
                cin >> key;
                cout << (search(root, key) ? "Key Found!" : "Key Not Found!") << endl;
                break;
            case 4:
                cout << "Inorder Traversal: ";
                inorder(root);
                cout << endl;
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}

