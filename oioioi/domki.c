#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    int *t = malloc(n * sizeof(*t));

    int sumL = 0;
    int sumR = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &t[i]);
        sumR += t[i];
    }
    
    int result = -1;
    for (int i = 0; i < n; i++) {
        if (i - 1 >= 0) {
            sumL += t[i - 1];
        }
        sumR -= t[i];
        if (sumL == sumR) {
            result = i;
            break;
        }
    }
    printf("%d\n", result);
}