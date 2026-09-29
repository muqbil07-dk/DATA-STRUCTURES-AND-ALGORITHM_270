#include <stdio.h>
#include <stdlib.h>
struct n {
    int data;
    struct n *next;
};
struct n *complete = NULL;
void insert(int data)
{
    struct n *new_node;
    struct n *last;
    new_node = (struct n *)malloc(sizeof(struct n));
    new_node->data = data;
    if (complete == NULL) {
        complete = new_node;
        new_node->next = complete;
        return;
    }
    last = complete;
    while (last->next != complete)
        last = last->next;
    last->next = new_node;
    new_node->next = complete;
}
struct n *addEnd(struct n *head, int data)
{
    struct n *new_node;
    struct n *last;
    new_node = (struct n *)malloc(sizeof(struct n));
    new_node->data = data;
    if (head == NULL) {
        new_node->next = new_node;
        return new_node;
    }
    last = head;
    while (last->next != head)
        last = last->next;
    last->next = new_node;
    new_node->next = head;
    return head;
}
void display(struct n *h)
{
    struct n *current;
    printf("[h]=>");
    if (h != NULL) {
        current = h;
        do {
            printf("%d=>", current->data);
            current = current->next;
        } while (current != h);
    }
    printf("[h]\n");
}
int main(void)
{
    struct n *odd;
    struct n *even;
    struct n *current;
    int n;
    int position;
    int i;
    odd = NULL;
    even = NULL;
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        insert(i);
    printf("Complete linked_list:\n");
    display(complete);
    if (complete != NULL) {
        current = complete;
        position = 1;
        do {
            if (position % 2 == 1)
                odd = addEnd(odd, current->data);
            else
                even = addEnd(even, current->data);
            current = current->next;
            position++;
        } while (current != complete);
    }
    printf("Odd:\n");
    display(odd);
    printf("Even:\n");
    display(even);
    return 0;
}

