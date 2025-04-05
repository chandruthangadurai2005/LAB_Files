#include <iostream>
#include <vector>

using namespace std;

void binaryCounter(int bitLimit, int numIncrements) {
    vector<int> counter;
    counter.push_back(0);
    int totalCost = 0;
    int maxValue = (1 << bitLimit) - 1;
    int increments = (numIncrements > maxValue) ? maxValue : numIncrements;

    for (int i = 0; i < increments; ++i) {
        int carry = 1;
        int operationCost = 0;

        for (int j = 0; j < counter.size(); ++j) {
            operationCost++;
            counter[j] += carry;

            if (counter[j] == 2) {
                counter[j] = 0;
                carry = 1;
            } else {
                carry = 0;
                break;
            }
        }
        if (carry == 1 && counter.size() < bitLimit) {
            counter.push_back(1);
            operationCost++;
        }

        totalCost += operationCost;

        cout << "After increment " << i + 1 << ": ";
        for (int k = counter.size() - 1; k >= 0; --k) {
            cout << counter[k];
        }
        cout << " | Cost: " << operationCost << endl;
    }

    cout << "Total cost of all increments: " << totalCost << endl;
    cout << "Amortized cost per increment: " << (double)totalCost / increments << endl;
}

int main() {
    int bitLimit, numIncrements;
    cout << "Enter the number of bits: ";
    cin >> bitLimit;
    cout << "Enter the number of increments: ";
    cin >> numIncrements;
    
    binaryCounter(bitLimit, numIncrements);
    return 0;
}

