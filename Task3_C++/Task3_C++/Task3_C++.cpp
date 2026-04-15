#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <algorithm> // для std::sort

using namespace std;

// 1. Функція для обчислення медіани всієї матриці 
int calculateMedian(vector<vector<int>> mat, int n) {
    vector<int> flat;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            flat.push_back(mat[i][j]);
        }
    }
    sort(flat.begin(), flat.end());
    return flat[flat.size() / 2];
}

// 2. Функція для обробки Сектора 1\ (Верхній + Головна діагональ)
int processSector1(const vector<vector<int>>& mat, int n, int K) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            //i <= j для врахування головної діагоналі
            if (i <= j && (i + j) < (n - 1)) {
                if (mat[i][j] > K) {
                    count++;
                }
            }
        }
    }
    return count;
}

// 3. Функція для обробки Сектора *5 (Лівий + дві діагоналі)
int processSector5(vector<vector<int>>& mat, int n, int median) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // додано >= та <= для врахування обох діагоналей 
            if (i >= j && (i + j) <= (n - 1)) {
                count++;
                mat[i][j] = median;
            }
        }
    }
    return count;
}

// 4. Функція для виведення матриці 
void printMatrix(const vector<vector<int>>& mat) {
    for (const auto& row : mat) {
        for (int val : row) {
            cout << setw(6) << val;
        }
        cout << endl;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int n, K;
    cout << "Enter matrix size n: ";
    cin >> n;
    cout << "Enter number K to find elements greater than it in Sector 1: ";
    cin >> K;

    vector<vector<int>> matrix(n, vector<int>(n));

    // Заповнення (діапазоном: -28;28)
    cout << "Initial Matrix (Random values -28 to 28):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 57 - 28;// (діапазон значень)
            cout << setw(6) << matrix[i][j];
        }
        cout << endl;
    }
    //виводимо наші методи для коду 
    int median = calculateMedian(matrix, n);
    int countS1 = processSector1(matrix, n, K);
    int countS5 = processSector5(matrix, n, median);

    cout << "Matrix Median value: " << median << endl;
    cout << "Elements in Sector (with diag) > " << K << ": " << countS1 << endl;
    cout << "Total elements in Sector *5 (with diags) replaced: " << countS5 << endl;

    cout << "\nMatrix after Sector *5 replacement (with median " << median << "):" << endl;
    printMatrix(matrix);

    return 0;
}