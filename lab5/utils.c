#include "utils.h"
#include <stdio.h>
#include <string.h>

void clear_input_buffer(void) {
        int c;
        while ((c=getchar()) != '\n' && c != EOF);
}

int get_int_input(const char* prompt, int min, int max) {
        int value;
        char buffer[100];
        while (1) {
                printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                continue;
        }
        if (sscanf(buffer, "%d", &value) == 1 && value >= min && value <= max) {
                return value;
        }
        printf("Ошибка! Введите число от %d до %d\n", min, max);
        }
}

void get_string_input(const char* prompt, char* buffer, int max_len) { 
        printf("%s", prompt);
        if (fgets(buffer, max_len, stdin) == NULL) {
                buffer[0] = '\0';
                return;
        }
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
                buffer[len-1] = '\0';
        }
}

void print_separator(void) {
        printf("---------------------------------\n");
}

void print_game_details(const Game* game) {
        if (!game) return;
        print_separator;
        printf("Название: %s\n", game->title);
        printf("Разработчик: %s\n", game->developer);
        printf("id: %d\n", game->id);
        printf("Дата выхода: %02d.%02d.%d\n", game->rel_date.day, game->rel_date.month, game->rel_date>
        printf("Оценка: %.1f/10\n", game->rating.user_rate);
        printf("Описание: %s\n", game->desc);
}

void press_enter_to_continue(void) {
        printf("\nНажмите дважды Enter, чтобы продолжить.");
        clear_input_buffer();
        getchar();
}
