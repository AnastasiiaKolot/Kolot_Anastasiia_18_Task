#include <iostream>
#include <vector>    // для std::vector
#include <algorithm> // для std::sort
#include <ctime>     // для time(0)
#include <chrono>    // для вимірювання часу

using namespace std;

// 1. Сортування Вибором (Selection Sort)
void sort1Selection(vector<int>& a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[min_idx]) min_idx = j;
        }
        swap(a[min_idx], a[i]); // Міняємо місцями
    }
}

// 2. Сортування методом Шелла (Shell Sort)
void sort2Shell(vector<int>& a) {
    int n = a.size();
    // Використовуємо крок (gap), який поступово зменшується
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int t = a[i], j;
            for (j = i; j >= gap && a[j - gap] > t; j -= gap) a[j] = a[j - gap];
            a[j] = t;
        }
    }
}

// 3. Сортування підрахунком (Counting Sort)
void sort3Counting(vector<int>& a) {
    if (a.empty()) return;
    int max_v = a[0], min_v = a[0];

    // Шукаємо діапазон чисел
    for (int x : a) {
        if (x > max_v) max_v = x;
        if (x < min_v) min_v = x;
    }
    int r = max_v - min_v + 1;
    vector<int> count(r, 0), out(a.size());

    // Рахуємо кількість кожного числа
    for (int x : a) count[x - min_v]++;
    for (int i = 1; i < r; i++) count[i] += count[i - 1];

    // Записуємо в результуючий масив
    for (int i = a.size() - 1; i >= 0; i--) {
        out[count[a[i] - min_v] - 1] = a[i];
        count[a[i] - min_v]--;
    }
    a = out;
}

// Функція бінарного пошуку 
int binarySearch(const vector<int>& a, int target) {
    int left = 0, right = a.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (a[mid] == target) return mid;
        if (a[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Функція для компактного виведення масиву (щоб не захаращувати звіт)
void printCompact(const vector<int>& a) {
    int n = a.size();
    if (n <= 18) {
        // Якщо масив малий, виводимо всі елементи
        for (int x : a) cout << x << " ";
    }
    else {
        // Якщо масив великий, виводимо лише перші та останні 5 елементів
        for (int i = 0; i < 5; i++) cout << a[i] << " ";
        cout << "... ";
        for (int i = n - 5; i < n; i++) cout << a[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(0));

    int sizes[] = { 18, 160, 1024, 4096, 32600, 128000 };

    for (int n : sizes) {
        cout << "\n----------------------------" << endl;
        cout << "SIZE: " << n << endl;
        vector<int> data(n);
        for (int i = 0; i < n; i++) data[i] = rand() % 10000;

        // Копії масиву для кожного сортування
        vector<int> a1 = data, a2 = data, a3 = data;

        // Вимірюємо Сортування Вибором
        auto s1 = chrono::high_resolution_clock::now();
        sort1Selection(a1);
        auto e1 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> d1 = e1 - s1;
        cout << "1. Selection Sort: " << d1.count() << " ms" << endl;

        // Вимірюємо Шелл
        auto s2 = chrono::high_resolution_clock::now();
        sort2Shell(a2);
        auto e2 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> d2 = e2 - s2;
        cout << "2. Shell Sort:     " << d2.count() << " ms" << endl;

        // Вимірюємо Підрахунок
        auto s3 = chrono::high_resolution_clock::now();
        sort3Counting(a3);
        auto e3 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> d3 = e3 - s3;
        cout << "3. Counting Sort:  " << d3.count() << " ms" << endl;

        // Компактний вивід масиву після сортування
        cout << "Sorted array (preview): ";
        printCompact(a3);
        // Виконуємо бінарний пошук 
        if (n > 0) {
            int target = a3[n / 2]; // Шукаємо елемент з середини
            cout << "Searching for value " << target << "..." << endl;
            int pos = binarySearch(a3, target);
            cout << "Found at index: " << pos << endl;
        }
    }

    return 0;
}