#include <stdio.h>
void merge(int a[], int low, int mid, int high) {
    int temp[50];
    int i = low, j = mid + 1, k = 0;
    while (i <= mid && j <= high) {
        if (a[i] < a[j])
        temp[k++] = a[i++];
        else
        temp[k++] = a[j++];
    }
    while (i <= mid)
    temp[k++] = a[i++];
    while (j <= high)
    temp[k++] = a[j++];
    for (i = low, k = 0; i <= high; i++, k++)
    a[i] = temp[k];
}
void mergeSort(int a[], int low, int high) {
    int mid;
    if (low < high) {
        mid = (low + high) / 2;
        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
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
    mergeSort(a, 0, n - 1);
    printf("After Merge Sort: ");
    display(a, n);
    return 0;
}
