#include <stdio.h>
void quickSort(int a[], int low, int high) {
    int i, j, pivot, temp;
    if (low >= high)
    return;
    pivot = a[high];
    i = low - 1;
    for (j = low; j < high; j++) {
        if (a[j] < pivot) {
            i++;
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    temp = a[i + 1];
    a[i + 1] = a[high];
    a[high] = temp;
    quickSort(a, low, i);
    quickSort(a, i + 2, high);
}
void display(int a[], int n) {
    int i;
    for (i = 0; i < n; i++)
    printf("%d ", a[i]);
    printf("\n");
}
int main() {
    int a[] = {45, 12, 78, 23, 9, 34};
    int n = 6;
    printf("Before sorting: ");
    display(a, n);
    quickSort(a, 0, n - 1);
    printf("After Quick Sort: ");
    display(a, n);
    return 0;
}
