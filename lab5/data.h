#ifndef DATA_H
#define DATA_H
#include <stdio.h>
#include <stdbool.h>

typedef struct { 
        float user_rate;
} Rating;

typedef struct { 
        int day;
        int month;
        int year;
} Rel_date;

typedef struct {
        char title[50];
        char developer[50];
        int id;
        char desc[500];
        Rel_date rel_date;
        Rating rating;
} Game;

typedef struct {
        Game* games;
        int size;
        int capacity;
} GameArray;

GameArray* create_array(int init_capacity);
void free_array(GameArray* array);
bool add_array(GameArray* array, Game game);
bool delete_array(GameArray* array, int index);
bool save(const char* filename, GameArray* array);
bool load(const char* filename, GameArray* array);
void add_desc(Game* game, const char* desc);

#endif
