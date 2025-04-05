#include <iostream>
#include <cmath>
#include <vector>
#include <climits>

using namespace std;

class FibonacciHeapNode {
public:
    int key;
    FibonacciHeapNode* parent;
    FibonacciHeapNode* child;
    FibonacciHeapNode* next;
    FibonacciHeapNode* prev;
    int degree;
    bool marked;

    FibonacciHeapNode(int key) {
        this->key = key;
        parent = child = next = prev = nullptr;
        degree = 0;
        marked = false;
    }
};

class FibonacciHeap {
private:
    FibonacciHeapNode* minNode;
    int nodeCount;

    void link(FibonacciHeapNode* y, FibonacciHeapNode* x) {
        y->prev->next = y->next;
        y->next->prev = y->prev;

        if (x->child == nullptr) {
            x->child = y;
            y->prev = y->next = y;
        } else {
            y->prev = x->child;
            y->next = x->child->next;
            x->child->next = y;
            y->next->prev = y;
        }

        x->degree++;
        y->marked = false;
    }

    void consolidate() {
        int maxDegree = log2(nodeCount) + 1;
        vector<FibonacciHeapNode*> degreeTable(maxDegree, nullptr);

        FibonacciHeapNode* current = minNode;
        FibonacciHeapNode* start = minNode;

        do {
            FibonacciHeapNode* x = current;
            int d = x->degree;

            while (degreeTable[d] != nullptr) {
                FibonacciHeapNode* y = degreeTable[d];

                if (x->key > y->key)
                    swap(x, y);

                link(y, x);
                degreeTable[d] = nullptr;
                d++;
            }

            degreeTable[d] = x;
            current = current->next;
        } while (current != start);

        minNode = nullptr;
        for (FibonacciHeapNode* node : degreeTable) {
            if (node != nullptr) {
                if (minNode == nullptr || node->key < minNode->key)
                    minNode = node;
            }
        }
    }

    void cut(FibonacciHeapNode* x, FibonacciHeapNode* y) {
        if (x->next == x) {
            y->child = nullptr;
        } else {
            x->next->prev = x->prev;
            x->prev->next = x->next;

            if (y->child == x) {
                y->child = x->next;
            }
        }

        y->degree--;
        x->next = minNode;
        x->prev = minNode->prev;
        minNode->prev->next = x;
        minNode->prev = x;
        x->parent = nullptr;

        x->marked = false;
    }

    void cascadingCut(FibonacciHeapNode* y) {
        FibonacciHeapNode* z = y->parent;
        if (z != nullptr) {
            if (!y->marked) {
                y->marked = true;
            } else {
                cut(y, z);
                cascadingCut(z);
            }
        }
    }

public:
    FibonacciHeap() {
        minNode = nullptr;
        nodeCount = 0;
    }

    void insert(int key) {
        FibonacciHeapNode* newNode = new FibonacciHeapNode(key);

        if (minNode == nullptr) {
            minNode = newNode;
            newNode->next = newNode->prev = newNode;
        } else {
            newNode->prev = minNode->prev;
            newNode->next = minNode;
            minNode->prev->next = newNode;
            minNode->prev = newNode;

            if (key < minNode->key) {
                minNode = newNode;
            }
        }

        nodeCount++;
    }

    FibonacciHeapNode* minimum() {
        return minNode;
    }

    int extractMin() {
        FibonacciHeapNode* oldMin = minNode;

        if (oldMin != nullptr) {
            if (oldMin->child != nullptr) {
                FibonacciHeapNode* child = oldMin->child;
                do {
                    child->parent = nullptr;
                    child = child->next;
                } while (child != oldMin->child);

                oldMin->prev->next = oldMin->child;
                oldMin->child->prev = oldMin->prev;
                oldMin->next->prev = oldMin->child->prev;
                oldMin->child->prev->next = oldMin->next;
            }

            oldMin->prev->next = oldMin->next;
            oldMin->next->prev = oldMin->prev;

            if (oldMin == oldMin->next) {
                minNode = nullptr;
            } else {
                minNode = oldMin->next;
                consolidate();
            }

            nodeCount--;
            int minValue = oldMin->key;
            delete oldMin;
            return minValue;
        }

        return -1;
    }

    void decreaseKey(FibonacciHeapNode* x, int newKey) {
        if (newKey > x->key) {
            cout << "New key is greater than current key" << endl;
            return;
        }

        x->key = newKey;
        FibonacciHeapNode* y = x->parent;
        if (y != nullptr && x->key < y->key) {
            cut(x, y);
            cascadingCut(y);
        }

        if (x->key < minNode->key) {
            minNode = x;
        }
    }

    void deleteNode(FibonacciHeapNode* x) {
        decreaseKey(x, INT_MIN);
        extractMin();
    }
};

int main() {
    FibonacciHeap fibHeap;
    int choice, key;

    do {
        cout << "\nFibonacci Heap Operations Menu\n";
        cout << "1. Insert\n";
        cout << "2. Extract Min\n";
        cout << "3. Decrease Key\n";
        cout << "4. Delete Node\n";
        cout << "5. Get Minimum\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the key to insert: ";
                cin >> key;
                fibHeap.insert(key);
                cout << "Key " << key << " inserted successfully." << endl;
                break;
            case 2:
                cout << "Extracting min: " << fibHeap.extractMin() << endl;
                break;
            case 3:
                cout << "Enter the key to decrease: ";
                cin >> key;
                cout << "Enter the new key value: ";
                int newKey;
                cin >> newKey;
                {
                    FibonacciHeapNode* node = fibHeap.minimum();
                    while (node != nullptr && node->key != key) {
                        node = node->next;
                    }
                    if (node != nullptr) {
                        fibHeap.decreaseKey(node, newKey);
                        cout << "Key decreased successfully." << endl;
                    } else {
                        cout << "Key not found in heap." << endl;
                    }
                }
                break;
            case 4:
                cout << "Enter the key to delete: ";
                cin >> key;
                {
                    FibonacciHeapNode* node = fibHeap.minimum();
                    while (node != nullptr && node->key != key) {
                        node = node->next;
                    }
                    if (node != nullptr) {
                        fibHeap.deleteNode(node);
                        cout << "Node with key " << key << " deleted successfully." << endl;
                    } else {
                        cout << "Key not found in heap." << endl;
                    }
                }
                break;
            case 5:
                if (fibHeap.minimum() != nullptr) {
                    cout << "Minimum key: " << fibHeap.minimum()->key << endl;
                } else {
                    cout << "Heap is empty." << endl;
                }
                break;
            case 6:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}

