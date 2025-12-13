#include "menu.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void print_menu(void) {
        print_separator();
        printf("[  База данных Steam  ]\n");
        print_separator();
        printf("1. Вывести все игры на экран\n");
        printf("2. Добавить игру\n");
        printf("3. Удалить игру\n");
        printf("4. Добавить или изменить описание\n");
        printf("5. Найти игру\n");
        printf("6. Сохранить измения\n");
        printf("7. Загрузить из файла\n");
        printf("8. Выход\n");
        print_separator();
        printf("\nВведите цифру, чтобы продолжить:\n");
}

void display(GameArray* array) {
        if (!array || array->size == 0) {
                printf("Нет игр для отображения!\n");
                return;
        }
        printf("\n[ Список игр ]\n");
        printf("Всего игр: %d\n\n", array->size);
        for (int i=0; i < array->size; i++) {
                printf("%d. %s\n", i+1, array->games[i].title);
                printf("id: %d | Разработчик: %s | Рейтинг: %.1f/10\n", array->games[i].id, array->game[i].developer, array->game[i].rating);
                printf(" Дата выхода: %02d.%02d.%d\n", array->games[i].rel_date.day, array->games[i].rel_date.month, array->games[i].rel_date.year);
                printf(" Описание: %s\n", array->games[i].desc);
                print_separator();
        }
}

void add_game(GameArray* array) {
        if (!array) return;
        printf("[ Добавить новую игру ]\n");
        Game new_game;
        static int next_id = 1;
        new_game.id = next_id++;

        get_string_input("Название игры: ", new_game.title, sizeof(new_game.title));
        get_string_input("Разработчик: ", new_game.developer, sizeof(new_game.developer));
        printf("Дата выхода:\n");
        new_game.rel_date.day = get_int_input(" День: ", 1, 31);
        new_game.rel_date.month = get_int_input(" Месяц: ", 1, 12);
        new_game.rel_date.year = get_int_input(" Год: ", 1980, 2025);
        new_game.rating.user_rate = get_int_input("Оценки: ", 1, 10);
        get_string_input("Краткое описание: ", new_game.desc, sizeof(new_game.desc));

        if (add_array(array, new_game)) {
                printf("\n Игра '%s' добавлена!\n", new_game.title);
        } else {
                printf("\nОшибка!\n");
        }
}

void delete_game(GameArray* array) {
        if (!array || array->size == 0) {
                printf("Нет игр...\n");
                return;
        }
        printf("\n[ Удаление игры ]\n");
        for (int i=0; i<array->size; i++) {
                printf("%d. %s", i+1, array->games[i].title);
                printf(" | id: %d", array->games[i].id);
                printf(" | Разработчик: %s | ", array->games[i].developer);
        }
        printf("\n0. Отмена\n");
        int choice = get_int_input("\nВыберете игру: ", 0, array->size);
        if (choice == 0) {
                printf("Удаление отменено.\n");
                return;
        }
        int index = choice-1;
        printf("\nВы точно хотите удалить?\n");
        printf("Название: %s\n", array->games[index].title);
        printf("Разработчик: %s\n", array->games[index].developer);
        printf("id: %d\n", array->games[index].id);
        printf("\n1. Да.\n");
        printf("2. Нет.\n");

        int confirm = get_int_input("Ваш выбор: ", 1, 2);
        if (confirm == 1) {
                char game_title[50];
                strcpy(game_title, array->games[index].title);
                if (delete_array(array, index)) {
                        printf("\nИгра '%s' удалена!\n", game_title);
                } else {
                        printf("\nОшибка!\n");
                }
        } else {
                printf("Отмена удаления.\n");
        }
}

void add_desc_game(GameArray* array) {
        if (!array || array->size == 0) {
                printf("Нет игр!\n");
                return;
        }
        printf("\n[ Добавление опиания ]\n");
        for (int i=0; i < array->size; i++) {
                printf("%d. %s\n", i+1, array->games[i].title);
        }
        int choice = get_int_input("\nВыберите игру: ", 1, array->size);
        char new_desc[500];
        get_string_input("Введите новое описание: ", new_desc, sizeof(new_desc));
        add_desc(&array->games[choice-1], new_desc);
        printf("Описание добавлено!\n");
}

void search_game(GameArray* array) {
        if (!array || array->size == 0) {
                printf("База данных пуста!\n");
                return;
        }
        printf("\n[ Поиск игры ]\n");
        printf("1. По названию\n");
        printf("2. По разработчику\n");
        int choice = get_int_input("Ваш выбор: ", 1, 2);
        char search_term[50];
        int found = 0;

        switch (choice) {
                case 1:
                        get_string_input("Введите название игры: ", search_term, 50);
                        printf("\nРезультаты поиска '%s':\n", search_term);
                        for (int i=0; i < array->size; i++) {
                                if (strstr(array->games[i].title, search_term) != NULL) {
                                        print_game_detail(&array->games[i]);
                                        found++;
                                }
                        }
                        break;
                case 2:
                        get_string_input("Введите развработчика: ", search_term, 50);
                        printf("\nРезультаты поиска '%s':\n", search_term);
                        for (int i=0; i < array->size; i++) { 
                                if (strstr(array->games[i].developer, search_term) != NULL) {
                                        print_game_detail(&array->games[i]);
                                        found++;
                                }
                        }
                        break;
        }
        if (found == 0) {
                printf("Игры не найдены.\n");
        }
}
