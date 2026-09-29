#include <stdio.h>
#define MAXN 100000

void printArray(int arr[], int n)
{
    int i;

    for (i = 0; i < n; i++) {
        if (i > 0)
            printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");
}

void insertionSort(int arr[], int n)
{
    int i;
    int j;
    int key;
    int printed;

    printed = 0;
    for (i = 1; i < n; i++) {
        if (i == 3) {
            printArray(arr, n);
            printed = 1;
        }

        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }

    if (!printed)
        printArray(arr, n);
    printArray(arr, n);
}

int main(void)
{
    int n;
    int arr[MAXN];
    int i;

    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    insertionSort(arr, n);
    return 0;
}

