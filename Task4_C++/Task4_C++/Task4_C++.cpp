#include <iostream>
#include <fstream>   // для роботи з файлами
#include <string>
#include <vector>
#include <sstream> // теж з роботою файлів повязане 
#include <algorithm> // для сортування sort()

using namespace std;

// Функція для обробки одного речення: розбиття на слова, сортування та збирання назад
string processSentence(string sentence) {
    if (sentence.empty()) return "";

    // Перевіряємо, чи є крапка в кінці, і запам'ятовуємо це
    bool hasDot = (!sentence.empty() && sentence.back() == '.');
    if (hasDot) sentence.pop_back(); // Тимчасово прибираємо крапку для сортування слів

    stringstream ss(sentence);
    string word;
    vector<string> words;

    // Розбиваємо рядок на окремі слова
    while (ss >> word) {
        words.push_back(word);
    }

    // Сортуємо слова в алфавітному порядку 
    sort(words.begin(), words.end());

    // Збираємо слова назад у рядок
    string result = "";
    for (size_t i = 0; i < words.size(); ++i) {
        result += words[i] + (i == words.size() - 1 ? "" : " ");
    }

    if (hasDot) result += "."; // Повертаємо крапку на місце
    return result;
}

int main() {
    // Відкриваємо файл для читання
    ifstream inputFile("input.txt");
    // Створюємо файл для запису результату
    ofstream outputFile("output.txt");

    if (!inputFile.is_open()) {
        cout << "Error: Could not open input.txt!" << endl;
        return 1;
    }

    string line;
    cout << "Processing file content..." << endl;

    // Читаємо файл рядок за рядком 
    while (getline(inputFile, line)) {
        if (line.empty()) continue;

        // Сортуємо слова
        string processedLine = processSentence(line);

        // Записуємо результат у вихідний файл
        outputFile << processedLine << endl;
    }

    cout << "Success! Sorted sentences are saved in 'output.txt'." << endl;

    inputFile.close();
    outputFile.close();

    return 0;
}

