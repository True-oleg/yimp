#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int main(int argc, char **argv) {

        char *filename = argv[1];
        FILE *file = fopen(filename, "r");
        if(file == NULL) {
                printf("Не удалось открыть файл '%s'\n", filename);
                return 1;
        }


        int N, M;
        if(fscanf(file, "%d %d", &N, &M) != 2) {
                printf("Неверный формат. Ожидается: N M\n");
                fclose(file);
                return 1;
        }
        if(N <= 0 || M <= 0) {
                printf("Некорректные размеры матрицы: %d x %d\n", N, M);
                fclose(file);
                return 1;
        }

        if (N<2 || M<3) {
                printf("Матрица мала! Введите до элемента а(23)\n");
                fclose(file);
                return 1;
        }

int **matrix = (int**)malloc(N * sizeof(int*));
        if (matrix == NULL) {
                printf("Не удалось выделить память для матрицы\n");
                fclose(file);
                return 1;
        }

        for (int i=0; i<N; i++) {
                matrix[i] = (int*)malloc(M * sizeof(int));
                if (matrix[i] == NULL) {
                        printf("Не удалось выделить память для строки\n");
                        for (int j=0; j<M; j++) {
                                free(matrix[j]);
                        }
                        free(matrix);
                        fclose(file);
                        return 1;
                }
        }

        for (int i=0; i<N; i++) {
                for (int j=0; j<M; j++) {
                        if(fscanf(file, "%d", &matrix[i][j]) != 1) {
                                printf("Не удалось считать элемент [%d][%d]\n", i, j);
                                for(int k=0; k<N; k++)
                                        free(matrix[k]);
                                free(matrix);
                                fclose(file);
                                return 1;
                        }
                }
        }

fclose(file);


        //Вывод
        printf("Исходная матрица размером %d x %d: \n", N, M);
        for(int i=0; i<N; i++) {
                for(int j=0; j<M; j++) {
                        printf("%d\t", matrix[i][j]);
                }
                printf("\n");
        }
        printf("\n");

        double *arifm = (double*)malloc(N * sizeof(double));
        if (arifm == NULL) {
                printf("Не удалось выделить память для массива ср. арифм. строк\n");
                for(int i=0; i<N; i++) {
                        free(matrix[i]);
                }
                free(matrix);
                return 1;
        }

        printf("1.) Средние арифметические строк: \n");
        printf("Одномерный массив: { ");
        for(int i=0; i<N; i++) {
                int sum = 0;
                for(int j=0; j<M; j++)
                        sum += matrix[i][j];
                arifm[i] = (double)sum / M;
                printf("%.2f ", sum, arifm[i]);
        }
        printf("}\n");
        printf("\n");

        //col - столбец, str - строка
        int min_col = matrix[0][2];
        int min_str = 0;

        printf("2.) Поиск наименьшего элемента 3-его столбца: \n");
        printf("Элементы столбца: ");
        for(int i=0; i<N; i++) {
                printf("%d ", matrix[i][2]);
                if (matrix[i][2] < min_col) {
                        min_col = matrix[i][2];
                        min_str = i;
                }
        }
        printf("\n");
        printf("Наименьший элемент: %d\n", min_col);
        printf("\n");

        int str2 = 1;
        int col3 = 2;

        printf("3.) Обмен элементов:\n");
        int temp = matrix[min_str][2];
        matrix[min_str][2] = matrix[str2][col3];
        matrix[str2][col3] = temp;

        printf("а(%d2) = %d\n", min_str + 1, matrix[min_str][2]);
        printf("а(%d%d) = %d\n", str2 + 1, col3 + 1, matrix[str2][col3]);
        printf("\n");

        printf("Матрица после обмена:\n");
        for(int i=0; i<N; i++) {
                for(int j=0; j<M; j++)
                        printf("%d\t", matrix[i][j]);
                printf("\n");
        }
        printf("\n");

        //память
        for(int i=0; i<N; i++)
                free(matrix[i]);
        free(matrix);
        free(arifm);

        return 0;

}
