#include <stdio.h>
#include <stdlib.h>
#include<string.h>



struct Node {
    int key;
    struct Node *left, *right;
};


struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void findAncestors(struct Node* root, int key) {
    if (root == NULL) {
        return;
    }

    if (key < root->key) {
        findAncestors(root->left, key);
        printf("%d ", root->key);
    } else if (key > root->key) {
        findAncestors(root->right, key);
        printf("%d ", root->key);
    } else {
        
        printf("%d ", root->key);
    }
}


void printRange(struct Node* root, int k1, int k2) {
    if (root == NULL) {
        return;
    }

    if (k1 < root->key) {
        printRange(root->left, k1, k2);
    }

    if (k1 <= root->key && k2 >= root->key) {
        printf("%d ", root->key);
    }

    if (k2 > root->key) {
        printRange(root->right, k1, k2);
    }
}


struct Node* insert(struct Node* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }

    return root;
}


struct Node* buildBST(char exp[], int* index) {
    int num = 0;
    while (exp[*index] >= '0' && exp[*index] <= '9') {
        num = num * 10 + (exp[*index] - '0');
        (*index)++;
    }

    struct Node* root = createNode(num);

    if (exp[*index] == '(') {
        (*index)++;
        root->left = buildBST(exp, index);
        (*index)++;
    }

    if (exp[*index] == '(') {
        (*index)++;
        root->right = buildBST(exp, index);
        (*index)++;
    }

    return root;
}

int main() {
    char exp[1000];
    fgets(exp, sizeof(exp), stdin);

    int index = 0;
    struct Node* root = buildBST(exp, &index);

    char command;
    while (1) {
        scanf(" %c", &command);

        if (command == 'p') {
            int k1, k2;
            scanf("%d %d", &k1, &k2);
            printRange(root, k1, k2);
            printf("\n");
        } else if (command == 'a') {
            int k;
            scanf("%d", &k);
            findAncestors(root, k);
              printf("\n");
        } else if (command == 'e') {
            break;
        }
    }

    return 0;
}
