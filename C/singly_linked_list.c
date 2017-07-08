/* 
    singly linked list realization 
    
    sources:
        http://www.geeksforgeeks.org/linked-list-set-1-introduction/
        https://neerc.ifmo.ru/wiki/index.php?title=Список [ru]

    usage:
        all examples of using functions with singly linked list 
        are available in main
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct Node
{   
    int Data;
    struct Node* next;
};

struct List
{
    struct Node* head;
};

struct List*  list_new()
{
    /*
     * Initialize new singly linked list
     */

    struct List* list = NULL;
    list =  malloc(sizeof(struct List));
    if (list == NULL)
    {
        fprintf(stderr, "Can't allocate memory: %s\n", strerror(errno));
        fprintf(stderr, "Error in function 'list_new()\n'");
        return NULL;
    }
    list->head = NULL;
    return  list;
}

int insert(struct List *list, int a)
{
    /*
     * add a new element to list
     * asymptotically O(1)
     */
    
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
    /*
     * delete all elements in list
     * which is equal to a
     */

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
    /*
     * free memory from elements in list
     */
 
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
    
    printf("inserted 20, 10, 20, 20, 20, 40, 20, 30, 30, 20\n");
    insert(list, 20);
    insert(list, 10);
    insert(list, 20);
    insert(list, 20);
    insert(list, 20);
    insert(list, 40);
    insert(list, 20);
    insert(list, 30);
    insert(list, 30);
    insert(list, 20);
    printf("list:  ");
    print(list);
    
    printf("removed 20 from list\n");
    remov(list, 20);
    printf("list: ");
    print(list);
    
    printf("inserted 50\n");
    insert(list, 50);
    printf("list :");
    print(list);
    
    printf("deleted\n");
    list_delete(list);
    return 0;
}
