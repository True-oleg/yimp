#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "menu.h"
#include "utils.h"
#define FILENAME "games_db.bin"
#define INIT_CAPACITY 10

int main(void) {
        GameArray* games = create_array(INIT_CAPACITY);
        if (!games) {
                printf("Ошибка создания базы данных.\n");
                return 1;
        }
        if (load(FILENAME, games)) {
                printf("Данные загружены из файла!\n");
        } else {
                printf("Файл не найден. Создана новая база данных.\n");
        }
        int choice;
        int running =1;
        while (running) {
                print_menu();
                choice = get_int_input("", 1, 7);
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
                                if (save(FILENAME, games)) {
                                        printf("Успешно сохранено!\n");
                                } else {
                                        printf("Ошибка сохранения данных!\n");
                                }
                                press_enter_to_continue();
                                break;
                        case 6:
                                if (load(FILENAME, games)) { 
                                        printf("Успешно загружено!\n");
                                } else {
                                        printf("Ошибка загрузки данных!\n");
                                }
                                press_enter_to_continue();
                                break;
                        case 7:
                                printf("Идёт сохранение данных...\n");
                                if (save(FILENAME, games)) { 
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
