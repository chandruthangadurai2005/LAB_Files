#include <iostream>
using namespace std;

class DynamicTable {
private:
    int* table;       // Pointer to the dynamic table
    int size;         // Current capacity of the table
    int count;        // Number of elements in the table
    int totalCost;    // Total cost of all insertions

    void resize() {
        int newSize = size * 2;
        int* newTable = new int[newSize];

        // Copy elements to the new table
        for (int i = 0; i < count; ++i) {
            newTable[i] = table[i];
        }

        delete[] table;  // Free the old table memory
        table = newTable;
        size = newSize;

        cout << "Resized table to size " << size << " (Cost of resizing: " << count << ")" << endl;
    }

public:
    DynamicTable() : size(1), count(0), totalCost(0) {
        table = new int[size];
    }

    ~DynamicTable() {
        delete[] table;
    }

    void insert(int value) {
        int insertionCost = 1; // Cost for inserting one element

        // If table is full, resize
        if (count == size) {
            insertionCost += count; // Cost of copying all elements during resizing
            resize();
        }

        // Insert the element
        table[count++] = value;
        totalCost += insertionCost; // Update total cost

        cout << "Inserted " << value << " | Cost: " << insertionCost << endl;
    }

    void display() const {
        cout << "Table contents: ";
        for (int i = 0; i < count; ++i) {
            cout << table[i] << " ";
        }
        cout << endl;
    }

    void displayCosts() const {
        cout << "Total cost of all insertions: " << totalCost << endl;
        cout << "Amortized cost per insertion: " << (double)totalCost / count << endl;
    }
};

int main() {
    int n, value;
    cout << "Enter the number of elements to insert: ";
    cin >> n;

    DynamicTable dt;

    for (int i = 0; i < n; ++i) {
        cout << "Enter value to insert: ";
        cin >> value;
        dt.insert(value);
        dt.display();
    }

    dt.displayCosts();

    return 0;
}

