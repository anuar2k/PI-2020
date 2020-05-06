#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {
    const char *suffix = "-result";

    if (argc < 2) {
        perror("Nie podano pliku jako argument!\n");
        return 1;
    }

    FILE *source = fopen(argv[1], "r");

    if (source == NULL) {
        perror("Nie udalo sie otworzyc pliku\n");
    }

    char *targetName = malloc((strlen(argv[1]) + strlen(suffix) + 1) * sizeof(*targetName));
    strcpy(targetName, argv[1]);
    strcpy(targetName + strlen(targetName), suffix);

    FILE *target = fopen(targetName, "w");

    char prevprev = '\0';
    char prev = '\0';
    char curr;
    bool skipLine = false;
    bool skipBlock = false;
    while (prevprev != EOF) {
        curr = fgetc(source);

        if (prevprev == '/' && prev == '*') {
            skipBlock = true;
        }

        if (prevprev != '/' && prev == '*' && curr == '/') {
            prevprev = prev = curr = '\0';
            skipBlock = false;
        }

        if (prevprev == '/' && prev == '/') {
            skipLine = true;
        }

        if (prevprev != EOF && !skipBlock) {
            if (prevprev == '\n') {
                skipLine = false;
            }
            if (!skipLine && prevprev != '\0') {
                fputc(prevprev, target);
            }
        }

        prevprev = prev;
        prev = curr;
    }
}