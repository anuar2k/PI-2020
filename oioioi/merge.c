#include <stdio.h>
#include <stdlib.h>


void sort(int* t, int n) {
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

int merge(int* t1, int* t2, int* t3, int m, int n) {
    int t1Idx = 0;
    int t2Idx = 0;
    int t3Idx = 0;

    int first = 1;
    int lastVal;

    while (t1Idx != m || t2Idx != n) {
        if (t2Idx == n || (t1Idx < m && t1[t1Idx] < t2[t2Idx])) {
            if (first || t1[t1Idx] > lastVal) {
                lastVal = t1[t1Idx];
                t3[t3Idx++] = lastVal;
            }
            t1Idx++;
        }
        else {
            if (first || t2[t2Idx] > lastVal) {
                lastVal = t2[t2Idx];
                t3[t3Idx++] = lastVal;
            }
            t2Idx++;
        }
        first = 0;
    }

    return t3Idx;
}

void print(int* t, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d\n", t[i]);
    }
}

int main() {

	int m, n;
	scanf("%d %d", &m, &n);

	//	define and allocate memory for t1, t2, t3
    int* t1 = (int*)malloc(m * sizeof(int));
    int* t2 = (int*)malloc(n * sizeof(int));
    int* t3 = (int*)malloc((m + n) * sizeof(int));

	for (int i = 0; i < m; i++) {
		scanf("%d", &t1[i]);
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", &t2[i]);
	}

	sort(t1, m);
	sort(t2, n);

	int l = merge(t1, t2, t3, m, n);

	print(t3, l);

	//	free memory
    free(t1);
    free(t2);
    free(t3);
}
