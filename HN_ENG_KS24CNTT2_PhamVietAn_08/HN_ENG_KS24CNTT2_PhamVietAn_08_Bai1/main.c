#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100

typedef struct Operation {
    char url[100];
    char timestamp[100];
    struct Operation *next;
    struct Operation *prev;
}Operation;

typedef struct Stack {
    int top;
    Operation *data[MAX];
} Stack;

typedef struct History {
    Operation *head;
    Operation *tail;
} History;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmptyStack(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, Operation *op) {
    if (s->top < MAX - 1) {
        s->data[++(s->top)] = op;
    }
}

Operation *pop(Stack *s) {
    if (!isEmptyStack(s)) {
        return s->data[(s->top)--];
    }
    return NULL;
}

Operation *peek(Stack *s) {
    if (!isEmptyStack(s)) {
        return s->data[(s->top)];
    }
    return NULL;
}

void clearStack(Stack *s) {
    s->top = -1;
}

void initHistory(History *h) {
    h->head = h->tail = NULL;
}

void addHistory(History *h, Operation *op) {
    if (h->head == NULL) {
        h->head = op;
        h->tail = op;
    } else {
        h->tail->next = op;
        op->prev = h->tail;
        h->tail = op;
    }
}

void printHistory(History *h) {
    if (h->head == NULL) {
        printf("Khong co lich su duyet web");
        return;
    }
    Operation *cur = h->head;
    printf("---------- Lich su duyet web ----------");
    while (cur) {
        printf("URL: %s Timestamp: %s \n", cur->url, cur->timestamp);
        cur = cur->next;
    }
}

void clearHistory(History *h) {
    Operation *cur = h->head;
    while (cur) {
        Operation *temp = cur;
        cur = cur->next;
        free(cur);
    }
    h->head = NULL;
    h->tail = NULL;
}

char *getCurrentTime() {
    time_t now = time(NULL);
    return ctime(&now);
}

Operation *createOperation(char *url) {
    Operation *op = (Operation *)malloc(sizeof(Operation));
    strcpy(op->url, url);
    strcpy(op->timestamp, getCurrentTime());
    op->next = NULL;
    op->prev = NULL;
    return op;
}

int main(void) {
    Stack back, forward;
    History history;
    Operation *cur = NULL;

    initStack(&back);
    initStack(&forward);
    initHistory(&history);

    char command[100], input[100];
    int choice;
    do {
        printf("\n---------- WEB HISTORY ----------\n");
        printf("1. VISIT URL\n");
        printf("2. BACKWARD\n");
        printf("3. FORWARD\n");
        printf("4. CURRENT\n");
        printf("5. HISTORY\n");
        printf("6. CLEAR HISTORY\n");
        printf("7. EXIT\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                char url[100];
                if (cur == NULL) {
                    push(&back, cur);
                }
                printf("Nhap trang web hien tai: ");
                fgets(url, 100, stdin);
                url[strcspn(url, "\n")] = 0;

                cur = createOperation(url);
                addHistory(&history, cur);
                clearStack(&forward);
                printf("Da truy cap: %s\n", url);
                break;

            case 2:
                if (isEmptyStack(&back)) {
                    printf("Khong the quay lai\n");
                } else {
                    push(&forward, cur);
                    cur = pop(&back);
                    printf("Da quay lai: %s\n", cur->url);
                }
                break;

            case 3:
                if (isEmptyStack(&forward)) {
                    printf("Khong the di tiep\n");
                } else {
                    push(&back, cur);
                    cur = pop(&forward);
                    printf("Da chuyen tiep: %s\n", cur->url);
                }
                break;

            case 4:
                if (cur != NULL) {
                    printf("Trang hien tai: %s\n", cur->url);
                } else {
                    printf("Chua truy cap trang nao\n");
                }
                break;

            case 5:
                printHistory(&history);
                break;

            case 6:
                clearHistory(&history);
                printf("Da xoa lich su\n");
                break;

            case 7:
                printf("Da thoat chuong trinh");
                break;

            default:
                printf("Lua chon khong hop le");
                break;
        }
    }while (choice != 7);
    return 0;
}