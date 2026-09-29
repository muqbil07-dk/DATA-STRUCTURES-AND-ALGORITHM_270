#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void create(struct node **head, int data)
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

void print(struct node *head)
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

struct node *reverse(struct node *head)
{
    struct node *previous;
    struct node *current;
    struct node *next_node;

    previous = NULL;
    current = head;
    while (current != NULL) {
        next_node = current->next;
        current->next = previous;
        previous = current;
        current = next_node;
    }
    return previous;
}

struct node *fold(struct node *head, int n)
{
    struct node *first;
    struct node *second;
    struct node *splitter;
    struct node *dummy;
    struct node *tail;
    struct node *next_node;
    int first_count;
    int i;

    if (head == NULL || head->next == NULL)
        return head;

    first_count = n / 2;
    splitter = head;
    for (i = 1; i < first_count; i++)
        splitter = splitter->next;

    second = splitter->next;
    splitter->next = NULL;
    second = reverse(second);

    dummy = (struct node *)malloc(sizeof(struct node));
    dummy->next = NULL;
    tail = dummy;
    first = head;

    while (first != NULL || second != NULL) {
        if (first != NULL) {
            next_node = first->next;
            tail->next = first;
            tail = first;
            first = next_node;
        }
        if (second != NULL) {
            next_node = second->next;
            tail->next = second;
            tail = second;
            second = next_node;
        }
    }
    tail->next = NULL;

    head = dummy->next;
    free(dummy);
    return head;
}

int main(void)
{
    struct node *head;
    int n;
    int value;
    int i;

    head = NULL;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &value);
        create(&head, value);
    }

    printf("Link list data:");
    print(head);
    head = fold(head, n);
    printf("Link list data after fold:");
    print(head);
    return 0;
}

