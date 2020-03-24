#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

        #ifdef SHOW_TIME
        clock_t t0, t1;
    	t0 = clock();
        #endif
        
        radixSort(strings, n, k);

        #ifdef SHOW_TIME
    	t1 = clock();
        #endif

        for (int i = 0; i < n; i++) {
            printf("%s\n", strings[i]);
        }
        
        #ifdef SHOW_TIME
        double result = (t1 - t0) * (1.0 / CLOCKS_PER_SEC);
        printf("Czas: %12.2e [s]\n", result);
        #endif

        free(memBlock);
        free(strings);
    }
}