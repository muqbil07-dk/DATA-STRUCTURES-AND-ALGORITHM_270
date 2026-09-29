#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node *next;
};
void append(struct node **head, int data)
{
    struct node *new_node;
    struct node *last;
    new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    last = *head;
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
}
int contains(struct node *head, int value)
{
    struct node *current;
    current = head;
    while (current != NULL) {
        if (current->data == value)
            return 1;
        current = current->next;
    }
    return 0;
}
void deleteBefore(struct node **head, int value)
{
    struct node *temp;
    while (*head != NULL && (*head)->data != value) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}
void display(struct node *head)
{
    struct node *current;
    printf("Linked List:");
    current = head;
    while (current != NULL) {
        printf("->%d", current->data);
        current = current->next;
    }
    printf("\n");
}
int main(void)
{
    struct node *head;
    int n;
    int value;
    int target;
    int i;

    head = NULL;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &value);
        append(&head, value);
    }
    scanf("%d", &target);

    if (!contains(head, target)) {
        printf("Invalid Node! ");
        display(head);
    } else {
        deleteBefore(&head, target);
        display(head);
    }
    return 0;
}

