#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node *next;
};
void sortedInsert(struct Node **head_ref, struct Node *new_node)
{
    struct Node *current;
    struct Node *last;
    if (*head_ref == NULL) {
        new_node->next = new_node;
        *head_ref = new_node;
        return;
    }
    if (new_node->data <= (*head_ref)->data) {
        last = *head_ref;
        while (last->next != *head_ref)
            last = last->next;
        new_node->next = *head_ref;
        last->next = new_node;
        *head_ref = new_node;
        return;
    }
    current = *head_ref;
    while (current->next != *head_ref &&
           current->next->data < new_node->data)
        current = current->next;
    new_node->next = current->next;
    current->next = new_node;
}
void display(struct Node *head)
{
    struct Node *current;
    int first;
    if (head == NULL) {
        printf("\n");
        return;
    }
    current = head;
    first = 1;
    do {
        if (!first)
            printf(" ");
        printf("%d", current->data);
        first = 0;
        current = current->next;
    } while (current != head);
    printf("\n");
}
int main(void)
{
    struct Node *head;
    struct Node *new_node;
    int n;
    int value;
    int i;
    head = NULL;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &value);
        new_node = (struct Node *)malloc(sizeof(struct Node));
        new_node->data = value;
        new_node->next = NULL;
        sortedInsert(&head, new_node);
    }
    display(head);
    return 0;
}

