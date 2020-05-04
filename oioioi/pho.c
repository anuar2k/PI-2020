#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIME 53 //around 52, num of lower and uppercase letters
#define STR_SZ 31 //30 + 1 nullchar

typedef enum {
    NIL, EXISTS, DELETED
} state;

typedef struct kv_pair {
    state state;
    char *key;
    char *value;
} kv_pair;

typedef struct dict {
    kv_pair *dict;
    int n; //power of 2, >= m
    int m;
} dict;

//polynomial rolling hash function, assuming n is prime
//see: https://cp-algorithms.com/string/string-hashing.html
int hash_string(char *string, int m) {
    int result = 0;
    int prime_power = 1;
    while (*string) {
        result = (result + *string * prime_power) % m; //'a' == 1, otherwise: "a", "aa", "aaa"... == 0
        prime_power = (prime_power * PRIME) % m;
        string++;
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
    for (int i = 0; i < dict->n; i++) {
        if (dict->dict[i].state == EXISTS) {
            free(dict->dict[i].key);
            free(dict->dict[i].value);
        }
    }
    free(dict->dict);
}

void dict_add(dict *dict, char *key, char *value) {
    int i = 0;
    int h1 = hash_string(key, dict->m);
    while (i < dict->n) {
        //assuming n is power of 2, >= m
        //c1=c2=1/2 - this leads to triangular numbers, which are unique in [0..n-1]
        int hash = (h1 + (i + i * i) / 2) % dict->n;
        if (dict->dict[hash].state != EXISTS) {
            dict->dict[hash].key = malloc((strlen(key) + 1) * sizeof(*dict->dict[hash].key));
            dict->dict[hash].value = malloc((strlen(value) + 1) * sizeof(*dict->dict[hash].value));
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
    int h1 = hash_string(key, dict->m);
    while (i < dict->n) {
        //assuming n is power of 2, >= m
        //c1=c2=1/2 - this leads to triangular numbers, which are unique in [0..n-1]
        int hash = (h1 + (i + i * i) / 2) % dict->n;
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
    int h1 = hash_string(key, dict->m);
    while (i < dict->n) {
        //assuming n is power of 2, >= m
        //c1=c2=1/2 - this leads to triangular numbers, which are unique in [0..n-1]
        int hash = (h1 + (i + i * i) / 2) % dict->n;
        if (dict->dict[hash].state != NIL) {
            if (dict->dict[hash].state == EXISTS && strcmp(dict->dict[hash].key, key) == 0) {
                free(dict->dict[hash].key);
                free(dict->dict[hash].value);
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