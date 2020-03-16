#include <stdio.h>
#include <stdlib.h>

void sort(int *t, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (t[j] > t[j + 1]) {
                int tmp = t[j];
                t[j] = t[j + 1];
                t[j + 1] = tmp;
            }
        }
    }
}

int split(int *t1, int *t2, int *t3, int n) {
    int t2Idx = 0;
    int t3Idx = 0;
    for (int i = 0; i < n; i++) {
        if (t1[i] % 2 == 0) {
            t2[t2Idx++] = t1[i];
        }
        else {
            t3[t3Idx++] = t1[i];
        }
    }

    return t2Idx;
}

void print(int *t, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d\n", t[i]);
    }
}

int main() {

    int n;
    scanf("%d", &n);

    //	allocate memory

    int *t1 = malloc(n * sizeof(*t1));
    int *t2 = malloc(n * sizeof(*t2));
    int *t3 = malloc(n * sizeof(*t3));

    for (int i = 0; i < n; i++) {
        scanf("%d", &t1[i]);
    }

    int e = split(t1, t2, t3, n);
    int o = n - e;

    sort(t2, e);
    sort(t3, o);

    printf("%d %d\n", e, o);
    print(t2, e);
    print(t3, o);

    //	free memory

    free(t1);
    free(t2);
    free(t3);
}
