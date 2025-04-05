#include <iostream>
#include <vector>

using namespace std;

class DisjointSet {
private:
    vector<int> parent, rank;

public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    void unionSet(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
            cout << "Union done between " << x << " and " << y << endl;
        } else {
            cout << x << " and " << y << " are already in the same set!" << endl;
        }
    }

    void displayParents() {
        cout << "\nElement -> Parent mapping:\n";
        for (int i = 0; i < parent.size(); i++) {
            cout << i << " -> " << parent[i] << endl;
        }
    }

    void displaySetAdjacencyMatrix() {
        int n = parent.size();
        cout << "\n=== Disjoint Set Adjacency Matrix ===\n    ";
        for (int i = 0; i < n; i++) {
            cout << i << " ";
        }
        cout << "\n   ";
        for (int i = 0; i < n; i++) cout << "--";
        cout << endl;

        for (int i = 0; i < n; i++) {
            cout << i << " | ";
            for (int j = 0; j < n; j++) {
                if (find(i) == find(j)) {
                    cout << "1 ";
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    int n, choice, x, y;
    cout << "Enter the number of elements: ";
    cin >> n;

    DisjointSet ds(n);

    while (true) {
        cout << "\n===== Disjoint Set Menu =====" << endl;
        cout << "1. Find Set\n2. Union Sets\n3. Display Parent Array\n4. Display Adjacency Matrix\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter element to find its set: ";
                cin >> x;
                if (x >= 0 && x < n)
                    cout << "Representative of " << x << " is: " << ds.find(x) << endl;
                else
                    cout << "Invalid input! Enter a value between 0 and " << n - 1 << endl;
                break;

            case 2:
                cout << "Enter two elements to unite: ";
                cin >> x >> y;
                if (x >= 0 && x < n && y >= 0 && y < n)
                    ds.unionSet(x, y);
                else
                    cout << "Invalid input! Enter values between 0 and " << n - 1 << endl;
                break;

            case 3:
                ds.displayParents();
                break;

            case 4:
                ds.displaySetAdjacencyMatrix();
                break;

            case 5:
                cout << "Exiting program. Goodbye!" << endl;
                return 0;

            default:
                cout << "Invalid choice! Please enter a valid option." << endl;
        }
    }

    return 0;
}

