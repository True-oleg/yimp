#include "game.h"
#include <fstream>
#include <algorithm>

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
    os << (date.day < 10 ? "0" : "") << date.day << "."
       << (date.month < 10 ? "0" : "") << date.month << "."
       << date.year;
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
Game::Game() : id(nextId++) {}
Game::Game(const std::string& t, const std::string& dev, 
           const RelDate& date, const Rating& rate, const std::string& desc)
    : title(t), developer(dev), id(nextId++), description(desc), 
      releaseDate(date), rating(rate) {}

std::string Game::getTitle() const { return title; }
std::string Game::getDeveloper() const { return developer; }
int Game::getId() const { return id; }
std::string Game::getDescription() const { return description; }
RelDate Game::getReleaseDate() const { return releaseDate; }
Rating Game::getRating() const { return rating; }

void Game::setTitle(const std::string& newTitle) { title = newTitle; }
void Game::setDeveloper(const std::string& newDeveloper) { developer = newDeveloper; }
void Game::setDescription(const std::string& newDesc) { description = newDesc; }
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
    std::getline(is, game.title);
    
    std::cout << "Разработчик: ";
    std::getline(is, game.developer);
    
    std::cout << "Дата выхода:\n";
    is >> game.releaseDate;
    
    is >> game.rating;
    
    std::cout << "Краткое описание: ";
    is.ignore();
    std::getline(is, game.description);
    
    return is;
}

bool Game::containsTitle(const std::string& searchTerm) const {
    return title.find(searchTerm) != std::string::npos;
}

bool Game::containsDeveloper(const std::string& searchTerm) const {
    return developer.find(searchTerm) != std::string::npos;
}

GameDatabase::GameDatabase() : currentFilename("games_db.bin") {}
GameDatabase::GameDatabase(const std::string& filename) : currentFilename(filename) {}

bool GameDatabase::addGame(const Game& game) {
    games.push_back(game);
    return true;
}

bool GameDatabase::deleteGame(int index) {
    if (index < 0 || index >= static_cast<int>(games.size())) {
        return false;
    }
    games.erase(games.begin() + index);
    return true;
}

int GameDatabase::getSize() const { return games.size(); }
bool GameDatabase::isEmpty() const { return games.empty(); }

Game& GameDatabase::operator[](int index) {
    return games[index];
}

const Game& GameDatabase::operator[](int index) const {
    return games[index];
}

std::vector<int> GameDatabase::searchByTitle(const std::string& title) const {
    std::vector<int> results;
    for (size_t i = 0; i < games.size(); ++i) {
        if (games[i].containsTitle(title)) {
            results.push_back(i);
        }
    }
    return results;
}

std::vector<int> GameDatabase::searchByDeveloper(const std::string& developer) const {
    std::vector<int> results;
    for (size_t i = 0; i < games.size(); ++i) {
        if (games[i].containsDeveloper(developer)) {
            results.push_back(i);
        }
    }
    return results;
}

bool GameDatabase::save(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) return false;
    
    size_t size = games.size();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (const auto& game : games) {
        std::string title = game.getTitle();
        std::string developer = game.getDeveloper();
        std::string description = game.getDescription();
        int id = game.getId();
        RelDate date = game.getReleaseDate();
        Rating rating = game.getRating();
        
        size_t len = title.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(title.c_str(), len);
        
        len = developer.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(developer.c_str(), len);
        
        len = description.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(description.c_str(), len);
        file.write(reinterpret_cast<const char*>(&id), sizeof(id));
        file.write(reinterpret_cast<const char*>(&date), sizeof(date));
        file.write(reinterpret_cast<const char*>(&rating), sizeof(rating));
    }
    return true;
}

bool GameDatabase::load(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) return false;
    
    games.clear();
    
    size_t size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    for (size_t i = 0; i < size; ++i) {
        std::string title, developer, description;
        int id;
        RelDate date;
        Rating rating;
        
        size_t len;
        
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        title.resize(len);
        file.read(&title[0], len);
        
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        developer.resize(len);
        file.read(&developer[0], len);
        
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        description.resize(len);
        file.read(&description[0], len);
        
        file.read(reinterpret_cast<char*>(&id), sizeof(id));
        file.read(reinterpret_cast<char*>(&date), sizeof(date));
        file.read(reinterpret_cast<char*>(&rating), sizeof(rating));
        
        Game game(title, developer, date, rating, description);
        games.push_back(game);
    }
    return true;
}

std::string GameDatabase::getCurrentFilename() const { return currentFilename; }
void GameDatabase::setCurrentFilename(const std::string& filename) { currentFilename = filename; }

std::ostream& operator<<(std::ostream& os, const GameDatabase& db) {
    if (db.games.empty()) {
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
