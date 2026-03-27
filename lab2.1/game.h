#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>
#include <vector>

class Rating {
private:
    float user_rate;
public:
    Rating(float rate = 0.0f);
    float getRate() const;
    void setRate(float rate);
    
    friend std::ostream& operator<<(std::ostream& os, const Rating& rating);
    friend std::istream& operator>>(std::istream& is, Rating& rating);
};

class RelDate {
private:
    int day;
    int month;
    int year;
public:
    RelDate(int d = 1, int m = 1, int y = 2000);
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    void setDate(int d, int m, int y);
    
    friend std::ostream& operator<<(std::ostream& os, const RelDate& date);
    friend std::istream& operator>>(std::istream& is, RelDate& date);
};

class Game {
private:
    std::string title;
    std::string developer;
    int id;
    std::string description;
    RelDate releaseDate;
    Rating rating;
    static int nextId;
    
public:
    Game();
    Game(const std::string& title, const std::string& developer, 
         const RelDate& date, const Rating& rate, const std::string& desc = "");
    
    std::string getTitle() const;
    std::string getDeveloper() const;
    int getId() const;
    std::string getDescription() const;
    RelDate getReleaseDate() const;
    Rating getRating() const;
    
    void setTitle(const std::string& newTitle);
    void setDeveloper(const std::string& newDeveloper);
    void setDescription(const std::string& newDesc);
    void setReleaseDate(const RelDate& date);
    void setRating(const Rating& rate);
    
    friend std::ostream& operator<<(std::ostream& os, const Game& game);
    friend std::istream& operator>>(std::istream& is, Game& game);
    
    bool containsTitle(const std::string& searchTerm) const;
    bool containsDeveloper(const std::string& searchTerm) const;
};

class GameDatabase {
private:
    std::vector<Game> games;
    std::string currentFilename;
    
public:
    GameDatabase();
    explicit GameDatabase(const std::string& filename);
    
    bool addGame(const Game& game);
    bool deleteGame(int index);
    int getSize() const;
    bool isEmpty() const;
    
    Game& operator[](int index);
    const Game& operator[](int index) const;
    
    std::vector<int> searchByTitle(const std::string& title) const;
    std::vector<int> searchByDeveloper(const std::string& developer) const;
    
    bool save(const std::string& filename);
    bool load(const std::string& filename);
    
    std::string getCurrentFilename() const;
    void setCurrentFilename(const std::string& filename);
    friend std::ostream& operator<<(std::ostream& os, const GameDatabase& db);
    friend std::istream& operator>>(std::istream& is, GameDatabase& db);
};

#endif // GAME_H
