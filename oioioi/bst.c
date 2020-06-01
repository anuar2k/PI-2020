#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SZ 32 //31 + 1 nullchar

typedef struct node {
    int key;
    char* value;
    struct node* parent;
    struct node* left;
    struct node* right;
} node;

node* add(node* tree, int key, char* value) {
    node* to_add = malloc(sizeof(*to_add));
    to_add->value = malloc(sizeof(*to_add->value) * (strlen(value) + 1));
    to_add->key = key;
    to_add->left = NULL;
    to_add->right = NULL;
    strcpy(to_add->value, value);

    node* prev = NULL;
    node* curr = tree;

    while (curr) {
        prev = curr;
        curr = key < curr->key ? curr->left : curr->right;
    }
    to_add->parent = prev;

    if (prev) {
        if (key < prev->key) {
            prev->left = to_add;
        }   
        else {
            prev->right = to_add;
        }
        return tree;
    }
    else {
        return to_add;
    }
}

node* find(node* tree, int key) {
    while (tree) {
        if (key == tree->key) {
            return tree;
        }
        else if (key < tree->key) {
            tree = tree->left;
        }
        else {
            tree = tree->right;
        }
    }
    return NULL;
}

node* succ(node* tree) {
    if (tree->right) {
        tree = tree->right;
        while (tree->left) {
            tree = tree->left;
        }
        return tree;
    }
    
    node* tmp = tree->parent;
    while (tmp && tmp->left != tree) {
        tree = tmp;
        tmp = tree->parent;
    }
    return tmp;
}

node* rmv(node* tree, int key) {
    node* to_delete = find(tree, key);
    if (to_delete) {
        if (!to_delete->left) {
            node* parent = to_delete->parent;
            node* right = to_delete->right;

            free(to_delete->value);
            free(to_delete);

            if (parent) {
                if (key < parent->key) {
                    parent->left = right;
                }
                else {
                    parent->right = right;
                }
                return tree;
            }
            else {
                return right;
            }
        }

        if (!to_delete->right) {
            node* parent = to_delete->parent;
            node* left = to_delete->left;
            
            free(to_delete->value);
            free(to_delete);

            if (parent) {
                if (key < parent->key) {
                    parent->left = left;
                }
                else {
                    parent->right = left;
                }
                return tree;
            }
            else {
                return left;
            }
        }

        node* successor = succ(to_delete);
        if (successor->key < successor->parent->key) {
            successor->parent->left = successor->right;
        }
        else {
            successor->parent->right = successor->right;
        }
        free(to_delete->value);
        to_delete->value = successor->value;
        to_delete->key = successor->key;
        free(successor);
        
        return tree;
    }
    return tree;
}

void freeTree(node* tree) {
    if (tree) {
        if (tree->left) {
            freeTree(tree->left);
        }
        if (tree->right) {
            freeTree(tree->right);
        }
        free(tree->value);
        free(tree);
    }
}

int main() {
    int a, r, f, key;
    char value[STR_SZ];
    node* tree = NULL;
    scanf("%d %d %d", &a, &r, &f);

    while (a--) {
        scanf("%d %s", &key, value);
        tree = add(tree, key, value);
    }
    while (r--) {
        scanf("%d", &key);
        tree = rmv(tree, key);
    }
    while (f--) {
        scanf("%d", &key);
        node* result = find(tree, key);

        if (result) {
            printf("%s\n", result->value);
        }
        else {
            printf("NO\n");
        }
    }
    freeTree(tree);
}