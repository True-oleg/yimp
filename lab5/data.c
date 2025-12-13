#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GameArray* create_array(int init_capacity) {
        GameArray* array = (GameArray*)malloc(sizeof(GameArray));
        if (!array) return NULL;
        array->games = (Game*)malloc(init_capacity * sizeof(Game));
        if (!array->games) {
                free(array);
                return NULL;
        }
        array->size = 0;
        array->capacity = init_capacity;
        return array;
}

void free_array(GameArray* array) {
        if(array) {
                free(array->games);
                free(array);
        }
}

bool add_array(GameArray* array, Game game) {
        if (!array) return false;
        if (array->size >= array->capacity) {
                int new_capacity = array->capacity * 2;
                Game* new_games = (Game*)realloc(array->games, new_capacity * sizeof(Game));
                if (!new_games) return false;
                array->games = new_games;
                array->capacity = new_capacity;
        }
        array->games[array->size] = game;
array->size++;
        return true;
}

bool delete_array(GameArray* array, int index) {
        if (!array || index < 0 || index>=array->size) {
                return false;
        }
        for (int i=index; i<array->size-1; i++) {
                array->games[i] = array->games[i+1];
        }
        array->size--;
        if (array->size >0 && array->size <= array->capacity / 4) {
                int new_capacity = array->capacity/2;
                Game* new_games = (Game*)realloc(array->games, new_capacity * sizeof(Game));
                if (new_games) {
                        array->games = new_games;
                        array->capacity = new_capacity;
                }
        }
        return true;
}

bool save(const char* filename, GameArray* array) {
        if (!array || !filename) return false;
        FILE* file = fopen(filename, "wb");
        if (!file) return false;
        fwrite(&array->size, sizeof(int), 1, file);
        fwrite(array->games, sizeof(Game), array->size, file);
        fclose(file);
        return true;
}

bool load(const char* filename, GameArray* array) {
        if (!array || !filename) return false;
        FILE* file = fopen(filename, "rb");
        if (!file) return false;
        int size;
        if (fread(&size, sizeof(int), 1, file) !=1) {
                fclose(file);
                return false;
        }
        if (size > array->capacity) {
                Game* new_games = (Game*)realloc(array->games, size * sizeof(Game));
                if (!new_games) {
                        fclose(file);
                        return false;
                }
                array->games = new_games;
                array->capacity = size;
        }
        if (fread(array->games, sizeof(Game), size, file) != size) {
                fclose(file);
                return false;
        }
        array->size = size;
        fclose(file);
        return true;
}

void add_desc(Game* game, const char* desc) {
        if (game && desc) {
                strncpy(game->desc, desc, sizeof(game->desc)-1);
                game->desc[sizeof(game->desc)-1] = '\0';
        }
}
