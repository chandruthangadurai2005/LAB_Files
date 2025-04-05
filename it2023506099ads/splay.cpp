#include <iostream>
using namespace std;

// Global counters for amortized cost analysis
int totalOperations = 0;
int totalRotations = 0;

// Node structure
struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

// Right rotation (Zig rotation)
Node* rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    totalRotations++;  // Increment the rotation counter
    return y;
}

// Left rotation (Zag rotation)
Node* leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    totalRotations++;  // Increment the rotation counter
    return y;
}

// Splay operation (Moves key to root)
Node* splay(Node* root, int key) {
    if (!root || root->key == key) return root;

    // Key in left subtree
    if (key < root->key) {
        if (!root->left) return root;

        // Zig-Zig (Left Left)
        if (key < root->left->key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        // Zig-Zag (Left Right)
        else if (key > root->left->key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right) root->left = leftRotate(root->left);
        }

        return (root->left) ? rightRotate(root) : root;
    } 
    
    // Key in right subtree
    else {
        if (!root->right) return root;

        // Zag-Zig (Right Left)
        if (key < root->right->key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left) root->right = rightRotate(root->right);
        }
        // Zag-Zag (Right Right)
        else if (key > root->right->key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }

        return (root->right) ? leftRotate(root) : root;
    }
}

// Insert operation
Node* insert(Node* root, int key) {
    totalOperations++;  // Increment the operation counter
    if (!root) return new Node(key);

    root = splay(root, key);
    if (root->key == key) return root;  // Key already exists

    Node* newNode = new Node(key);
    if (key < root->key) {
        newNode->right = root;
        newNode->left = root->left;
        root->left = nullptr;
    } else {
        newNode->left = root;
        newNode->right = root->right;
        root->right = nullptr;
    }

    return newNode;
}

// Delete operation
Node* deleteNode(Node* root, int key) {
    totalOperations++;  // Increment the operation counter
    if (!root) return nullptr;

    root = splay(root, key);

    if (root->key != key) return root;  // Key not found

    if (!root->left) {
        Node* temp = root->right;
        delete root;
        return temp;
    } 
    else {
        Node* temp = root->left;
        temp = splay(temp, key);
        temp->right = root->right;
        delete root;
        return temp;
    }
}

// Search operation
bool search(Node*& root, int key) {
    totalOperations++;  // Increment the operation counter
    root = splay(root, key);
    return root && root->key == key;
}

// Inorder traversal (sorted order)
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

// Print amortized cost analysis
void printAmortizedCostAnalysis() {
    if (totalOperations > 0) {
        cout << "--- Amortized Cost Analysis ---\n";
        cout << "Total number of operations: " << totalOperations << endl;
        cout << "Total number of rotations: " << totalRotations << endl;
        cout << "Average rotations per operation: " << (double)totalRotations / totalOperations << endl;
    }
}

// Menu-driven program
int main() {
    Node* root = nullptr;
    int choice, key;

    while (true) {
        cout << "\n--- Splay Tree Operations ---";
        cout << "\n1. Insert";
        cout << "\n2. Delete";
        cout << "\n3. Search";
        cout << "\n4. Display (Inorder)";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                root = insert(root, key);
                cout << "Inserted " << key << " successfully.\n";
                break;
            case 2:
                cout << "Enter key to delete: ";
                cin >> key;
                root = deleteNode(root, key);
                cout << "Deleted " << key << " successfully.\n";
                break;
            case 3:
                cout << "Enter key to search: ";
                cin >> key;
                if (search(root, key))
                    cout << key << " found in the tree.\n";
                else
                    cout << key << " not found.\n";
                break;
            case 4:
                cout << "Tree (Inorder): ";
                inorder(root);
                cout << endl;
                break;
            case 5:
                cout << "Exiting...\n";
                printAmortizedCostAnalysis();
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}

