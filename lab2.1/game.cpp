#include "game.h"
#include <fstream>

Rating::Rating(float rate) : user_rate(rate) {}
float Rating::getRate() const { return user_rate; }
void Rating::setRate(float rate) { user_rate = rate; }
std::ostream& operator<<(std::ostream& os, const Rating& rating) {
    os << rating.user_rate;
    return os;
}

std::istream& operator>>(std::istream& is, Rating& rating) {
    std::cout << "Оценка (1-10): ";
    float rate;
    is >> rate;
    if (rate < 1) rate = 1;
    if (rate > 10) rate = 10;
    rating.user_rate = rate;
    return is;
}

RelDate::RelDate(int d, int m, int y) : day(d), month(m), year(y) {}
int RelDate::getDay() const { return day; }
int RelDate::getMonth() const { return month; }
int RelDate::getYear() const { return year; }

void RelDate::setDate(int d, int m, int y) {
    day = d; month = m; year = y;
}

std::ostream& operator<<(std::ostream& os, const RelDate& date) {
    if (date.day < 10) os << "0";
    os << date.day << ".";
    if (date.month < 10) os << "0";
    os << date.month << ".";
    os << date.year;
    return os;
}

std::istream& operator>>(std::istream& is, RelDate& date) {
    std::cout << "  День (1-31): ";
    is >> date.day;
    std::cout << "  Месяц (1-12): ";
    is >> date.month;
    std::cout << "  Год (1980-2025): ";
    is >> date.year;
    if (date.day < 1) date.day = 1;
    if (date.day > 31) date.day = 31;
    if (date.month < 1) date.month = 1;
    if (date.month > 12) date.month = 12;
    if (date.year < 1980) date.year = 1980;
    if (date.year > 2025) date.year = 2025;
    return is;
}

int Game::nextId = 1;
Game::Game() : id(nextId++) {
    title[0] = '\0';
    developer[0] = '\0';
    description[0] = '\0';
}
Game::Game(const char* t, const char*& dev, const RelDate& date, const Rating& rate, const char* desc)
    : releaseDate(date), rating(rate) id(nextId++) {
    setTitle(t);
    setDeveloper(dev);
    setDescription(desc);
}

const char* Game::getTitle() const { return title; }
const char* Game::getDeveloper() const { return developer; }
int Game::getId() const { return id; }
const char* Game::getDescription() const { return description; }
RelDate Game::getReleaseDate() const { return releaseDate; }
Rating Game::getRating() const { return rating; }

void Game::setTitle(const char* newTitle) { title = newTitle; }
void Game::setDeveloper(const char* newDeveloper) { developer = newDeveloper; }
void Game::setDescription(const char* newDesc) { description = newDesc; }
void Game::setReleaseDate(const RelDate& date) { releaseDate = date; }
void Game::setRating(const Rating& rate) { rating = rate; }

std::ostream& operator<<(std::ostream& os, const Game& game) {
    os << "---------------------------------\n";
    os << "Название: " << game.title << "\n";
    os << "Разработчик: " << game.developer << "\n";
    os << "ID: " << game.id << "\n";
    os << "Дата выхода: " << game.releaseDate << "\n";
    os << "Оценка: " << game.rating << "/10\n";
    os << "Описание: " << game.description << "\n";
    return os;
}

std::istream& operator>>(std::istream& is, Game& game) {
    std::cout << "Название игры: ";
    is.ignore();
    is.getline(game.title, sizeof(game.title));
    
    std::cout << "Разработчик: ";
    is.getline(game.developer, sizeof(game.developer));
    
    std::cout << "Дата выхода:\n";
    is >> game.releaseDate;
    
    is >> game.rating;
    
    std::cout << "Краткое описание: ";
    is.ignore();
    is.getline(game.description, sizeof(game.description));
    
    return is;
}

bool Game::containsTitle(const char* searchTerm) const {
    return std::strstr(title, searchTerm) != nullptr;
}

bool Game::containsDeveloper(const char* searchTerm) const {
    return std::strstr(developer, searchTerm) != nullptr;
}

GameDatabase::GameDatabase() : games(nullptr), size(0), capacity(0) {
    std::strcpy(currentFilename, "games_db.bin");
}
GameDatabase::GameDatabase(const char* filename) : games(nullptr), size(0), capacity(0) {
    std::strncpy(currentFilename, filename, sizeof(currentFilename) - 1);
    currentFilename[sizeof(currentFilename) - 1] = '\0';
}
GameDatabase::~GameDatabase() {
    delete[] games;
}

bool GameDatabase::addGame(const Game& game) {
    if (size >= capacity) {
        int newCapacity = (capacity == 0) ? 10 : capacity * 2;
        if (!resize(newCapacity)) return false;
    }
    games[size] = game;
    size++;
    return true;
}

bool GameDatabase::deleteGame(int index) {
    if (index < 0 || index >= size) return false;
    for (int i = index; i < size - 1; ++i) {
        games[i] = games[i + 1];
    }
    size--;
    return true;
}
int GameDatabase::getSize() const { return size; }
bool GameDatabase::isEmpty() const { return sizw == 0; }

Game& GameDatabase::operator[](int index) {
    return games[index];
}

const Game& GameDatabase::operator[](int index) const {
    return games[index];
}

int* GameDatabase::searchByTitle(const char* title, int& foundCount) const {
    int* results = new int[size];
    foundCount = 0;
    for (int i = 0; i < size(); ++i) {
        if (games[i].containsTitle(title)) {
            results[foundCount++] = i;
        }
    }
    return results;
}

int* GameDatabase::searchByDeveloper(const char* developer, int& foundCount) const {
    int* results = new int[size];
    foundCount = 0;
    for (int i = 0; i < size; ++i) {
        if (games[i].containsDeveloper(developer)) {
            results[foundCount++] = i;
        }
    }
    return results;
}

bool GameDatabase::save(const char* filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) return false;
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    
 for (int i = 0; i < size; ++i) {
        const Game& game = games[i];
        
        file.write(game.getTitle(), 50);
        file.write(game.getDeveloper(), 50);
        file.write(reinterpret_cast<const char*>(&game.getId()), sizeof(int));
        file.write(game.getDescription(), 500);
        
        RelDate date = game.getReleaseDate();
        Rating rate = game.getRating();
        file.write(reinterpret_cast<const char*>(&date), sizeof(RelDate));
        file.write(reinterpret_cast<const char*>(&rate), sizeof(Rating));
    }
    int nextId = Game::getNextId();
    file.write(reinterpret_cast<const char*>(&nextId), sizeof(nextId));
    return true;
}

bool GameDatabase::load(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) return false;
    
    int newSize;
    file.read(reinterpret_cast<char*>(&newSize), sizeof(newSize));
        if (newSize > capacity) {
        delete[] games;
        games = new Game[newSize];
        capacity = newSize;
    }
    size = newSize;
    
    for (int i = 0; i < size; ++i) {
        char title[50], developer[50], description[500];
        int id;
        RelDate date;
        Rating rate;
        
        file.read(title, 50);
        file.read(developer, 50);
        file.read(reinterpret_cast<char*>(&id), sizeof(int));
        file.read(description, 500);
        file.read(reinterpret_cast<char*>(&date), sizeof(RelDate));
        file.read(reinterpret_cast<char*>(&rate), sizeof(Rating));
        
        Game game(title, developer, date, rating, description);
        games[i] = game;
    }
    return true;
}

const char* GameDatabase::getCurrentFilename() const { return currentFilename; }
void GameDatabase::setCurrentFilename(const char* filename) {
    std::strncpy(currentFilename, filename, sizeof(currentFilename) - 1);
    currentFilename[sizeof(currentFilename) - 1] = '\0';
}
std::ostream& operator<<(std::ostream& os, const GameDatabase& db) {
    if (db.isEmpty()) {
        os << "База данных пуста.\n";
        return os;
    }
    
    os << "Всего игр: " << db.games.size() << "\n\n";
    for (size_t i = 0; i < db.games.size(); ++i) {
        os << i + 1 << ". " << db.games[i].getTitle() << "\n";
        os << "ID: " << db.games[i].getId() << " | Разработчик: " 
           << db.games[i].getDeveloper() << " | Рейтинг: " 
           << db.games[i].getRating() << "/10\n";
        os << "Дата выхода: " << db.games[i].getReleaseDate() << "\n";
        os << "Описание: " << db.games[i].getDescription() << "\n";
        os << "---------------------------------\n";
    }
    return os;
}

std::istream& operator>>(std::istream& is, GameDatabase& db) {
    Game newGame;
    is >> newGame;
    db.addGame(newGame);
    return is;
}
