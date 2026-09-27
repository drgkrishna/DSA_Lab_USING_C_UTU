#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node *next;
};
struct Node *top = NULL;
struct Node *front = NULL, *rear = NULL;
void push(int x) {
    struct Node *n = (struct Node *)malloc(sizeof(struct Node));
    n->data = x;
    n->next = top;
    top = n;
}
void pop() {
    struct Node *t;
    if (top == NULL) {
        printf("Stack Underflow\n");
        return;
    }
    t = top;
    printf("Deleted: %d\n", t->data);
    top = top->next;
    free(t);
}
void displayStack() {
    struct Node *p = top;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}
void enqueue(int x) {
    struct Node *n = (struct Node *)malloc(sizeof(struct Node));
    n->data = x;
    n->next = NULL;
    if (rear == NULL)
    front = rear = n;
    else {
        rear->next = n;
        rear = n;
    }
}
void dequeue() {
    struct Node *t;
    if (front == NULL) {
        printf("Queue Underflow\n");
        return;
    }
    t = front;
    printf("Deleted: %d\n", t->data);
    front = front->next;
    if (front == NULL)
    rear = NULL;
    free(t);
}
void displayQueue() {
    struct Node *p = front;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}
int main() {
    push(10);
    push(20);
    push(30);
    printf("Stack: ");
    displayStack();
    pop();
    enqueue(10);
    enqueue(20);
    enqueue(30);
    printf("Queue: ");
    displayQueue();
    dequeue();
    return 0;
}
