#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PRIME 53 //around 52, num of lower and uppercase letters
#define STR_SZ 31 //30 + 1 nullchar

typedef struct kv_pair_ll {
    char key[STR_SZ];
    char value[STR_SZ];
    struct kv_pair_ll *next;
} kv_pair_ll;

typedef enum state { NIL, EXISTS, DELETED } state;

typedef struct kv_pair_arr {
    state state;
    char key[STR_SZ];
    char value[STR_SZ];
} kv_pair_arr;

typedef struct dict_ll {
    kv_pair_ll **dict_ll;
    int n;
} dict_ll;

typedef struct dict_arr {
    kv_pair_arr **dict_arr;
    int n;
} dict_arr;

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

dict_ll dict_ll_init(int n) {
    dict_ll result;
    result.n = n;
    result.dict_ll = malloc(result.n * sizeof(*result.dict_ll));
    for (int i = 0; i < n; i++) {
        result.dict_ll[i] = NULL;
    }
    return result;
}

dict_arr dict_arr_init(int n) {
    dict_arr result;
    result.n = n;
    result.dict_arr = malloc(result.n * sizeof(*result.dict_arr));
    for (int i = 0; i < n; i++) {
        result.dict_arr[i] = malloc(result.n * sizeof(*result.dict_arr[i]));
        for (int j = 0; j < n; j++) {
            result.dict_arr[i][j].state = NIL;
        }
    }
    return result;
}

void dict_ll_free(dict_ll *dict_ll) {
    for (int i = 0; i < dict_ll->n; i++) {
        kv_pair_ll *to_free = dict_ll->dict_ll[i];
        while (to_free) {
            kv_pair_ll *next = to_free->next;
            free(to_free);
            to_free = next;
        }
    }
    free(dict_ll->dict_ll);
}

void dict_arr_free(dict_arr *dict_arr) {
    for (int i = 0; i < dict_arr->n; i++) {
        free(dict_arr->dict_arr[i]);
    }
    free(dict_arr->dict_arr);
}

void dict_ll_add(dict_ll *dict_ll, char *key, char *value) {
    int hash = hash_string(key, dict_ll->n);
    kv_pair_ll *to_add = malloc(sizeof(*to_add));
    strcpy(to_add->key, key);
    strcpy(to_add->value, value);
    to_add->next = dict_ll->dict_ll[hash];
    dict_ll->dict_ll[hash] = to_add;
}

void dict_arr_add(dict_arr *dict_arr, char *key, char *value) {
    int hash = hash_string(key, dict_arr->n);
    kv_pair_arr to_add;
    to_add.state = EXISTS;
    strcpy(to_add.key, key);
    strcpy(to_add.value, value);
    int i = 0;
    while (dict_arr->dict_arr[hash][i].state == EXISTS) {
        i++;
    }
    dict_arr->dict_arr[hash][i] = to_add;
}

char *dict_ll_get(dict_ll *dict_ll, char *key) {
    kv_pair_ll *kv_list = dict_ll->dict_ll[hash_string(key, dict_ll->n)];
    while (kv_list && strcmp(key, kv_list->key)) {
        kv_list = kv_list->next;
    }
    return kv_list ? kv_list->value : NULL;
}

char *dict_arr_get(dict_arr *dict_arr, char *key) {
    int hash = hash_string(key, dict_arr->n);
    int i = 0;
    while (i < dict_arr->n && (dict_arr->dict_arr[hash][i].state == DELETED || (dict_arr->dict_arr[hash][i].state == EXISTS && strcmp(key, dict_arr->dict_arr[hash][i].key)))) {
        i++;
    }
    return (i < dict_arr->n && dict_arr->dict_arr[hash][i].state == EXISTS) ? dict_arr->dict_arr[hash][i].value : NULL;
}

void dict_ll_remove(dict_ll *dict_ll, char *key) {
    int hash = hash_string(key, dict_ll->n);
    kv_pair_ll *to_free;
    
    //first element must be treated specially
    if (strcmp(key, dict_ll->dict_ll[hash]->key) == 0) {
        to_free = dict_ll->dict_ll[hash];
        dict_ll->dict_ll[hash] = to_free->next;
    }
    else {
        kv_pair_ll *kv_list = dict_ll->dict_ll[hash];
        while (strcmp(key, kv_list->next->key)) {
            kv_list = kv_list->next;
        }
        to_free = kv_list->next;
        kv_list->next = kv_list->next->next;
    }
    
    free(to_free);
}

void dict_arr_remove(dict_arr *dict_arr, char *key) {
    int hash = hash_string(key, dict_arr->n);
    int i = 0;
    while (dict_arr->dict_arr[hash][i].state != EXISTS || strcmp(key, dict_arr->dict_arr[hash][i].key)) {
        i++;
    }
    dict_arr->dict_arr[hash][i].state = DELETED;
}

int main() {
    int Z;
    scanf("%d", &Z);

    #ifdef SHOW_TIME
    clock_t time_ll = 0, time_arr = 0;
    clock_t t0, t1;
    #endif

    while (Z--) {
        int n, k;
        char op[2], key[STR_SZ], value[STR_SZ], *result;

        scanf("%d %d", &n, &k);
        dict_arr dict_arr = dict_arr_init(n);
        dict_ll dict_ll = dict_ll_init(n);

        while (k--) {
            scanf("%s %s", op, key);
            switch(op[0]) {
                case 'a':
                    scanf("%s", value);
                    #ifdef SHOW_TIME
                    t0 = clock();
                    #endif
                    dict_arr_add(&dict_arr, key, value);
                    #ifdef SHOW_TIME
                    t1 = clock();
                    time_arr += t1 - t0;
                    dict_ll_add(&dict_ll, key, value);
                    t0 = clock();
                    time_ll += t0 - t1;
                    #endif
                    break;
                case 'g':
                    #ifdef SHOW_TIME
                    t0 = clock();
                    #endif
                    result = dict_arr_get(&dict_arr, key);
                    #ifdef SHOW_TIME
                    t1 = clock();
                    time_arr += t1 - t0;
                    result = dict_ll_get(&dict_ll, key);
                    t0 = clock();
                    time_ll += t0 - t1;
                    #endif
                    printf("%s\n", (result ? result : ""));
                    break;
                case 'r':
                    #ifdef SHOW_TIME
                    t0 = clock();
                    #endif
                    dict_arr_remove(&dict_arr, key);
                    #ifdef SHOW_TIME
                    t1 = clock();
                    time_arr += t1 - t0;
                    dict_ll_remove(&dict_ll, key);
                    t0 = clock();
                    time_ll += t0 - t1;
                    #endif
                    break;
            }
        }

        dict_ll_free(&dict_ll);
        dict_arr_free(&dict_arr);
    }

    #ifdef SHOW_TIME
    double result_arr = time_arr * (1.0 / CLOCKS_PER_SEC);
    double result_ll = time_ll * (1.0 / CLOCKS_PER_SEC);
    printf("Czas: %f [s]\n", result_arr);
    printf("Czas: %f [s]\n", result_ll);
    #endif
}