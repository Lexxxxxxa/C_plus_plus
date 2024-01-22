#include <iostream>
#include <windows.h>
using namespace std;

const int size = 3;

int matrix[::size][::size] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

int calculateRowSum(int row) {
    int sum = 0;
    for (int i = 0; i < ::size; i++) {
        sum += matrix[row][i];
    }
    return sum;
}

int main() {
    for (int i = 0; i < ::size; i++) {
        cout << "Row " << i + 1 << " Sum: " << calculateRowSum(i) << endl;
    }

    return 0;
}
