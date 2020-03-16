#include <stdio.h>
#include <stdlib.h>

const int N = 10;

void intPrint(int *t, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d at %p\n", t[i], &t[i]);
    }
}

void doublePrint(double *t, int n) {
    for (int i = 0; i < n; i++) {
        printf("%f at %p\n", t[i], &t[i]);
    }
}

int main() {
    int t1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    double t2[] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8};

    int *ptr1 = t1;
    double *ptr2 = t2;

    intPrint(ptr1, N);
    doublePrint(ptr2, N);
}
