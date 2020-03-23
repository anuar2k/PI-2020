#include <stdio.h>
#include <stdlib.h>

void countingSort(char **strings, int n, int k) {
    //static, by oszczedzic alokowanie histogramu na stosie
    static int hist[10];
    //okej, bo zaalokowaliśmy 2n pamięci
    char **result = &strings[n];

    for (int i = 0; i < 10; i++) {
        hist[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        hist[strings[i][k] - '0']++;
    }

    for (int i = 1; i < 10; i++) {
        hist[i] += hist[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        int digit = strings[i][k] - '0';
        
        hist[digit]--;
        result[hist[digit]] = strings[i];
    }

    for (int i = 0; i < n; i++) {
        strings[i] = result[i];
    }
}

void radixSort(char **strings, int n, int k) {
    while (k--) {
        countingSort(strings, n, k);
    }
}

int main() {
    int Z;
    scanf("%d", &Z);

    while (Z--) {
        int n;
        int k;
        scanf("%d %d", &n, &k);

        //alokujemy 2n elementów po to, by móc utworzyć bufor dla counting sorta
        char **strings = malloc(2 * n * sizeof(*strings));
        char *memBlock = malloc(n * (k + 1) * sizeof(*memBlock));

        for (int i = 0; i < n; i++) {
            strings[i] = memBlock + i * (k + 1);
        }

        for (int i = 0; i < n; i++) {
            scanf("%s", strings[i]);
        }

        radixSort(strings, n, k);

        for (int i = 0; i < n; i++) {
            printf("%s\n", strings[i]);
        }

        free(memBlock);
        free(strings);
    }
}