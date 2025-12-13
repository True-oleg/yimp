#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include "data.h"

void clear_input_buffer(void);
int get_int_input(const char* prompt, int min, int max);
void get_string_input(const char* prompt, char* buffer, int max_len);
void print_separator(void);
void print_game_detail(const Game* game);
void press_enter_to_continue(void);

#endif
