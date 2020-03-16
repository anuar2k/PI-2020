#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool ascending(int n) {
    int lastDigit = n % 10;
    n /= 10;
    while (n > 0) {
        int digit = n % 10;
        n /= 10;
        if (digit > lastDigit) {
            return false;
        }
        lastDigit = digit;
    }
    return true;
}

int main() {
    size_t n;
    scanf("%zu", &n);

    char *sieve = calloc(n, sizeof(*sieve));

    sieve[0] = 1;
    sieve[1] = 1;
    for (int i = 2; i * i < n; i++) {
        if (!sieve[i]) {
            for (int j = 2 * i; j < n; j += i) {
                sieve[j] = 1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (!sieve[i] && ascending(i)) {
            printf("%d\n", i);
        }
    }
}