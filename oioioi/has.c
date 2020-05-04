#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIME 53 //around 52, num of lower and uppercase letters
#define STR_SZ 31 //30 + 1 nullchar

typedef struct kv_pair {
    char key[STR_SZ];
    char value[STR_SZ];
    struct kv_pair *next;
} kv_pair;

typedef struct dict {
    kv_pair **dict;
    int n;
} dict;

//polynomial rolling hash function, assuming n is prime
//see: https://cp-algorithms.com/string/string-hashing.html
int hash_string(char *string, int n) {
    int result = 0;
    int prime_power = 1;
    while (*string) {
        result = (result + *string * prime_power) % n; //'a' == 1, otherwise: "a", "aa", "aaa"... == 0
        prime_power = (prime_power * PRIME) % n;
        string++;
    }
    return result;
}

dict dict_init(int n) {
    dict result;
    result.n = n;
    result.dict = malloc(result.n * sizeof(*result.dict));
    for (int i = 0; i < n; i++) {
        result.dict[i] = NULL;
    }
    return result;
}

void dict_free(dict *dict) {
    for (int i = 0; i < dict->n; i++) {
        kv_pair *to_free = dict->dict[i];
        while (to_free) {
            kv_pair *next = to_free->next;
            free(to_free);
            to_free = next;
        }
    }
    free(dict->dict);
}

void dict_add(dict *dict, char *key, char *value) {
    int hash = hash_string(key, dict->n);
    kv_pair *to_add = malloc(sizeof(*to_add));
    strcpy(to_add->key, key);
    strcpy(to_add->value, value);
    to_add->next = dict->dict[hash];
    dict->dict[hash] = to_add;
}

char *dict_get(dict *dict, char *key) {
    kv_pair *kv_list = dict->dict[hash_string(key, dict->n)];
    while (kv_list && strcmp(key, kv_list->key)) {
        kv_list = kv_list->next;
    }
    return kv_list ? kv_list->value : NULL;
}

void dict_remove(dict *dict, char *key) {
    int hash = hash_string(key, dict->n);
    kv_pair *to_free;
    
    //first element must be treated specially
    if (strcmp(key, dict->dict[hash]->key) == 0) {
        to_free = dict->dict[hash];
        dict->dict[hash] = to_free->next;
    }
    else {
        kv_pair *kv_list = dict->dict[hash];
        while (strcmp(key, kv_list->next->key)) {
            kv_list = kv_list->next;
        }
        to_free = kv_list->next;
        kv_list->next = kv_list->next->next;
    }
    
    free(to_free);
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
            
            #ifdef DEBUG
            printf("Current key hash: %d\n", hash_string(key, n));
            for (int i = 0; i < n; i++) {
                printf("%d: ", i);
                if (dict.dict[i]) {
                    kv_pair *list = dict.dict[i];
                    while (list) {
                        printf("<%s, %s> ", list->key, list->value);
                        list = list->next;
                    }
                }
                else {
                    printf("NULL");
                }
                printf("\n");
            }
            #endif
        }

        dict_free(&dict);
    }
}