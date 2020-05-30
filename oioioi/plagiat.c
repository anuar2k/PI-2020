#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t STR_SZ = 201; //200 + 1 nullchar

    char a_buf[STR_SZ];
    char b_buf[STR_SZ];
    char* a = a_buf;
    char* b = b_buf;

    getline(&a, &STR_SZ, stdin);
    getline(&b, &STR_SZ, stdin);

    int m = strlen(a);
    int n = strlen(b);
    
    int* v0 = malloc((n + 1) * sizeof(*v0));
    int* v1 = malloc((n + 1) * sizeof(*v1));

    for (int i = 0; i < n + 1; ++i) {
        v0[i] = i;
    }

    for (int i = 0; i < m; ++i) {
        v1[0] = i + 1;

        for (int j = 0; j < n; ++j) {
            int deletion_cost = v0[j + 1] + 1;
            int insertion_cost = v1[j] + 1;
            int substitution_cost = v0[j] + (a[i] != b[j]);

            int new_val = deletion_cost;
            if (insertion_cost < new_val) {
                new_val = insertion_cost;
            }
            if (substitution_cost < new_val) {
                new_val = substitution_cost;
            }

            v1[j + 1] = new_val;
        }

        int* swap = v0;
        v0 = v1;
        v1 = swap;
    }

    printf("%d\n", v0[n]);

    free(v0);
    free(v1);
}