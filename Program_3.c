#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node *prev, *next;
};
struct Node *front = NULL, *rear = NULL;
void insertFront(int x) {
    struct Node *n = malloc(sizeof(struct Node));
    n->data = x;
    n->prev = NULL;
    n->next = front;
    if (front)
    front->prev = n;
    else
    rear = n;
    front = n;
}
void insertRear(int x) {
    struct Node *n = malloc(sizeof(struct Node));
    n->data = x;
    n->next = NULL;
    n->prev = rear;
    if (rear)
    rear->next = n;
    else
    front = n;
    rear = n;
}
void deleteFront() {
    struct Node *t;
    if (!front) {
        printf("Deque Empty\n");
        return;
    }
    t = front;
    front = front->next;
    if (front)
    front->prev = NULL;
    else
    rear = NULL;
    free(t);
}
void deleteRear() {
    struct Node *t;
    if (!rear) {
        printf("Deque Empty\n");
        return;
    }
    t = rear;
    rear = rear->prev;
    if (rear)
    rear->next = NULL;
    else
    front = NULL;
    free(t);
}
void display() {
    struct Node *p = front;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}
int main() {
    insertFront(20);
    insertFront(10);
    insertRear(30);
    insertRear(40);
    printf("Deque: ");
    display();
    deleteFront();
    deleteRear();
    printf("After deletion: ");
    display();
    return 0;
}
