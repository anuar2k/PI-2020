#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void heapify(int *a, int n, int idx) {
    int lChild = idx * 2 + 1;
    int rChild = idx * 2 + 2;
    int max = idx;

    if (lChild < n && a[lChild] > a[max]) {
        max = lChild;
    }

    if (rChild < n && a[rChild] > a[max]) {
        max = rChild;
    }

    if (max != idx) {
        swap(&a[max], &a[idx]);
        heapify(a, n, max);
    }
}

void heapSort(int *a, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(a, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(&a[0], &a[i]);
        heapify(a, i, 0);
    }
}

int main() {
    int Z;
    scanf("%d", &Z);

    while (Z--) {
        int n;
        scanf("%d", &n);
        int *a = malloc(n * sizeof(*a));
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }

        heapSort(a, n);

        for (int i = 0; i < n; i++) {
            printf("%d\n", a[i]);
        }

        free(a);
    }
}