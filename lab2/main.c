#include <stdio.h>
#include <stdlib.h>

int posled(int arr[], int n, int nom, int count, int prev) {

if (count == 3) {
return 1;
}

if (nom >= n) {
return 0;
}

if (arr[nom] > prev) {
        if (posled(arr, n, nom + 1, count + 1, arr[nom])) {
        return 1;
        }
}

 if (posled(arr, n, nom + 1, 1, arr[nom])) {
        return 1;
  }

 if (posled(arr, n, nom + 1, count, prev)) {
        return 1;
 }

return 0;
} //конец проверяющей функции

int vvod(int **arr, int *n) {
        printf("Введите количество элементов в массиве:\n");

        if (scanf("%d", n) != 1 || *n <= 0) {
                printf("Значение некорректно. Введите целое число.\n");
                return 0;
        }

        *arr = (int*)malloc(*n * sizeof(int));
        if (*arr == NULL) {
                printf("Не удалось выделить память :(\n");
                free(*arr);
                return 0;
        }

        printf("Введите ваш массив:\n");
        for (int i=0; i<*n; i++) {
                if (scanf("%d", &(*arr)[i]) != 1) {
                        printf("Значение некоррректно. Введите целое число.\n");
                        free(*arr);
                        return 0;
                }
        }
return 1;
} // конец функции ввода

int main() {
        int *arr = NULL;
        int n = 0;

        if (!vvod(&arr, &n)) {
                return 1;
        }

        int res1 = posled(arr, n, 0, 0, -100);
        printf("Результат: %s\n", res1 ? "true" : "false");

free(arr);
return 0;
}
