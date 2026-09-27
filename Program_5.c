#include <stdio.h>
#define MAX 5
int q[MAX];
int front = -1, rear = -1;
void enqueue(int x) {
    if ((rear + 1) % MAX == front) {
        printf("Queue Overflow\n");
        return;
    }
    if (front == -1)
    front = rear = 0;
    else
    rear = (rear + 1) % MAX;
    q[rear] = x;
}
void dequeue() {
    if (front == -1) {
        printf("Queue Underflow\n");
        return;
    }
    printf("Deleted: %d\n", q[front]);
    if (front == rear)
    front = rear = -1;
    else
    front = (front + 1) % MAX;
}
void display() {
    int i;
    if (front == -1) {
        printf("Queue Empty\n");
        return;
    }
    i = front;
    while (1) {
        printf("%d ", q[i]);
        if (i == rear)
        break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}
int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    display();
    dequeue();
    dequeue();
    enqueue(50);
    enqueue(60);
    display();
    return 0;
}
