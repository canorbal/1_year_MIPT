#include <stdio.h>
#include <stdlib.h>

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
    struct List *list;
    list = (struct List *) malloc(sizeof(struct List));
    return list;
}

int IsEmpty(struct List* list)
{
    if (list->head == NULL)
    {
        return 0;
    }
    return 1;
}

void push(struct List *list, int a)
{    
    if (IsEmpty(list) == 0)
    {
        struct Node *node;
        node = (struct Node *)malloc(sizeof(struct Node));
        node->Data = a;
        node->back = NULL;
        node->next = NULL;
        list->head = node;
        return;
    }
    struct Node *node;
    node = (struct Node *)malloc(sizeof(struct Node));
    node->Data = a;
    
    node->next = NULL;
    node->back = list->head;
    node->back->next = node;
    list->head = node;
}

void unshift(struct List *list, int a)
{
    struct Node *node_pointer;
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
    
    struct Node *Node;
    Node = (struct Node *)malloc(sizeof(struct Node));
    Node->Data = a;
    Node->back = NULL;
    Node->next = node_pointer;
    node_pointer->back = Node;
}

int pop(struct List *list, int *x)
{
    if (IsEmpty(list) == 0)
    {
        return 0;
    }
    *x = list->head->Data;
    struct Node* node = list->head;
    list->head = list->head->back;
    free(node); 
    if (IsEmpty(list) == 1)
    {
        list->head->next = NULL;
        return 1;
    }
    list->head = NULL;
    return 1;
}

int shift(struct List *list, int *x)
{
    if (IsEmpty(list) == 0)
    {
        return 0;
    }
    struct Node *node_pointer;
    node_pointer = list->head;
    while (node_pointer->back != NULL)
    {
        node_pointer = node_pointer->back;
    }
    *x = node_pointer->Data;
    if (node_pointer->back == NULL)
    {
        free(node_pointer);
        node_pointer = NULL;
        list->head = NULL;
        return 1;
    }
    node_pointer = node_pointer->next;
    free(node_pointer->back);
    node_pointer->back = NULL;
    return 1;
}

void list_reverse(struct List* list)
{
    struct List* list_revers;
    list_revers = list_new();
    struct Node * node;
    
    if (IsEmpty(list) == 0)
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



int main()
{
    struct List* list;
    list = list_new();
    int x;
    push(list, 10);
    pop(list, &x);
    return 0;
}
