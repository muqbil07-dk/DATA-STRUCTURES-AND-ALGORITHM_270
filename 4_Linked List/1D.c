#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node *next;
};
struct node *head = NULL;
void append(int data)
{
    struct node *new_node;
    struct node *last;
    new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;
    if (head == NULL) {
        head = new_node;
        return;
    }
    last = head;
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
}
void del(int value)
{
    struct node *current;
    struct node *previous;
    struct node *temp;
    while (head != NULL && head->data == value) {
        temp = head;
        head = head->next;
        free(temp);
    }
    previous = NULL;
    current = head;
    while (current != NULL) {
        if (current->data == value) {
            temp = current;
            previous->next = current->next;
            current = current->next;
            free(temp);
        } else {
            previous = current;
            current = current->next;
        }
    }
}
void display(void)
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
    int n;
    int value;
    int i;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &value);
        append(value);
    }
    scanf("%d", &value);
    del(value);
    display();
    return 0;
}

