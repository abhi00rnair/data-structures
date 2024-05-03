#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *createnode(int value) {
    struct node *p;
    p = (struct node *)(malloc(sizeof(struct node)));
    p->data = value;
    p->next = NULL;
    return p;
}

struct node *insert(struct node *head, int val) {
    struct node *p, *q;
    p = head;
    if (p == NULL) {
        return createnode(val);
    }

    while (p->next != NULL) {
        p = p->next;
    }
    q = createnode(val);
    p->next = q;

    return head;
}

int totnodes(struct node *head) {
    int count = 0;
    struct node *p = head;
    while (p != NULL) {
        count++;
        p = p->next;
    }

    return count;
}

void display(struct node *head) {
    struct node *p = head;

    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int delete(struct node *head, int pos) {
    struct node *p, *q;
    int val = 0;
    int count = 1;
    int nodesno = totnodes(head);
    p = head;
    q = NULL;
    if (pos <= 0 || pos > nodesno) {
        return -1;
    } else {

        while (p != NULL && count != pos) {
            count++;
            q = p;
            p = p->next;
        }

        val = p->data;
        if (q == NULL) {
            head = p->next;
            free(p);
        } else {
            q->next = p->next;
            free(p);
        }
    }
    return val;
}



struct node *reverse(struct node *head) {
    struct node *p, *q, *r;
    p = head;
    q = NULL;
    r = NULL;
    while (p != NULL) {
        r = q;
        q = p;
        p = p->next;
        q->next = r;
    }
    head = q;
    return head;
}

struct node *reduplicate(struct node *head) {
    struct node *p, *q ,*r;
    p = head;
    
    if (p == NULL || p->next == NULL) {
        return head;
    }

while(p!=NULL){
    q = p->next;
    r=p;

    while(q!=NULL){
        if(p->data!=q->data){
            r=q;
            q=q->next;

        }else{
            r->next=q->next;
            free(q);
            q=r->next;


        }
    }p=p->next;
}
    return head;
}

char isPalindrome(struct node *head) {
    int count = totnodes(head);
    struct node *p = head, *q = head, *r = head;
    int key = 1;
    int mid;

    if (count % 2 != 0) {
        mid = (count / 2) + 1;
        while (key != mid) {
            p = p->next;
            r = r->next;
            key++;
        }
        p = reverse(p);

        while (q != r) {
            if (q->data == p->data) {
                q = q->next;
                p = p->next;
            } else {
                return 'N';
            }
        }
    } else {

        mid = count / 2;
        key = 1;
        while (key <= mid) {
            r = r->next;
            key++;
        }
        p = reverse(r);

        while (p != NULL) {
            if (q->data == p->data) {
                q = q->next;
                p = p->next;
            } else {
                return 'N';
            }
        }
    }

    return 'Y';
}

int main() {
    struct node *head = NULL;
    char c;
     int val=0;
     int result=0;
                    int pos=0;
    
    while (1) {
        scanf(" %c", &c);

        if (c == 'e') {
            return 0;
        } else {
            switch (c) {
                case 'a':
                   
                    scanf("%d", &val);
                    head = insert(head, val);
                    break;

                case 'r':
                    
                    scanf("%d", &pos);
                    result = delete(head, pos);
                    printf("%d\n", result);
                    break;

                case 'd':
                    head = reduplicate(head);
                    display(head);
                    break;

                case 'p':
                    printf("%c\n", isPalindrome(head));
                    break;

                case 's':
                    display(head);
                    break;
            }
        }
    }
    return 0;
}
