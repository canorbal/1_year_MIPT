#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct Node
{
    int Data;
    struct Node *next;
};

struct List
{
    struct Node *head;
};

struct List*  list_new()
{
    struct List* list = NULL;
    list =  malloc(sizeof(struct List));
    if (list == NULL)
    {
        fprintf(stderr, "Can't allocate memory: %s\n", strerror(errno));
        fprintf(stderr, "Error in function 'list_new()\n'");
        return NULL;
    }
   	return  list;
}

int insert(struct List *list, int a)
{
    struct Node *node = NULL;
    node = malloc(sizeof(struct Node));
    if (node == NULL)
    {
        fprintf(stderr, "Can't allocate memory: %s\n", strerror(errno));
        fprintf(stderr, "Error in creating Node with data = %d\n", a);
        return -1;
    }
    
    node->Data = a;
    node->next = list->head;
    list->head = node;
    return 0; 
}

void print(struct List *list)
{
    struct Node* node;
    node = list->head;
    while (node != NULL){
        printf( "%d ", node->Data);
        node = node->next;
    }
    printf("\n");
}

void remov(struct List *list, int a)
{
    struct Node *node = list->head;
    struct Node* free_node;
    while (node->Data == a)
    {
        free_node = node;
        node = node->next;
        free(free_node);
    }
    list->head = node;
    struct Node *back_node = NULL;
    while (node->next != NULL)
    {
        if (node->Data != a)
        {
            back_node = node;
            node = node->next;
            continue;
        }
        if (node->Data == a)
        {
            while (node->Data == a & node->next != NULL)
            {
                free_node = node;
                node = node->next;
                free(free_node);
            }
            back_node->next = node;
        }
    }
    if (node->Data == a)
    {
        back_node->next = NULL;
        free(node);
    }
}

void list_delete(struct List *list)
{
    struct Node *node = list->head;
    while (node != NULL)
    {
        struct Node *node_free = node;
        node = node->next;
        free(node_free);
        node_free = NULL;
    }
    
    list->head = NULL;
}

int main()
{
    struct List *list;
    list = list_new();
    insert(list, 20);
    insert(list, 10);
    insert(list, 20);
    insert(list, 20);
    insert(list, 20);
    insert(list, 40);
    insert(list, 20);
    insert(list, 30);
    insert(list, 30);
    print(list);
    remov(list, 20);
    print(list);
    insert(list, 50);
    print(list);
    list_delete(list);
    return 0;
}
