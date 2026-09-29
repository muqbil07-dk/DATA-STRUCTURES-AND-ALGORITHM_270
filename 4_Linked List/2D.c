#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};
void insertStart(struct Node **head, int data)
{
    struct Node *new_node;
    new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = *head;
    if (*head != NULL)
        (*head)->prev = new_node;
    *head = new_node;
}
void printForward(struct Node *head)
{
    struct Node *current;
    int first;
    current = head;
    first = 1;
    while (current != NULL) {
        if (!first)
            printf(" ");
        printf("%d", current->data);
        first = 0;
        current = current->next;
    }
    printf("\n");
}
void printBackward(struct Node *head)
{
    struct Node *current;
    int first;
    current = head;
    if (current != NULL) {
        while (current->next != NULL)
            current = current->next;
    }
    first = 1;
    while (current != NULL) {
        if (!first)
            printf(" ");
        printf("%d", current->data);
        first = 0;
        current = current->prev;
    }
    printf("\n");
}
int main(void)
{
    struct Node *head;
    int n;
    int value;
    int i;
    head = NULL;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &value);
        insertStart(&head, value);
    }
    printForward(head);
    printBackward(head);
    return 0;
}

