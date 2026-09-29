#include <stdio.h>
#include <stdlib.h>
int main(void) {
    int n;
    int i;
    int top;
    int inIndex;
    int last;
    int root;
    int *preorder;
    int *inorder;
    int *left;
    int *right;
    int *stack;
    int *stack1;
    int *stack2;
    int top1;
    int top2;
    int current;
    scanf("%d", &n);
    preorder = (int *)malloc((n + 1) * sizeof(int));
    inorder = (int *)malloc((n + 1) * sizeof(int));
    left = (int *)calloc(n + 1, sizeof(int));
    right = (int *)calloc(n + 1, sizeof(int));
    stack = (int *)malloc((n + 1) * sizeof(int));
    stack1 = (int *)malloc((n + 1) * sizeof(int));
    stack2 = (int *)malloc((n + 1) * sizeof(int));
    for (i = 0; i < n; i++) {
        scanf("%d", &preorder[i]);
    }
    for (i = 0; i < n; i++) {
        scanf("%d", &inorder[i]);
    }
    root = preorder[0];
    top = -1;
    stack[++top] = root;
    inIndex = 0;
    for (i = 1; i < n; i++) {
        last = 0;
        while (top >= 0 && stack[top] == inorder[inIndex]) {
            last = stack[top];
            top--;
            inIndex++;
        }
        if (last != 0) {
            right[last] = preorder[i];
        } else {
            left[stack[top]] = preorder[i];
        }
        stack[++top] = preorder[i];
    }
    top1 = -1;
    top2 = -1;
    stack1[++top1] = root;

    while (top1 >= 0) {
        current = stack1[top1--];
        stack2[++top2] = current;

        if (left[current] != 0) {
            stack1[++top1] = left[current];
        }
        if (right[current] != 0) {
            stack1[++top1] = right[current];
        }
    }

    for (i = top2; i >= 0; i--) {
        if (i != top2) {
            printf(" ");
        }
        printf("%d", stack2[i]);
    }
    printf("\n");

    free(preorder);
    free(inorder);
    free(left);
    free(right);
    free(stack);
    free(stack1);
    free(stack2);
    return 0;
}

