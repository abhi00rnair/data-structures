#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};

struct node *createnode(int value) {
    struct node *p;
    p = (struct node *)(malloc(sizeof(struct node)));
    p->data = value;
    p->left = NULL;
    p->right = NULL;

    return p;
}



int findindex(int arr[], int x, int y, int val) {
    for (int i = x; i <= y; i++) {
        if (arr[i] == val) {
            return i;
        }
    }
    
    return -1;
}


struct node *buildtree(int arr1[], int arr2[], int x, int y, int *index) {
    if (x > y ) {
        return NULL;
    }

    struct node *p;
    p = createnode(arr2[(*index)++]);

    if (x == y) {
        return p;
    }

    int inindex = findindex(arr1, x, y, p->data);

    
     p->left = buildtree(arr1, arr2, x, inindex - 1, index);
    p->right = buildtree(arr1, arr2, inindex + 1, y, index);
   

    return p;
}



void postorder(struct node *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

struct stacknode{
    struct node*data;
    struct stacknode*next;
};

struct stack{
    struct stacknode *top;
};

void push(struct stack *s, struct node *data) {
    struct stacknode *p = (struct stacknode *)malloc(sizeof(struct stacknode));
    if (p == NULL) {
        exit(0);
    }
    p->data = data;
    p->next = s->top;
    s->top = p;
}

struct node *pop(struct stack *s) {
    if (s->top == NULL) {
        return NULL;  
    }

    struct node *data = s->top->data;
    struct stacknode *temp = s->top;
    s->top = s->top->next;
    free(temp);

    
    if (data == NULL) {
        exit(0);  
    }

    return data;
}

int isEmpty(struct stack *s) {
    return s->top == NULL;
}

void zigzag(struct node *root) {
    if (root == NULL) {
        return;
    }

    struct stack *current = (struct stack *)malloc(sizeof(struct stack));
    struct stack *next = (struct stack *)malloc(sizeof(struct stack));
    
current->top = NULL;
    next->top = NULL;

    push(current, root);
    bool leftToRight = true;

    while (!isEmpty(current)) {
        struct node *temp = pop(current);

        if (temp != NULL) {
            printf("%d ", temp->data);

            if (leftToRight) {
                if (temp->left != NULL) {
                    push(next, temp->left);
                }

                if (temp->right != NULL) {
                    push(next, temp->right);
                }
            } else {
                if (temp->right != NULL) {
                    push(next, temp->right);
                }

                if (temp->left != NULL) {
                    push(next, temp->left);
                }
            }
        }

        if (isEmpty(current)) {
            leftToRight = !leftToRight;
            struct stack *tempStack = current;
            current = next;
            next = tempStack;
        }
    }

    free(current);
    free(next);
}

int max(int a, int b) {
    if(a>b){
        return a;
    }else{
        return b;
    }
}

int height(struct node* root)
{
    if (root == NULL)
        return 0;
 
    
    return 1 + max(height(root->left), height(root->right));
}

int printGivenLevelMax(struct node *root, int level) {
    if (root == NULL) {
        return INT_MIN;
    }
    if (level == 1) {
        
        //printf("%d ", root->data);
        return root->data;
    } else if (level > 1) {
    
        int maxLeft = printGivenLevelMax(root->left, level - 1);
        int maxRight = printGivenLevelMax(root->right, level - 1);
        
        return max(max(root->data, maxLeft), maxRight);
    }
    return INT_MIN;
}


int findMax(struct node *root) {
    if (root == NULL) {
        return INT_MIN; 
    }

    int maxLeft = findMax(root->left);
    int maxRight = findMax(root->right);

    return max(max(root->data, maxLeft), maxRight);
}

void levelMax(struct node *root) {
    if (root == NULL) {
        return;
    }

    int h = height(root);

    for (int i = 1; i <= h; i++) {
        int maxVal = printGivenLevelMax(root, i);
        printf("%d ", maxVal);
    }
}

int diameter(struct node* root)
{
    if (root == NULL)
        return 0;
 
    int lheight = height(root->left);
    int rheight = height(root->right);
 
    int ldiameter = diameter(root->left);
    int rdiameter = diameter(root->right);
 
   
 
    return max(lheight + rheight + 1,
               max(ldiameter, rdiameter));
}


 bool isLeaf(struct node *node)
{
  if (node == NULL)
    return false;
  if (node->left == NULL && node->right == NULL)
    return true;
  return false;
}

int leftLeavesSum(struct node *root)
{
  int res = 0;
 
  if (root != NULL)
  {
    
    if (isLeaf(root->left))
      res += root->left->data;
    else 
      res += leftLeavesSum(root->left);
 
    res += leftLeavesSum(root->right);
  }
  return res;
}
 
int main() {
    int n;
    scanf("%d", &n);

    int arr1[]={4,2, 5, 1, 6, 3, 7};
    int arr2[]={1, 2, 4, 5, 3, 6, 7};

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr1[i]);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr2[i]);
    }

    int index = 0;
    struct node *root = buildtree(arr1, arr2, 0, n - 1, &index);
 char c;
 while(1){
    scanf("%c",&c);
    if(c=='p'){
postorder(root);
    printf("\n");
    }

    if(c=='z'){
zigzag(root);
    printf("\n");
    }

    if(c=='m'){

    levelMax(root);
    printf("\n");
    }
    if(c=='d'){
int result=diameter(root);
    printf("%d",result);
    printf("\n");
    }
    if(c=='s'){
int sum =leftLeavesSum(root);
    printf("%d",sum);
    }
    if(c=='e'){
        return 0;
    }
 }
    
    return 0;
}
