#include <stdio.h>
#define MAX 5
int stack[MAX], top = -1;
int queue[MAX], front = -1, rear = -1;
void push(int x) {
    if (top == MAX - 1)
    printf("Stack Overflow\n");
    else
    stack[++top] = x;
}
void pop() {
    if (top == -1)
    printf("Stack Underflow\n");
    else
    printf("Deleted: %d\n", stack[top--]);
}
void displayStack() {
    int i;
    for (i = top; i >= 0; i--)
    printf("%d ", stack[i]);
    printf("\n");
}
void enqueue(int x) {
    if (rear == MAX - 1)
    printf("Queue Overflow\n");
    else {
        if (front == -1)
        front = 0;
        queue[++rear] = x;
    }
}
void dequeue() {
    if (front == -1 || front > rear)
    printf("Queue Underflow\n");
    else
    printf("Deleted: %d\n", queue[front++]);
}
void displayQueue() {
    int i;
    for (i = front; i <= rear; i++)
    printf("%d ", queue[i]);
    printf("\n");
}
int main() {
    int choice, x;
    while (1) {
        printf("\n1.Push 2.Pop 3.Stack Display");
        printf("\n4.Enqueue 5.Dequeue 6.Queue Display");
        printf("\n7.Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("Enter element: ");
            scanf("%d", &x);
            push(x);
            break;
        case 2:
            pop();
            break;
        case 3:
            displayStack();
            break;
        case 4:
            printf("Enter element: ");
            scanf("%d", &x);
            enqueue(x);
            break;
        case 5:
            dequeue();
            break;
        case 6:
            displayQueue();
            break;
        case 7:
            return 0;
        default:
            printf("Invalid choice\n");
        }
    }
}
