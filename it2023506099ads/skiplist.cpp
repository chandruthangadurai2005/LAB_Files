#include <iostream>
#include <cstdlib>
#include <ctime>

template <typename T>
class Node {
public:
    T key;
    Node** forward;
    int level;

    Node(T key, int level) {
        this->key = key;
        this->level = level;
        forward = new Node*[level + 1];
        for (int i = 0; i <= level; i++) {
            forward[i] = nullptr;
        }
    }
    ~Node() {
        delete[] forward;
    }
};

template <typename T>
class SkipList {
private:
    int maxLevel;
    float probability;
    int currentLevel;
    Node<T>* header;

    int randomLevel() {
    int level = 1; // Start with level 1
    while ((rand() / (float)RAND_MAX) < probability) {
        level += 2; // Increase by 2 (1, 3, 5, ...)
    }
    return level <= maxLevel ? level : maxLevel;  // Make sure the level doesn't exceed maxLevel
}

public:
    SkipList(int maxLevel = 16, float probability = 0.5) {
        this->maxLevel = maxLevel;
        this->probability = probability;
        this->currentLevel = 0;
        header = new Node<T>(T(), maxLevel);
        srand(time(nullptr));
    }

    ~SkipList() {
        Node<T>* current = header->forward[0];
        while (current) {
            Node<T>* next = current->forward[0];
            delete current;
            current = next;
        }
        delete header;
    }

    void insert(T key) {
        Node<T>* update[maxLevel + 1];
        Node<T>* current = header;

        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        int newLevel = randomLevel();
        if (newLevel > currentLevel) {
            for (int i = currentLevel + 1; i <= newLevel; i++) {
                update[i] = header;
            }
            currentLevel = newLevel;
        }

        Node<T>* newNode = new Node<T>(key, newLevel);
        for (int i = 0; i <= newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }

    bool search(T key) {
        Node<T>* current = header;
        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->key < key) {
                current = current->forward[i];
            }
        }
        current = current->forward[0];

        return (current && current->key == key);
    }

    void remove(T key) {
        Node<T>* update[maxLevel + 1];
        Node<T>* current = header;

        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];

        if (current && current->key == key) {
            for (int i = 0; i <= currentLevel; i++) {
                if (update[i]->forward[i] != current) break;
                update[i]->forward[i] = current->forward[i];
            }

            delete current;

            while (currentLevel > 0 && header->forward[currentLevel] == nullptr) {
                currentLevel--;
            }
        }
    }

    void display() {
        for (int i = currentLevel; i >= 0; i--) {
            Node<T>* node = header->forward[i];
            std::cout << "Level " << i << ": ";
            while (node) {
                std::cout << node->key << " ";
                node = node->forward[i];
            }
            std::cout << "\n";
        }
    }
};

int main() {
    SkipList<int> list;
   cout<<"enter no of entries";
   int a;
   cin>>a;
   cout<<"enter the elements";
   for(int i=0;i<a;i++){
           int j;
           cin>>j;
           list.insert(j);
   }

    std::cout << "Skip List:\n";
    list.display();
    int s;
    cout<<"enter search element";
    cin>>s;
    std::cout << "\nSearch  " <<s<< (list.search(s) ? " Found" : " Not Found") << "\n";

     int t;
   cout<<"enter element to delete";
   cin>>t;
    list.remove(t);

    std::cout << "\nAfter removing :"<<t<<"\n";

    list.display();

    return 0;
}



/*
Algorithm
Here’s a simplified 6-step breakdown of the algorithm behind the provided Skip List implementation:

1. **Initialization**:  
   - A Skip List is initialized with a `maxLevel` (default 16) and a `probability` (default 0.5).  
   - A header node is created to start the list, and a random seed is set for level generation.

2. **Insert Operation**:
   - **Search for Insertion Point**: Starting from the highest level, traverse through the list to find where the new element should be inserted, using the `forward` pointers.
   - **Random Level Generation**: Determine the random level for the new node based on the probability (higher probability increases level).
   - **Insert Node**: Create the new node with the calculated level, and adjust the `forward` pointers of the nodes at the appropriate levels to link to the new node.

3. **Search Operation**:
   - Starting from the highest level, traverse through the list to find the target key.  
   - If the key is found at the base level (`forward[0]`), return `true`, otherwise return `false`.

4. **Remove Operation**:
   - **Search for Node**: Similar to the search operation, traverse the list to locate the node to be removed.
   - **Update Pointers**: Adjust the `forward` pointers at each level where the node is present, effectively removing it from the list.
   - **Reduce List Level**: After removal, reduce the `currentLevel` if the highest level of the list becomes empty.

5. **Random Level Generation**:
   - A random level for a new node is chosen based on a probabilistic approach. The level increases as long as a randomly generated number is less than the defined probability and the maximum level is not exceeded.

6. **Display Operation**:
   - Traverse through each level of the list and display the nodes present at that level, helping visualize the structure of the Skip List.

This structure enables efficient search, insertion, and removal operations with an average time complexity of \(O(\log N)\), where \(N\) is the number of elements in the list.*/
