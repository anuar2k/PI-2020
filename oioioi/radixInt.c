#include <stdio.h>
#include <stdlib.h>

int extractDigit(int number, int digit) {
    int divisor = 1;
    while (--digit > 0) {
        divisor *= 10;
    }
    return (number / divisor) % 10;
}

void countingSort(int *a, int n, int d) {
    //static, by oszczedzic alokowanie histogramu na stosie
    static int hist[10];
    //okej, bo zaalokowaliśmy 2n pamięci
    int *result = &a[n];

    for (int i = 0; i < 10; i++) {
        hist[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        hist[extractDigit(a[i], d)]++;
    }

    for (int i = 1; i < 10; i++) {
        hist[i] += hist[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        int digit = extractDigit(a[i], d);
        hist[digit]--;
        result[hist[digit]] = a[i];
    }

    for (int i = 0; i < n; i++) {
        a[i] = result[i];
    }
}

void radixSort(int *a, int n, int k) {
    for (int i = 1; i <= k; i++) {
        countingSort(a, n, i);
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
        int *a = malloc(2 * n * sizeof(*a));
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }

        radixSort(a, n, k);

        for (int i = 0; i < n; i++) {
            printf("%d\n", a[i]);
        }

        free(a);
    }
}