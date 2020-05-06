#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main() {
    int n;
    
    scanf("%d", &n);

    int **T = malloc(n * sizeof(*T));
    int *memBlockT = malloc(n * n * sizeof(*memBlockT));

    for (int i = 0; i < n; i++) {
        T[i] = memBlockT + i * n;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &T[i][j]);
        }
    }

    int dX[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int dY[] = {-1, 0, 1, 1, 1, 0, -1, -1};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int result = 0;
            for (int d = 0; d < 8; d++) {
                if (i + dX[d] >= 0 && i + dX[d] < n && j + dY[d] >= 0 && j + dY[d] < n) {
                    result += T[i + dX[d]][j + dY[d]];
                }
            }
            printf("%d ", result);
        }
        printf("\n");
    }

    free(memBlockT);
    free(T);
}