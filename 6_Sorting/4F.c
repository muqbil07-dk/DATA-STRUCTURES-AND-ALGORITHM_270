#include <stdio.h>
#define MAXN 100
void bubble_sort(int arr[], int no)
{
    int i;
    int j;
    int temp;
    for (i = 0; i < no - 1; i++) {
        for (j = 0; j < no - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
int MEGA_SALE(int arr[], int no, int k)
{
    int negative[MAXN];
    int count;
    int i;
    int answer;
    count = 0;
    for (i = 0; i < no; i++) {
        if (arr[i] < 0) {
            negative[count] = arr[i];
            count++;
        }
    }

    bubble_sort(negative, count);
    answer = 0;
    if (k > count)
        k = count;
    for (i = 0; i < k; i++)
        answer += -negative[i];
    return answer;
}

int main(void)
{
    int t;
    int n;
    int m;
    int arr[MAXN];
    int i;

    scanf("%d", &t);
    while (t-- > 0) {
        scanf("%d %d", &n, &m);
        for (i = 0; i < n; i++)
            scanf("%d", &arr[i]);
        printf("%d\n", MEGA_SALE(arr, n, m));
    }
    return 0;
}

