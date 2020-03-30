#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long call_start;
    char number[16]; //15 + 1 nullchar
} incoming;

int main() {
    int n;
    scanf("%d", &n);

    incoming *i_calls = malloc(n * sizeof(*i_calls));
    size_t queueTail = 0;
    size_t queueHead = 0;

    char op[2]; //1 + 1 nullchar

    while (n--) {
        scanf("%s", op);
        if (op[0] == 'a') {
            scanf("%lld", &i_calls[queueHead].call_start);
            scanf("%s", i_calls[queueHead].number);
            queueHead++;
        }
        else {
            long long call_end;
            scanf("%lld", &call_end);
            printf("%s %lld\n", i_calls[queueTail].number, call_end - i_calls[queueTail].call_start);
            queueTail++;
        }
    }

    free(i_calls);
}