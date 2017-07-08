/*
   Reverse Polish notation (RPN)
   This code transforms input string to RPN

   Sources:
        https://en.wikipedia.org/wiki/Reverse_Polish_notation
        https://ru.wikiversity.org/wiki/Обратная_польская_запись:_примеры_реализации
        https://habrahabr.ru/post/282379/

    This implementation works only with digits

    Example:

    (((1+2)/4)*5)+(8*(7-6)) -> 1 2 + 4 / 5 * 8 7 6 - * +
 
    (1+2/3-4*5^6*(7-4/3)) -> 1 2 3 / + 4 5 6 ^ * 7 4 3 / - * -

    Attention! works only with digits and +,-,*,/,^ operands
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


struct Node
{
    char Data;
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

int IsEmpty(struct List* list)
{
    if (list->head == NULL)
    {
        return 0;
    }
    return 1;
}

void push(struct List* list, char a)
{
    /*
     * add element a to the end of the list
     */

    if (IsEmpty(list) == 0)
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

void unshift(struct List *list, char a)
{
    /*
     * add element a to the begining of the list
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

void pop(struct List *list, char *x)
{
    /*
     * take the last element from list
     * and place it in x variable
     */

    if (IsEmpty(list) == 0)
    {
        return;
    }
    *x = list->head->Data;
    struct Node* node = list->head;
    list->head = list->head->back;
    free(node);

    if (IsEmpty(list) == 1)
    {
        list->head->next = NULL;
        return;
    }
    list->head = NULL;
}

void shift(struct List *list, char *x)
{
    /*
     * take the first element from list
     * and place it in x variable
     */

    if (IsEmpty(list) == 0)
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


char get_last(struct List *list)
{
    /* get last element from list and push it back */

    char c = 0;
    shift(list, &c);
    if (c !=  0)
        unshift(list, c);
    return c;
}

void print(struct List* list)
{
    struct Node* node = list->head;
    while (node != NULL)
    {
        printf("%c ", node->Data);
        node = node->back;
    }
    printf("\n");
}

int check_priority(char operand)
{
    /* check operand priorities */
    if (operand == 0)
        return -1;
    if (operand == '(')
        return 0;
    if ((operand == '+') || (operand == '-'))
        return 1;
    if ((operand == '*') || (operand == '/'))
        return 2;
    else 
        return 3;
}

void debug(char s, struct List* stack, struct List* output)
{
    /* 
     * this function is used only for debug printing
     */

    printf("scanned = %c\n", s);
    printf("stack = ");
    if (IsEmpty(stack) == 0)
            printf("EMPTY\n");
    else
        print(stack);
    printf("output = ");
    print(output);
    printf("\n");
}

int main()
{
    struct List* stack = list_new();
    struct List* output = list_new();
    /* check https://habrahabr.ru/post/282379/ */
    
    char s=1;
    while (1)
    {
        scanf("%c", &s);
        if (s == '\n')
            break;

        else if (s == ' ')
        {
            continue;
        }
        
        else if ((s >= '0') && (s <= '9'))
        {    
            unshift(output, s);
            continue;
        }

        else if (s == '(')
        {
            unshift(stack, s);
            continue;
        }
        
        else if (s == ')')
        {
            char last;
            while(get_last(stack) != '(')
            {
                shift(stack, &last);
                unshift(output, last);
            }
            
            shift(stack, &last);
            continue;
        }
 
        while (1)
        {
            int stack_head_prioritet = check_priority(get_last(stack));
            int temple_symbol_prioritet = check_priority(s);
            
            if (stack_head_prioritet < temple_symbol_prioritet)
                break;
            
            if (IsEmpty(stack) == 0)
                break;
            
            char last;
            shift(stack, &last);
            unshift(output, last);
        }
        unshift(stack, s);
    }
    
    while (IsEmpty(stack) != 0)
    {
        char last;
        shift(stack, &last);
        unshift(output, last);
    }
    print(output);
    return 0;
}
