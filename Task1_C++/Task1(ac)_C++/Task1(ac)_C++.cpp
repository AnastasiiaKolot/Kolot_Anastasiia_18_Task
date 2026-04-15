#include <iostream>
#include <vector>    // для std::vector
#include <algorithm> // для std::sort
#include <ctime>     // для time(0)
#include <chrono>    // для вимірювання часу
#include <future>    // для асинхронності (std::async)

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
    for (int x : a) {
        if (x > max_v) max_v = x;
        if (x < min_v) min_v = x;
    }
    int r = max_v - min_v + 1;
    vector<int> count(r, 0), out(a.size());
    for (int x : a) count[x - min_v]++;
    for (int i = 1; i < r; i++) count[i] += count[i - 1];
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

// Нова функція для компактного виведення масиву
void printCompact(const vector<int>& a) {
    int n = a.size();
    if (n <= 18) {
        // Якщо масив малий, виводимо все
        for (int x : a) cout << x << " ";
    }
    else {
        // Якщо масив великий, виводимо початок і кінець
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
        cout << "\n>>> ASYNC SIZE: " << n << " <<<" << endl;
        vector<int> data(n);
        for (int i = 0; i < n; i++) data[i] = rand() % 10000;

        vector<int> a1 = data, a2 = data, a3 = data;

        // Початок відліку ЗАГАЛЬНОГО часу
        auto start = chrono::high_resolution_clock::now();

        // Асинхронний запуск
        auto f1 = async(launch::async, [&]() { sort1Selection(a1); });
        auto f2 = async(launch::async, [&]() { sort2Shell(a2); });
        auto f3 = async(launch::async, [&]() { sort3Counting(a3); });

        f1.wait(); f2.wait(); f3.wait();

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> diff = end - start;

        cout << "Async total time: " << diff.count() << " ms" << endl;

        // Компактний вивід масиву
        cout << "Sorted array (preview): ";
        printCompact(a3);

        // Бінарний пошук
        if (n > 0) {
            int target = a3[n / 2];
            cout << "Searching for value " << target << "..." << endl;
            int pos = binarySearch(a3, target);
            cout << "Found at index: " << pos << endl;
        }
        cout << "--------------------------------" << endl;
    }

    return 0;
}