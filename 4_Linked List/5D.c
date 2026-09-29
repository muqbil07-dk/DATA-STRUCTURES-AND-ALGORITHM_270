#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node *next;
};
void insert_Data(struct node **head, int data)
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
void delete_Alt(struct node **head)
{
    struct node *current;
    struct node *to_delete;
    current = *head;
    while (current != NULL && current->next != NULL) {
        to_delete = current->next;
        current->next = to_delete->next;
        free(to_delete);
        current = current->next;
    }
}
void display(struct node *head)
{
    struct node *current;
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
int main(void)
{
    struct node *head;
    int n;
    int i;
    head = NULL;
    scanf("%d", &n);
    /* The list in this challenge contains 1, 2, ..., N. */
    for (i = 1; i <= n; i++)
        insert_Data(&head, i);

    delete_Alt(&head);
    display(head);
    return 0;
}

