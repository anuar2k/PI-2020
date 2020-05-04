#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIME_1 53 //around 52, num of lower and uppercase letters
#define PRIME_2 89
#define STR_SZ 31 //30 + 1 nullchar

typedef enum {
    NIL, EXISTS, DELETED
} state;

typedef struct kv_pair {
    state state;
    char key[STR_SZ];
    char value[STR_SZ];
} kv_pair;

typedef struct dict {
    kv_pair *dict;
    int n; //power of 2, >= m
    int m;
} dict;

//polynomial rolling hash function, assuming n is prime
//see: https://cp-algorithms.com/string/string-hashing.html
int hash_string_primary(char *string, int m) {
    int result = 0;
    int prime_power = 1;
    while (*string) {
        result = (result + *string * prime_power) % m; //'a' == 1, otherwise: "a", "aa", "aaa"... == 0
        prime_power = (prime_power * PRIME_1) % m;
        string++;
    }
    return result;
}

//seconary hash must be always odd
int hash_string_secondary(char *string, int m) {
    int result = 0;
    int prime_power = 1;
    while (*string) {
        result = (result + *string * prime_power) % m; //'a' == 1, otherwise: "a", "aa", "aaa"... == 0
        prime_power = (prime_power * PRIME_2) % m;
        string++;
    }
    if (result % 2 == 0) {
        result++;
    }
    return result;
}

dict dict_init(int m) {
    dict result;
    result.m = m;
    result.n = 2;

    while (result.n < result.m) {
        result.n *= 2;
    }

    result.dict = malloc(result.n * sizeof(*result.dict));

    for (int i = 0; i < result.n; i++) {
        result.dict[i].state = NIL;
    }

    return result;
}

void dict_free(dict *dict) {
    free(dict->dict);
}

void dict_add(dict *dict, char *key, char *value) {
    int i = 0;
    int h1 = hash_string_primary(key, dict->m);
    int h2 = hash_string_secondary(key, dict->n);
    while (i < dict->n) {
        //assuming m is prime, n is power of 2, >= m, secondary hash is always odd
        int hash = (h1 + i * h2) % dict->n;
        if (dict->dict[hash].state != EXISTS) {
            strcpy(dict->dict[hash].key, key);
            strcpy(dict->dict[hash].value, value);
            dict->dict[hash].state = EXISTS;
            return;
        }
        i++;
    }
}

char *dict_get(dict *dict, char *key) {
    int i = 0;
    int h1 = hash_string_primary(key, dict->m);
    int h2 = hash_string_secondary(key, dict->n);
    while (i < dict->n) {
        //assuming m is prime, n is power of 2, >= m, secondary hash is always odd
        int hash = (h1 + i * h2) % dict->n;
        if (dict->dict[hash].state != NIL) {
            if (dict->dict[hash].state == EXISTS && strcmp(dict->dict[hash].key, key) == 0) {
                return dict->dict[hash].value;
            }
        }
        else {
            break;
        }
        i++;
    }
    return NULL;
}

void dict_remove(dict *dict, char *key) {
    int i = 0;
    int h1 = hash_string_primary(key, dict->m);
    int h2 = hash_string_secondary(key, dict->n);
    while (i < dict->n) {
        //assuming m is prime, n is power of 2, >= m, secondary hash is always odd
        int hash = (h1 + i * h2) % dict->n;
        if (dict->dict[hash].state != NIL) {
            if (dict->dict[hash].state == EXISTS && strcmp(dict->dict[hash].key, key) == 0) {
                dict->dict[hash].state = DELETED;
                return;
            }
        }
        else {
            return;
        }
        i++;
    }
}

int main() {
    int Z;
    scanf("%d", &Z);

    while (Z--) {
        int n, k;
        char op[2], key[STR_SZ], value[STR_SZ], *result;

        scanf("%d %d", &n, &k);
        dict dict = dict_init(n);

        while (k--) {
            scanf("%s %s", op, key);
            switch(op[0]) {
                case 'a':
                    scanf("%s", value);
                    dict_add(&dict, key, value);
                    break;
                case 'g':
                    result = dict_get(&dict, key);
                    printf("%s\n", (result ? result : ""));
                    break;
                case 'r':
                    dict_remove(&dict, key);
                    break;
            }
        }

        dict_free(&dict);
    }
}