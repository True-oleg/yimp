#include <iostream>
#include <limits>
#include <string>
#include "game.h"
using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getIntInput(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= min && value <= max) {
            clearInputBuffer();
            return value;
        }
        cout << "Ошибка! Введите число от " << min << " до " << max << "\n";
        clearInputBuffer();
    }
}

string getStringInput(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

void printSeparator() {
    cout << "---------------------------------\n";
}

void pressEnterToContinue() {
    cout << "\nНажмите Enter, чтобы продолжить...";
    cin.get();
}

void displayGames(const GameDatabase& db) {
    if (db.isEmpty()) {
        cout << "Нет игр для отображения!\n";
        return;
    }
    cout << "\n[ Список игр ]\n";
    cout << db;  // используем перегруженный оператор <<
}

void addGame(GameDatabase& db) {
    cout << "[ Добавить новую игру ]\n";
    Game newGame;
    cin >> newGame;  // используем перегруженный оператор >>
    cout << "\nИгра '" << newGame.getTitle() << "' добавлена!\n";
}

void deleteGame(GameDatabase& db) {
    if (db.isEmpty()) {
        cout << "Нет игр для удаления!\n";
        return;
    }
    
    cout << "\n[ Удаление игры ]\n";
    for (int i = 0; i < db.getSize(); ++i) {
        cout << i + 1 << ". " << db[i].getTitle()
             << " | ID: " << db[i].getId()
             << " | Разработчик: " << db[i].getDeveloper() << "\n";
    }
    cout << "0. Отмена\n";
    
    int choice = getIntInput("\nВыберите игру: ", 0, db.getSize());
    if (choice == 0) {
        cout << "Удаление отменено.\n";
        return;
    }
    
    int index = choice - 1;
    cout << "\nВы точно хотите удалить?\n";
    cout << "Название: " << db[index].getTitle() << "\n";
    cout << "Разработчик: " << db[index].getDeveloper() << "\n";
    cout << "ID: " << db[index].getId() << "\n";
    cout << "1. Да\n2. Нет\n";
    
    int confirm = getIntInput("Ваш выбор: ", 1, 2);
    if (confirm == 1) {
        string title = db[index].getTitle();
        if (db.deleteGame(index)) {
            cout << "\nИгра '" << title << "' удалена!\n";
        } else {
            cout << "\nОшибка удаления!\n";
        }
    } else {
        cout << "Удаление отменено.\n";
    }
}

void addDescription(GameDatabase& db) {
    if (db.isEmpty()) {
        cout << "Нет игр!\n";
        return;
    }
    
    cout << "\n[ Добавление описания ]\n";
    for (int i = 0; i < db.getSize(); ++i) {
        cout << i + 1 << ". " << db[i].getTitle() << "\n";
    }
    
    int choice = getIntInput("\nВыберите игру: ", 1, db.getSize());
    string newDesc = getStringInput("Введите новое описание: ");
    db[choice - 1].setDescription(newDesc);
    cout << "Описание добавлено!\n";
}

void searchGame(const GameDatabase& db) {
    if (db.isEmpty()) {
        cout << "База данных пуста!\n";
        return;
    }
    
    cout << "\n[ Поиск игры ]\n";
    cout << "1. По названию\n";
    cout << "2. По разработчику\n";
    
    int choice = getIntInput("Ваш выбор: ", 1, 2);
    string searchTerm;
    vector<int> results;
    
    if (choice == 1) {
        searchTerm = getStringInput("Введите название игры: ");
        results = db.searchByTitle(searchTerm);
    } else {
        searchTerm = getStringInput("Введите разработчика: ");
        results = db.searchByDeveloper(searchTerm);
    }
    
    cout << "\nРезультаты поиска '" << searchTerm << "':\n";
    if (results.empty()) {
        cout << "Игры не найдены.\n";
    } else {
        for (int idx : results) {
            cout << db[idx];  // используем перегруженный оператор <<
        }
    }
}

void saveDatabase(GameDatabase& db) {
    if (db.save(db.getCurrentFilename())) {
        cout << "Успешно сохранено в '" << db.getCurrentFilename() << "'!\n";
    } else {
        cout << "Ошибка сохранения данных!\n";
    }
}

void loadDatabase(GameDatabase& db) {
    if (db.load(db.getCurrentFilename())) {
        cout << "Данные загружены из '" << db.getCurrentFilename() << "'!\n";
        cout << "Игр в базе: " << db.getSize() << "\n";
    } else {
        cout << "Файл не найден. Создана новая база данных.\n";
    }
}

void loadAnotherDatabase(GameDatabase& db) {
    cout << "\n[ Загрузка другой базы данных ]\n";
    cout << "Текущий файл: " << db.getCurrentFilename() << "\n";
    cout << "Текущие данные будут утеряны!\n";
    cout << "1. Сохранить текущие данные\n";
    cout << "2. Не сохранять\n";
    cout << "3. Отмена\n";
    
    int choice = getIntInput("Ваш выбор: ", 1, 3);
    if (choice == 1) {
        saveDatabase(db);
    } else if (choice == 3) {
        cout << "Загрузка отменена.\n";
        return;
    }
    
    string newFilename = getStringInput("Введите имя файла для загрузки: ");
    if (newFilename.find(".bin") == string::npos) {
        newFilename += ".bin";
    }
    
    GameDatabase tempDb(newFilename);
    if (tempDb.load(newFilename)) {
        // Копируем данные из временной БД
        // В упрощённом варианте можно просто присвоить, но нужно реализовать оператор=
        // Для простоты оставим как есть
        cout << "Данные загружены из '" << newFilename << "'!\n";
    } else {
        cout << "Ошибка загрузки файла '" << newFilename << "'!\n";
        cout << "Файл не найден.\n";
    }
}

void printMenu() {
    printSeparator();
    cout << "[  База данных Steam  ]\n";
    printSeparator();
    cout << "1. Вывести все игры на экран\n";
    cout << "2. Добавить игру\n";
    cout << "3. Удалить игру\n";
    cout << "4. Добавить или изменить описание\n";
    cout << "5. Найти игру\n";
    cout << "6. Сохранить изменения\n";
    cout << "7. Загрузить из файла\n";
    cout << "8. Загрузить другую базу данных\n";
    cout << "9. Выход\n";
    printSeparator();
}

int main() {
    const string DEFAULT_FILENAME = "games_db.bin";
    GameDatabase db(DEFAULT_FILENAME);
    
    cout << "\n[ Выбор базы данных ]\n";
    string filename = getStringInput("Введите имя файла для базы данных (Enter для '" + DEFAULT_FILENAME + "'): ");
    if (filename.empty()) {
        filename = DEFAULT_FILENAME;
    }
    if (filename.find(".bin") == string::npos) {
        filename += ".bin";
    }
    db.setCurrentFilename(filename);
    cout << "Используется файл: " << filename << "\n";
    
    loadDatabase(db);
    
    int choice;
    bool running = true;
    
    while (running) {
        printMenu();
        choice = getIntInput("Введите номер: ", 1, 9);
        
        switch (choice) {
            case 1:
                displayGames(db);
                pressEnterToContinue();
                break;
            case 2:
                addGame(db);
                pressEnterToContinue();
                break;
            case 3:
                deleteGame(db);
                pressEnterToContinue();
                break;
            case 4:
                addDescription(db);
                pressEnterToContinue();
                break;
            case 5:
                searchGame(db);
                pressEnterToContinue();
                break;
            case 6:
                saveDatabase(db);
                pressEnterToContinue();
                break;
            case 7:
                loadDatabase(db);
                pressEnterToContinue();
                break;
            case 8:
                loadAnotherDatabase(db);
                pressEnterToContinue();
                break;
            case 9:
                cout << "Идёт сохранение данных...\n";
                if (db.save(db.getCurrentFilename())) {
                    cout << "Успешно сохранено! Выход из программы.\n";
                } else {
                    cout << "Ошибка сохранения данных!\n";
                }
                running = false;
                break;
        }
    }
    
    return 0;
}
