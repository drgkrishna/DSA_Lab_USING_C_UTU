#include <stdio.h>
#define SIZE 10
int key[SIZE];
int value[SIZE];
void init() {
    for (int i = 0; i < SIZE; i++)
    key[i] = -1;
}
int hash(int k) {
    return k % SIZE;
}
void insert(int k, int v) {
    int i = hash(k);
    int start = i;
    while (key[i] != -1) {
        i = (i + 1) % SIZE;
        if (i == start) {
            printf("Hash Table Full\n");
            return;
        }
    }
    key[i] = k;
    value[i] = v;
}
void search(int k) {
    int i = hash(k);
    int start = i;
    while (key[i] != -1) {
        if (key[i] == k) {
            printf("Value = %d\n", value[i]);
            return;
        }
        i = (i + 1) % SIZE;
        if (i == start)
        break;
    }
    printf("Key not found\n");
}
void display() {
    for (int i = 0; i < SIZE; i++)
    if (key[i] != -1)
    printf("%d : %d\n", key[i], value[i]);
}
int main() {
    init();
    insert(10, 100);
    insert(20, 200);
    insert(25, 250);
    insert(35, 350);
    printf("Dictionary:\n");
    display();
    printf("\nSearch key 25:\n");
    search(25);
    return 0;
}
