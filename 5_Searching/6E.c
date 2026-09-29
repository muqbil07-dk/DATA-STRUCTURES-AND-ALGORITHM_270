#include <stdio.h>

void thirdLargest(int arr[], int arr_size)
{
    int i;
    int j;
    int temp;
    int distinct;
    int answer;

    for (i = 0; i < arr_size - 1; i++) {
        for (j = i + 1; j < arr_size; j++) {
            if (arr[j] > arr[i]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    distinct = 1;
    answer = arr[0];
    for (i = 1; i < arr_size; i++) {
        if (arr[i] != arr[i - 1]) {
            distinct++;
            answer = arr[i];
            if (distinct == 3)
                break;
        }
    }

    printf("The third Largest element is %d\n", answer);
}

int main(void)
{
    int n;
    int arr[100];
    int i;

    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    thirdLargest(arr, n);
    return 0;
}

