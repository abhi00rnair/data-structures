#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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



int maxKey(struct Node* root) {
    while (root->right != NULL) {
        root = root->right;
    }
    return root->key;
}


int minKey(struct Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root->key;
}

int maxSumBST(struct Node* root, int* maxSum) {
    if (root == NULL) {
        return 0;
    }

    int leftSum = maxSumBST(root->left, maxSum);
    int rightSum = maxSumBST(root->right, maxSum);

    int currentSum = leftSum + rightSum + root->key;

    if ((root->left == NULL || root->key > maxKey(root->left)) &&
        (root->right == NULL || root->key < minKey(root->right))) {

        if (currentSum > *maxSum) {
            *maxSum = currentSum;
        }

        return currentSum;
    }

    return 0; 
}

void levelordertraversal(struct Node* root) {
    if (root == NULL)
        return;

    struct Node** queue = (struct Node**)malloc(sizeof(struct Node*) * 1000);
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        
        struct Node* tempNode = queue[front++];
        printf("%d ", tempNode->key);

        
        if (tempNode->left != NULL)
            queue[rear++] = tempNode->left;

        
        if (tempNode->right != NULL)
            queue[rear++] = tempNode->right;
    }

    
    free(queue);
}




struct Node* build(char exp[], int* index) {
    int num = 0;
    while (exp[*index] >= '0' && exp[*index] <= '9') {
        num = num * 10 + (exp[*index] - '0');
        (*index)++;
    }

    struct Node* root = createNode(num);

    if (exp[*index] == '(') {
        (*index)++;
        root->left = build(exp, index);
        (*index)++;
    }

    if (exp[*index] == '(') {
        (*index)++;
        root->right = build(exp, index);
        (*index)++;
    }

    return root;
}

void rightViewUtil(struct Node* root, int level, int* maxLevel) {
    if (root == NULL) {
        return;
    }

    if (level > *maxLevel) {
        printf("%d ", root->key);
        *maxLevel = level;
    }

    rightViewUtil(root->right, level + 1, maxLevel);
    rightViewUtil(root->left, level + 1, maxLevel);
}

void rightView(struct Node* root) {
    int maxLevel = 0;
    
    rightViewUtil(root, 1, &maxLevel);
    printf("\n");
}

int main() {
    char exp[1000];


    fgets(exp, sizeof(exp), stdin);
    int index = 0;
    struct Node* root = build(exp, &index);

     int maxSum = INT_MIN;

    char sym;
    while(1)
{
    scanf("%c",&sym);

    if(sym=='l'){
levelordertraversal(root);
  printf("\n");
    }
    if(sym=='m'){
         maxSumBST(root, &maxSum);
    printf("%d\n", maxSum);
    }

    if(sym=='r'){
rightView(root);
  printf("\n");
    }
    if(sym=='e'){
        return 0;
    }
}
    

    

    return 0;
}
