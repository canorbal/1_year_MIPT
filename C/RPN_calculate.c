/* Calculate the expression in Reverse Polish notation

    Sources:

        https://ru.wikiversity.org/wiki/Обратная_польская_запись:_примеры_реализации#C
        https://stackoverflow.com/questions/40328938/how-to-evaluate-reverse-polish-notation-using-stacks

    Example:
        1 2 + 4 / 5 * 8 7 6 - * + -> 11.75

    Attention! works only with digits and +,-,*,/ operands
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


struct Node
{
    double Data;
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
        return 1;

    return 0;
}

void push(struct List* list, double a)
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
        fprintf(stderr, "Error in function push with arguement %f\n", a);
        return;
    }

    node->Data = a;
    node->next = NULL;
    node->back = list->head;
    list->head = node;
}

void unshift(struct List *list, double a)
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
        fprintf(stderr, "Error in function unshift with arguement %f\n", a);
        return;
    }

    Node->Data = a;
    Node->back = NULL;
    Node->next = node_pointer;
    node_pointer->back = Node;
}

void pop(struct List *list, double *x)
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

void shift(struct List *list, double *x)
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
    printf("%f\n", node_pointer->Data);
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
        printf("%f ", node->Data);
        node = node->back;
    }
    printf("\n");
}


double result()
{
    struct List* list;
    list = list_new();

    char s=1;
    while (s != '\n')
    {
        scanf("%c", &s);
        if (s == '\n')
            break;

        if (s >= '0' && s <= '9')
        {
            push(list, s-'0');
        }

        if (s=='+')
        {
            double x,y;
            pop(list, &x);
            pop(list, &y);
            push(list, x+y);
        }

        if (s=='-')
        {
            double x,y;
            pop(list, &x);
            pop(list, &y);
            push(list, y-x);
        }

        if (s=='*')
        {
            double x,y;
            pop(list, &x);
            pop(list, &y);
            push(list, x*y);
        }

        if (s=='/')
        {
            double x,y;
            pop(list, &x);
            pop(list, &y);
            push(list, y/x);
        }
    }
    double b;
    pop(list, &b);
    return  b;
}

int main()
{
    printf("%f\n", result());
    return 0;
}
