/*
    realization of doubly linked list

    sources:
        http://www.geeksforgeeks.org/doubly-linked-list/
        https://neerc.ifmo.ru/wiki/index.php?title=Список [ru]

    usage:
        see main function

*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


struct Node
{
    int Data;
    struct Node* next;
    struct Node* back;
};

struct List
{
    struct Node* head;
};

struct List* list_new()
{
    /*
     * initialize new list
     */

    struct List* list;
    list = (struct List *) malloc(sizeof(struct List));
    if (list == NULL)
    {
        fprintf(stderr, "Can't allocate memory %s\n", strerror(errno));
        fprintf(stderr, "Error in function list_new()\n");
        return NULL;
    }
    list->head = NULL;
    return list;
}

int check_empty(struct List* list)
{
    if (list->head == NULL)
    {
        return 1;
    }
    return 0;
}

void push(struct List* list, int a)
{
    /*
     * add element to the end of the list
     */

    if (check_empty(list) == 1)
    {
        struct Node* node;
        node = (struct Node *)malloc(sizeof(struct Node));
        node->Data = a;
        node->back = NULL;
        node->next = NULL;
        list->head = node;
        return;

    }
    struct Node* node;
    node = (struct Node *)malloc(sizeof(struct Node));
    if (node == NULL)
    {
        fprintf(stderr, "Can't allocate memory: %s\n", strerror(errno));
        fprintf(stderr, "Error in function push with arguement %d\n", a);
        return;
    }

    node->Data = a;
    node->next = NULL;
    node->back = list->head;
    list->head = node;
}

void unshift(struct List *list, int a)
{
    /*
     * add element to the begining of the list
     */

    struct Node* node_pointer;
    node_pointer = list->head;
    if (node_pointer == NULL)
    {
        push(list, a);
        return;
    }

    while (node_pointer->back != NULL)
    {
        node_pointer = node_pointer->back;
    }

    struct Node* Node;
    Node = (struct Node *)malloc(sizeof(struct Node));
    if (Node == NULL)
    {
        fprintf(stderr, "Can't allocate memory: %s\n", strerror(errno));
        fprintf(stderr, "Error in function unshift with arguement %d\n", a);
        return;
    }

    Node->Data = a;
    Node->back = NULL;
    Node->next = node_pointer;
    node_pointer->back = Node;
}

void pop(struct List *list, int *x)
{
    /*
     * take the last element from list
     * and place it in x variable
     */

    if (check_empty(list) == 1)
    {
        return;
    }
    *x = list->head->Data;
    struct Node* node = list->head;
    list->head = list->head->back;
    free(node);

    if (check_empty(list) == 0)
    {
        list->head->next = NULL;
        return;
    }
    list->head = NULL;
}

void shift(struct List *list, int *x)
{
    /*
     * take the first element from list
     * and place it in x variable
     */

    if (check_empty(list) == 1)
    {
        return;
    }
    struct Node* node_pointer = list->head;

    if (node_pointer->back == NULL)
    {
        *x = node_pointer->Data;
        free(node_pointer);
        list->head = NULL;
        return;
    }

    while (node_pointer->back != NULL)
    {
        node_pointer = node_pointer->back;
    }
    *x = node_pointer->Data;
    node_pointer->next->back = NULL;
    free(node_pointer);
    return;
}

void list_reverse(struct List* list)
{
    /*
     * inverting list from [a,b,c,d] to [d,c,b,a]
     */

    struct List* list_revers;
    list_revers = list_new();
    struct Node* node;

    if (check_empty(list) == 1)
    {
        return;
    }
    node = list->head;
    while (node != NULL)
    {
        push(list_revers, node->Data);
        struct Node *free_node = node;
        node = node->back;
        free(free_node);
    }
    *list = *list_revers;
}

void print(struct List* list)
{
    struct Node* node = list->head;
    while (node != NULL)
    {
        printf("%d ", node->Data);
        node = node->back;
    }
    printf("\n");
}

int main()
{
    struct List* list;
    list = list_new();
    int x;
    printf("creates\n");

    printf("push 10\n");
    push(list, 10);
    printf("list: ");
    print(list);

    pop(list, &x);
    printf("pop last element %d\n", x);
    printf("list: ");
    print(list);

    printf("push -150\n");
    push(list, 150);
    printf("list: ");
    print(list);

    shift(list, &x);
    printf("shift last element %d\n", x);
    printf("list: ");
    print(list);

    printf("unshift 100\n");
    unshift(list, 100);
    printf("list: ");
    print(list);

    pop(list, &x);
    printf("pop last element %d\n", x);
    printf("list ");
    print(list);

    printf("unshift -10\n");
    unshift(list, -10);
    printf("list: ");
    print(list);

    printf("unshift -20\n");
    unshift(list, -20);
    printf("list: ");
    print(list);

    printf("push 20, 30, 40\n");
    push(list, 20);
    push(list, 30);
    push(list, 40);
    printf("list: ");
    print(list);

    pop(list, &x);
    printf("pop last element %d \n", x);
    printf("list: ");
    print(list);

    pop(list, &x);
    printf("pop last element %d \n", x);
    printf("list: ");
    print(list);

    printf("push 20, 30, 40\n");
    push(list, 20);
    push(list, 30);
    push(list, 40);
    printf("list: ");
    print(list);

    shift(list, &x);
    printf("shift last element %d\n", x);
    printf("list: ");
    print(list);

    unshift(list, -100);
    printf("unshift -100\n");
    printf("list: ");
    print(list);

    printf("reverse\n");
    list_reverse(list);
    printf("list: ");
    print(list);
    return 0;
}
