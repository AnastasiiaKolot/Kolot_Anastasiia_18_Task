#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// основні характеристики.
struct Planet {
    string name;           // Назва планети
    double size;           // Розмір 
    bool habitable;        // Логічне значення: 1 - придатна для життя, 0 - ні
    double orbitPeriod;    // Скільки днів триває один оберт навколо зорі
    string starName;       // Ім'я материнської зорі 
};

// Проста функція для перевірки, щоб не вводили букви замість цифр
double getSafeDouble(string message) {
    double value;
    cout << message;
    while (!(cin >> value)) { // Якщо введення не є числом
        cout << "[Error] Please enter a number: ";
        cin.clear();          // Скидаємо помилку
        string dummy;
        cin >> dummy;         // Clean неправильний текст, щоб він не зациклював програму
    }
    return value;
}

// Перевірка для так/ні (1 або 0)
bool getSafeBool(string message) {
    int value;
    cout << message;
    while (!(cin >> value) || (value != 0 && value != 1)) {
        cout << "[Error] Enter 1 (Yes) or 0 (No): ";
        cin.clear();
        string dummy;
        cin >> dummy;
    }
    return (value == 1);
}

// Приймає об'єкт структури та дописує його в текстовий файл. * Використовує ofstream
void saveToFile(const Planet& p) {
    // Відкриваємо файл у режимі ios::app (append), щоб додавати в кінець
    ofstream outFile("planets.txt", ios::app);

    if (outFile.is_open()) {
        // Записуємо дані через пробіл
        outFile << p.name << " "
            << p.size << " "
            << p.habitable << " "
            << p.orbitPeriod << " "
            << p.starName << endl;
        outFile.close(); // закриваємо файл після роботи
    }
    else {
        cout << "[Error] File not found!" << endl;
    }
}

// Читає всі записи з файлу і зберігає їх у динамічний масив (vector). * Використовує ifstream
vector<Planet> loadFromFile() {
    vector<Planet> planets;
    ifstream inFile("planets.txt");

    if (inFile.is_open()) {
        Planet p;
        // Поки можемо прочитати всі 5 полів планети
        while (inFile >> p.name >> p.size >> p.habitable >> p.orbitPeriod >> p.starName) {
            planets.push_back(p);
        }
        inFile.close();
    }
    return planets;
}

// Фільтрує список планет і виводить лише ті, де habitable == true.
void showHabitablePlanets(const vector<Planet>& planets) {
    cout << "\n>>> HABITABLE PLANETS <<<" << endl;

    bool found = false;
    for (int i = 0; i < planets.size(); i++) {
        if (planets[i].habitable) {
            cout << "Name: " << planets[i].name
                << " | Star: " << planets[i].starName << endl;
            found = true;
        }
    }
    if (!found) cout << "No habitable planets found." << endl;
}

// Реалізує інтерфейс термінала для взаємодії з користувачем.
int main() {
    int choice;

    while (true) {
        cout << "\n--- PLANET MENU ---" << endl;
        cout << "1. Add new planet" << endl;
        cout << "2. View all planets" << endl;
        cout << "3. Show habitable only" << endl;
        cout << "0. Exit" << endl;
        cout << "Your choice: ";

        // Перевірка на вибір меню
        if (!(cin >> choice)) {
            cin.clear();
            string dummy;
            cin >> dummy;
            cout << "[Error] Choose a number!" << endl;
            continue;
        }

        if (choice == 0) break;

        if (choice == 1) {
            Planet p;
            cout << "Planet name: "; cin >> p.name;
            p.size = getSafeDouble("Size: ");
            p.habitable = getSafeBool("Habitable? (1-Yes, 0-No): ");
            p.orbitPeriod = getSafeDouble("Orbit period: ");
            cout << "Star name: "; cin >> p.starName;

            saveToFile(p);
            cout << "[Done] Saved!" << endl;
        }
        else if (choice == 2) {
            vector<Planet> planets = loadFromFile();
            if (planets.empty()) cout << "File is empty." << endl;
            else {
                for (int i = 0; i < planets.size(); i++) {
                    cout << planets[i].name << " (Star: " << planets[i].starName << ")" << endl;
                }
            }
        }
        else if (choice == 3) {
            vector<Planet> planets = loadFromFile();
            showHabitablePlanets(planets);
        }
    }

    return 0;
}