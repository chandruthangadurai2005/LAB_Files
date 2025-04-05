#include <iostream>
#include <algorithm>

template <typename T>
class LeftistHeap {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int npl;

        Node(T val) : data(val), left(nullptr), right(nullptr), npl(0) {}
    };

    Node* root;

    Node* merge(Node* h1, Node* h2) {
        if (!h1) return h2;
        if (!h2) return h1;

        if (h1->data > h2->data) {
            std::swap(h1, h2);
        }

        h1->right = merge(h1->right, h2);

        if (!h1->left || h1->left->npl < h1->right->npl) {
            std::swap(h1->left, h1->right);
        }

        if (!h1->right) {
            h1->npl = 0;
        } else {
            h1->npl = h1->right->npl + 1;
        }

        return h1;
    }

public:
    LeftistHeap() : root(nullptr) {}

    ~LeftistHeap() {
        while (root) {
            deleteMin();
        }
    }

    void insert(T value) {
        Node* newNode = new Node(value);
        root = merge(root, newNode);
    }

    T getMin() {
        if (root) {
            return root->data;
        }
        throw std::runtime_error("Heap is empty");
    }

    void deleteMin() {
        if (!root) {
            throw std::runtime_error("Heap is empty");
        }

        Node* oldRoot = root;
        root = merge(root->left, root->right);
        delete oldRoot;
    }

    void printInOrder(Node* node) {
        if (node) {
            printInOrder(node->left);
            std::cout << node->data << " ";
            printInOrder(node->right);
        }
    }

    void printHeap() {
        printInOrder(root);
        std::cout << std::endl;
    }
};

int main() {
    LeftistHeap<int> heap;
    int choice, value;

    do {
        std::cout << "\nLeftist Heap Menu:\n";
        std::cout << "1. Insert\n";
        std::cout << "2. Get Minimum\n";
        std::cout << "3. Delete Minimum\n";
        std::cout << "4. Print Heap\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter the value to insert: ";
                std::cin >> value;
                heap.insert(value);
                std::cout << "Element inserted successfully.\n";
                break;

            case 2:
                try {
                    std::cout << "Minimum element: " << heap.getMin() << std::endl;
                } catch (const std::exception& e) {
                    std::cout << e.what() << std::endl;
                }
                break;

            case 3:
                try {
                    heap.deleteMin();
                    std::cout << "Minimum element deleted.\n";
                } catch (const std::exception& e) {
                    std::cout << e.what() << std::endl;
                }
                break;

            case 4:
                std::cout << "Heap in-order: ";
                heap.printHeap();
                break;

            case 5:
                std::cout << "Exiting...\n";
                break;

            default:
                std::cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}

