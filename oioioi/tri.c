#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool triangular(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i < j) {
                if (matrix[i][j] != 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    int n;
    scanf("%d", &n);

    int **matrix = malloc(n * sizeof(**matrix));
    matrix[0] = malloc(n * n * sizeof(matrix[0]));
    for (int i = 1; i < n; i++) {
        matrix[i] = matrix[0] + i * n;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("%s\n", triangular(matrix, n) ? "YES" : "NO");

    free(matrix[0]);
    free(matrix);
}