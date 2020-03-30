#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    long long *stack = malloc(n * sizeof(*stack));
    size_t stackSize = 0;
    
    char *stringBuffer = malloc((k + 1) * sizeof(*stringBuffer));

    n = n * 2 - 1; //n operands, n - 1 operators

    while (n--) {
        int a, b, result;
        scanf("%s", stringBuffer);
        switch (stringBuffer[0]) {
            case '+':
                b = stack[--stackSize];
                a = stack[--stackSize];
                result = a + b;
                break;
            case '-':
                b = stack[--stackSize];
                a = stack[--stackSize];
                result = a - b;
                break;
            case '*':
                b = stack[--stackSize];
                a = stack[--stackSize];
                result = a * b;
                break;
            case '/':
                b = stack[--stackSize];
                a = stack[--stackSize];
                result = a / b;
                break;
            default:
                result = atoi(stringBuffer);
                break;
        }
        stack[stackSize++] = result;
    }

    printf("%lld\n", stack[0]);
    free(stack);
    free(stringBuffer);
}