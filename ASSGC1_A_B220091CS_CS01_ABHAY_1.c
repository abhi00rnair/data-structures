#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct stack {
    char arr[1000];
    int top;
};

void initial(struct stack *s) {
    s->top = -1;
}

void push(struct stack *s, char c) {
    s->arr[++(s->top)] = c;
}

char pop(struct stack *s) {
    return s->arr[(s->top)--];
}

bool openparan(char c) {
    return (c == '(');
}

bool closeparan(char c) {
    return (c == ')');
}

int duplicate(char expression[], int n) {
    struct stack *s = (struct stack *)malloc(sizeof(struct stack));
    initial(s);
    int count = 0;

    for (int i = 0; i < n; i++) {
        char c = expression[i];
        if (!closeparan(c)) {
            push(s, c);
        } else {
            while (s->top != -1 && !openparan(s->arr[s->top])) {
                pop(s);
                count++;
            }
        }
    }

    free(s); 

    if (count <= 1) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int n;
    
    scanf("%d", &n);

    struct stack *s = (struct stack *)malloc(sizeof(struct stack)); 
    char expression[n];

    
    scanf("%s", expression); 

    int result = duplicate(expression, n);
    printf("%d\n", result);

    free(s); 

    return 0;
}
