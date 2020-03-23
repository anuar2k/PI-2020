#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(int *a, int left, int right) {
    swap(&a[rand() % (right - left + 1) + left], &a[right]);

    int pivot = a[right];
    int mid = left - 1;

    for (int i = left; i < right; i++) {
        if (a[i] < pivot) {
            mid++;
            swap(&a[mid], &a[i]);
        }
    }

    mid++;
    swap(&a[mid], &a[right]);
    return mid;
}

void quickSort(int *a, int left, int right) {
    if (left < right) {
        int mid = partition(a, left, right);
        quickSort(a, left, mid - 1);
        quickSort(a, mid + 1, right);
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

        quickSort(a, 0, n - 1);

        for (int i = 0; i < n; i++) {
            printf("%d\n", a[i]);
        }

        free(a);
    }
}