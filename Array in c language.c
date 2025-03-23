#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int array1[2][3];
int array2[3][2];
int targetMatrix[2][2];

void impactMatrix(int array1[2][3], int array2[3][2]);

void randomValueGenerator(int ROWS, int COLS, int matrix[ROWS][COLS]);

void printMatrix(int ROWS, int COLS, int matrix[ROWS][COLS]);

void totalMatrix(int ROWS1, int COLS1, int array1[ROWS1][COLS1], int ROWS2, int COLS2, int array2[ROWS2][COLS2]);


int main() {
    srand(time(NULL));
    randomValueGenerator(2, 3, array1);
    randomValueGenerator(3, 2, array2);

    printf("####-1.Matris-####\n");
    printMatrix(2, 3, array1);

    printf("####-2.Matris####\n");
    printMatrix(3, 2, array2);

    printf("####-3.ImpactMatris####\n");
    impactMatrix(array1, array2);

    printf("####-4.SumMatris####\n");
    totalMatrix(2, 3, array1, 3, 2, array2);

    return 0;
}

void printMatrix(int ROWS, int COLS, int matrix[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", matrix[i][j]);
        }
        puts("");
    }
}

void randomValueGenerator(int ROWS, int COLS, int matrix[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matrix[i][j] = rand() % 100+1;
        }
    }
}

void impactMatrix(int array1[2][3], int array2[3][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            targetMatrix[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                targetMatrix[i][j] += array1[i][k] * array2[k][j];
            }
        }
    }
    printMatrix(2, 2, targetMatrix);
}

void totalMatrix(int ROWS1, int COLS1, int array1[ROWS1][COLS1], int ROWS2, int COLS2, int array2[ROWS2][COLS2]) {
    if (ROWS1 != ROWS2 || COLS1 != COLS2) {
        printf("undefined\n");
        return;
    }
    for (int i = 0; i < ROWS1; i++) {
        for (int j = 0; j < COLS1; j++) {
            targetMatrix[i][j] = array1[i][j] + array2[i][j];
        }
    }
    printMatrix(ROWS1, COLS1, targetMatrix);
}
