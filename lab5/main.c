#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"
#include "menu.h"
#include "utils.h"
#define DEF_FILENAME "games_db.bin"
#define INIT_CAPACITY 10

void get_name(char* buffer, int buffer_size) {
        printf("\n[ Выбор базы данных ]\n");
        printf("Введите имя файла для базы данных\n");
        printf("(или нажмите Enter для использования '%s'): ", DEF_FILENAME);
        if (fgets(buffer, buffer_size, stdin) == NULL) {
                strcpy(buffer, DEF_FILENAME);
                return;
        }
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
                buffer[len-1] = '\0';
        }
        if (strlen(buffer) == 0) {
                strcpy(buffer, DEF_FILENAME);
        }
        if (strstr(buffer, ".bin") == NULL) {
                strcat(buffer, ".bin");
        }
        printf("Используется файл: %s\n", buffer);
}

int main(void) {
        GameArray* games = create_array(INIT_CAPACITY);
        if (!games) {
                printf("Ошибка создания базы данных.\n");
                return 1;
        }

        char cur_filename[500];
        strcpy(cur_filename, DEF_FILENAME);
        get_name(cur_filename, sizeof(cur_filename));
        printf("\n '%s'\n", cur_filename);
        if (load(cur_filename, games)) {
                printf("Данные загружены из файла!\n");
        } else {
                printf("Файл не найден. Создана новая база данных.\n");
        }
        int choice;
        int running =1;
        while (running) {
                print_menu();
                choice = get_int_input("Введите номер: ", 1, 9);
                switch (choice) {
                        case 1:
                                display(games);
                                press_enter_to_continue();
                                break;
                        case 2:
                                add_game(games);
                                press_enter_to_continue();
                                break;
                        case 3:
                                delete_game(games);
                                press_enter_to_continue();
                                break;
                        case 4:
                                add_desc_game(games);
                                press_enter_to_continue();
                                break;
                        case 5:
                                search_game(games);
                                press_enter_to_continue();
                                break;
                        case 6:
                                if (save(cur_filename, games)) {
                                        printf("Успешно сохранено!\n");
                                } else {
                                        printf("Ошибка сохранения данных!\n");
                                }
                                press_enter_to_continue();
                                break;
                        case 7:
                                if (load(cur_filename, games)) { 
                                        printf("Успешно загружено!\n");
                                } else {
                                        printf("Ошибка загрузки данных!\n");
                                }
                                press_enter_to_continue();
                                break;
                        case 8:
                        {
                                char new_filename[500];
                                printf("\n[ Загрузка другой базы данных ]\n");
                                printf("Текущий файл: %s\n", cur_filename);
                                printf("Текущие данные будут утеряны!\n");
                                printf("Сохранить текущие данные?\n");
                                printf("1. Да\n");
                                printf("2. Нет\n");
                                printf("3. Отмена\n");
                                int load_choice = get_int_input("Ваш выбор: ", 1, 3);
                                if (load_choice == 1) {
                                        if (save(cur_filename, games)) {
                                                printf("Данные сохранены в '%s'\n", cur_filename);
                                        }
                                } else if (load_choice == 3) {
                                        printf("Загрузка отменена.\n");
                                        press_enter_to_continue();
                                        break;
                                }
                                get_string_input("Введите имя файла для загрузки: ", new_filename, sizeof(new_filename));
                                if (strstr(new_filename, ".bin") == NULL) {
                                        strcat(new_filename, ".bin");
                                }
                                GameArray* temp_games = create_array(INIT_CAPACITY);
                                if (!temp_games) {
                                        printf("Ошибка создания базы!\n");
                                        press_enter_to_continue();
                                        break;
                                }
                                if (load(new_filename, temp_games)) {
                                        free_array(games);
                                        games = temp_games;
                                        strcpy(cur_filename, new_filename);
                                        printf("Данные загружены из '%s'!\n", cur_filename);
                                        printf("Игр в базе: %d\n", games->size);
                                } else {
                                        free_array(temp_games);
                                        printf("Ошибка загрузки файла '%s'!\n", new_filename);
                                        printf("Файл не найден.\n");
                                }
                        }
                        case 8:
                                printf("Идёт сохранение данных...\n");
                                if (save(cur_filename, games)) { 
                                        printf("Успешно сохранено! Выход из программы.\n");
                                } else {
                                        printf("Ошибка сохранения данных!\n");
                                }
                                running = 0;
                                break;
                }
        }
        free_array(games);
        return 0;
}
