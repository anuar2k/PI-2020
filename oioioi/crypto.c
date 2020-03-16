#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define N 101	//100 chars + nullbyte

bool isSmallChar(char character) {
    return character >= 'a' && character <= 'z';
}

bool isBigChar(char character) {
    return character >= 'A' && character <= 'Z';
}

bool isLetter(char character) {
    return isSmallChar(character) || isBigChar(character);
}

char shift(char character, int s) {
    if (isSmallChar(character)) {
        char baseNum = character - 'a';
        baseNum = (baseNum + s) % 26;
        character = 'a' + baseNum;
    }
    else if (isBigChar(character)) {
        char baseNum = character - 'A';
        baseNum = (baseNum + s) % 26;
        character = 'A' + baseNum;
    }

    return character;
}

int getS(char *message) {
    int result = 0;

    //skip trailing spaces
    while (*message != '\0' && !isLetter(*message)) {
        message++;
    }

    while (*message != '\0' && isLetter(*message)) {
        result++;
        message++;
    }

    return result;
}

void encrypt(char *message) {
    int s = getS(message);
    while (*message != '\0') {
        *message = shift(*message, s);
        message++;
    }
}

int main() {
    char message[N];
    fgets(message, N, stdin);
    encrypt(message);
    printf("%s\n", message);
}
