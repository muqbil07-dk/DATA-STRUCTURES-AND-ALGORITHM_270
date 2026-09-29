#include <stdio.h>
#define MAXN 100000
void swap(int *xp, int *yp)
{
    int temp;

    temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void selectionSort(int arr[], int n)
{
    int i;
    int j;
    int min_index;
    for (i = 0; i < n - 1; i++) {
        min_index = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_index])
                min_index = j;
        }
        if (min_index != i)
            swap(&arr[min_index], &arr[i]);
    }
}
void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++) {
        if (i > 0)
            printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");
}
int main(void)
{
    int n;
    int arr[MAXN];
    int i;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    selectionSort(arr, n);
    printArray(arr, n);
    return 0;
}

