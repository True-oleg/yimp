#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <cstring>

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
    char title[50];
    char developer[50];
    int id;
    char description[500];
    RelDate releaseDate;
    Rating rating;
    static int nextId;
    
public:
    Game();
    Game(const char* title, const char* developer, 
         const RelDate& date, const Rating& rate, const char* desc = "");
    
    const char* getTitle() const;
    const char* getDeveloper() const;
    int getId() const;
    const char* getDescription() const;
    RelDate getReleaseDate() const;
    Rating getRating() const;
    
    void setTitle(const char* newTitle);
    void setDeveloper(const char* newDeveloper);
    void setDescription(const char* newDesc);
    void setReleaseDate(const RelDate& date);
    void setRating(const Rating& rate);

    static int getNextId();
    static void setNextId(int id);
    
    friend std::ostream& operator<<(std::ostream& os, const Game& game);
    friend std::istream& operator>>(std::istream& is, Game& game);
    
    bool containsTitle(const char* searchTerm) const;
    bool containsDeveloper(const char* searchTerm) const;
};

class GameDatabase {
private:
    Game* games;
    int size;
    int capacity;
    char currentFilename[500];
    bool resize(int newCapacity);
    
public:
    GameDatabase();
    explicit GameDatabase(const char* filename);
    ~GameDatabase();
    
    bool addGame(const Game& game);
    bool deleteGame(int index);
    int getSize() const;
    bool isEmpty() const;
    void clear();
    
    Game& operator[](int index);
    const Game& operator[](int index) const;
    
    int* searchByTitle(const char* title, int& foundCount) const;
    int* searchByDeveloper(const char* developer, int& foundCount) const;
    
    bool save(const char* filename);
    bool load(const char* filename);
    
    const char* getCurrentFilename() const;
    void setCurrentFilename(const char* filename);
    friend std::ostream& operator<<(std::ostream& os, const GameDatabase& db);
    friend std::istream& operator>>(std::istream& is, GameDatabase& db);
};

#endif
