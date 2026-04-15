#include <iostream>
#include <vector>
#include <cmath>     // для sqrt та pow
#include <iomanip>
#include <string>

using namespace std;

// Функція для обчислення довжини вектора: sqrt(x^2 + y^2 + z^2)
double calculateLength(const vector<double>& v) {
    return sqrt(pow(v[0], 2) + pow(v[1], 2) + pow(v[2], 2));
}
int main() {
    cout << "Working with Vectors" << endl;

    // Ініціалізація векторів 
    vector<vector<double>> vectors = {
        {1.5, 2.1, 0.3},  // вектор a
        {3.0, 0.2, 0.7},  // вектор b
        {0.7, -2.5, 1.2}, // вектор c
        {0.4, 8.5, -1.2}, // вектор d
        {0.1, -0.3, 1.3}, // вектор f
        {0.4, 1.3, 0.6}   // вектор e
    };
    vector<string> names = { "a", "b", "c", "d", "f", "e" };

    // Припускаємо, що перший вектор має мінімальну довжину
    double minLength = calculateLength(vectors[0]);
    int minIndex = 0;

    cout << fixed << setprecision(4);
    cout << "Calculated lengths for all vectors:" << endl;
    // Цикл для обчислення довжин кожного вектора та пошуку мінімального
    for (int i = 0; i < vectors.size(); i++) {
        double currentLength = calculateLength(vectors[i]);
        cout << "Vector " << names[i] << ": " << currentLength << endl;

        // Перевірка на мінімальне значення
        if (currentLength < minLength) {
            minLength = currentLength;
            minIndex = i;
        }
    }
    // Вивід фінального результату (найкоротший вектор)
    cout << "Vector with the smallest length: " << names[minIndex] << endl;
    cout << "Coordinates: (";
    for (int i = 0; i < 3; i++) {
        cout << vectors[minIndex][i] << (i < 2 ? "; " : "");
    }
    cout << ")" << endl;
    cout << "Length value: " << minLength << endl;

    return 0;
}