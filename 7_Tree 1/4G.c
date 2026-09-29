#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};

int firstPrint = 1;

struct node *newNode(int item) {
    struct node *temp;

    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = item;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

struct node *insert(struct node *root, int item) {
    if (root == NULL) {
        return newNode(item);
    }

    if (item < root->data) {
        root->left = insert(root->left, item);
    } else {
        root->right = insert(root->right, item);
    }

    return root;
}

void postorder(struct node *root) {
    if (root == NULL) {
        return;
    }

    postorder(root->left);
    postorder(root->right);
    if (!firstPrint) {
        printf(" ");
    }
    printf("%d", root->data);
    firstPrint = 0;
}

void freeTree(struct node *root) {
    if (root == NULL) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    int n;
    int i;
    int value;
    struct node *root;

    scanf("%d", &n);
    root = NULL;

    for (i = 0; i < n; i++) {
        scanf("%d", &value);
        root = insert(root, value);
    }

    postorder(root);
    printf("\n");
    freeTree(root);
    return 0;
}

