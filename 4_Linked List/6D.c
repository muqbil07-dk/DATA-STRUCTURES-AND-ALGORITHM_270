#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node *next;
};
void insertStart(struct node **head, int data)
{
    struct node *new_node;
    new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = *head;
    *head = new_node;
}
int GetNth(struct node *head, int index)
{
    struct node *current;
    int position;
    current = head;
    position = 1;
    while (current != NULL && position < index) {
        current = current->next;
        position++;
    }
    if (current == NULL)
        return -1;
    return current->data;
}
void display(struct node *head)
{
    struct node *current;

    printf("Linked list:");
    current = head;
    while (current != NULL) {
        printf("-->%d", current->data);
        current = current->next;
    }
    printf("\n");
}
int main(void)
{
    struct node *head;
    int n;
    int value;
    int index;
    int i;
    int answer;
    head = NULL;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &value);
        insertStart(&head, value);
    }
    scanf("%d", &index);
    display(head);
    answer = GetNth(head, index);
    printf("Node at index=%d:%d\n", index, answer);
    return 0;
}

