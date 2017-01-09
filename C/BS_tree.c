#include <stdio.h>
#include <stdlib.h>

struct Node  //double DATA
{
    int key;
    double Data;
    int deep;
    struct Node *left;
    struct Node *right;
};

struct Tree
{
    struct Node *head;
};

struct Tree* new_tree()
{
    struct Tree *tree;
    tree=(struct Tree*) malloc(sizeof(struct Tree));
    return tree;
}

struct Node_queue
{
    struct Node* node;
    struct Node_queue* back;
};

struct Queue
{
    struct Node_queue* head;
};



struct Queue* new_queue()
{
    struct Queue* queue;
    queue=(struct Queue *)malloc(sizeof(queue));
    return queue;
}

void push_queue(struct Queue* queue, struct Node* node)
{
    struct Node_queue *node_queue;
    node_queue=(struct Node_queue*) malloc(sizeof(struct Node_queue));
    node_queue->node=node;
    node_queue->back=NULL;
    struct Node_queue *pointer;
    pointer=queue->head;
    
    if (pointer==NULL)
    {
        queue->head=node_queue;
        return;
    }
    while (pointer->back!=NULL)
    {
        pointer=pointer->back;
    }
    pointer->back=node_queue;
}

void pop_queue(struct Queue* queue, struct Node **x)
{
    *x=queue->head->node;
    struct Node_queue* node;
    node=queue->head;
    queue->head=queue->head->back;
    free(node);
}

int IsEmptyQueue(struct Queue* queue)
{
    if (queue->head==NULL)
    {
        return 0;
    }
    return 1;
}



void push(struct Tree* tree,  int key, double Data)
{
    struct Node* node;
    node=(struct Node *) malloc(sizeof(struct Node));
    
    node->key=key;
    node->Data=Data;
    node->deep=0;
    node->left=NULL;
    node->right=NULL;
    
    if (tree->head==NULL)
    {
        tree->head=node;
        return;
    }
    struct Node* pointer;
    pointer=tree->head;
    while (1)
    {
        if (node->key>pointer->key)
        {
            if (pointer->right==NULL)
            {
                pointer->right=node;
                node->deep++;
                break;
            }
            pointer=pointer->right;
            node->deep++;
        }
        if (node->key<=pointer->key)
        {
            if (pointer->left==NULL)
            {
                pointer->left=node;
                node->deep++;
                break;
            }
            pointer=pointer->left;
            node->deep++;
        }
    }
}


void delete(struct Tree* tree, int key, double Data)
{
    struct Node* node;
    node=tree->head;
    
    struct Node* back;
    back=tree->head;
    
    int count=0;
    while (1)
    {
        
        if (key>node->key)
        {
            back=node;
            node=node->right;
            count++;
            continue;
        }
        if (key<node->key)
        {
            back=node;
            node=node->left;
            count++;
            continue;
        }
        
        if (node->key==key && node->Data==Data)
        {
            if (node->right==NULL && node->left==NULL)
            {
                if (back->left==node)
                {
                    back->left=NULL;
                }
                if (back->right==node)
                {
                    back->right=NULL;
                }
                free(node);
                break;
            }
            if (node->right!=NULL && node->left==NULL)
            {
                if (back->left==node)
                {
                    back->left=node->right;
                }
                if (back->right==node)
                {
                    back->right=node->right;
                }
                free(node);
            }
            if (node->right==NULL && node->left!=NULL)
            {
                if (back->left==node)
                {
                    back->left=node->left;
                }
                if (back->right==node)
                {
                    back->right=node->left;
                }
                free(node);
            }
        }
        break;
    }
}

void wfs(struct Tree *tree)
{
    struct Queue *queue;
    queue=new_queue();
    push_queue(queue, tree->head);
    
    while (IsEmptyQueue(queue)==1)
    {
        struct Node* node;
        pop_queue(queue, &node);
        if (node->left!=NULL)
        {
            push_queue(queue, node->left);
        }
        if (node->right!=NULL)
        {
            push_queue(queue, node->right);
        }
        printf("deep is %d    Key is %d   Data is %f\n", node->deep, node->key, node->Data);
        
    }
}

void dfs(struct Node *tree_head)
{
    printf("%d ", tree_head->key);
    if (tree_head->left!=NULL)
    {
        dfs(tree_head->left);
    }
    printf("\n");
    if (tree_head->right!=NULL)
    {
        dfs(tree_head->right);
    }
}

int main()
{
    printf("input the head Data\n");
    int HeadData;
    scanf("%d", &HeadData);
    
    struct Tree *tree;
    tree=new_tree();
    push(tree, 0, 1);
    push(tree, 20, 1);
    push(tree, 5, 1);
    push(tree, 15, 1);
    push(tree, -5, 1);
    push(tree, 25, 1);
    push(tree, 27, 1);
    push(tree, 17, 1);
    push(tree, 16, 1);
    push(tree, 14, 1);
    push(tree, 8, 1);
    push(tree, 13, 1);
    push(tree, -4, 1);
    push(tree, 11, 1);
    
    //delete(tree, 15, 1);
    
   /* struct Queue *queue;
    queue=new_queue();
    push_queue(queue, tree->head);
    push_queue(queue, tree->head->left);*/
    
    wfs(tree);
    
    printf("<<<<<>>>>>>\n");
    dfs(tree->head);
    
    
    return  0;
}
