/*
    realization of binary search tree

    sources:
        https://neerc.ifmo.ru/wiki/index.php?title=Дерево_поиска,_наивная_реализация [ru]
        https://www.youtube.com/watch?v=2OyS4tW3xuQ (yandex data school) [ru]

    usage:
        main function contains all possible examples of binary search tree functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct Node
{
    /*
     * element in tree;
     * element has two descendants (left and right)
     */

    int key;
    int deep;
    struct Node *left;
    struct Node *right;
};

struct Tree
{
    /* tree structure has a pointer
     * to root node
     */

    struct Node *head;
};

struct Tree* new_tree()
{
    /*
     * function to initialize new tree
     * by creating root node == NULL pointer
     */

    struct Tree *tree;
    tree = (struct Tree*) malloc(sizeof(struct Tree));
    if (tree == NULL)
    {
        fprintf(stderr, "Can't allocate memory: %s\n", strerror(errno));
        fprintf(stderr, "Error in function 'new_tree()\n'");
        return NULL;
    }
    tree->head = NULL;
    return tree;
}

struct Node_queue
{
    /* element in queue of tree nodes */

    struct Node* node;
    struct Node_queue* back;
};

struct Queue
{
    /* a queue of tree nodes which
     * is used for bfs algorithm
     */

    struct Node_queue* head;
};


struct Queue* new_queue()
{
    /* queue initializer */

    struct Queue* queue;
    queue = (struct Queue *) malloc(sizeof(queue));
    if (queue == NULL)
    {
        fprintf(stderr, "Can't allocate memory: %s\n", strerror(errno));
        fprintf(stderr, "Error in function 'new_queue()\n'");
        return NULL;
    }
    queue->head = NULL;
    return queue;
}

void push_queue(struct Queue* queue, struct Node* node)
{
    /* push a tree node to queue */

    struct Node_queue *node_queue;
    node_queue = (struct Node_queue*) malloc(sizeof(struct Node_queue));
    if (node_queue == NULL)
    {
        fprintf(stderr, "Can't allocate memory: %s\n", strerror(errno));
        fprintf(stderr, "Error in function 'push_queue()\n'");
        return;
    }
    node_queue->node = node;
    node_queue->back = NULL;
    struct Node_queue *pointer;
    pointer = queue->head;
    if (pointer == NULL)
    {
        queue->head = node_queue;
        return;
    }
    while (pointer->back != NULL)
    {
        pointer = pointer->back;
    }
    pointer->back = node_queue;
}

void pop_queue(struct Queue* queue, struct Node **x)
{
    /* pop element from queue which contains tree nodes */

    *x = queue->head->node;
    struct Node_queue* node;
    node = queue->head;
    queue->head = node->back;
    free(node);
}

int check_empty_queue(struct Queue* queue)
{
    if (queue->head == NULL)
    {
        return 1;
    }
    return 0;
}

void push(struct Tree* tree,  int key)
{
    /* push key to tree */

    struct Node* node;
    node = (struct Node *) malloc(sizeof(struct Node));

    node->key = key;
    node->deep = 0;
    node->left = NULL;
    node->right = NULL;

    if (tree->head == NULL)
    {
        tree->head = node;
        return;
    }
    struct Node* pointer;
    pointer = tree->head;
    while (1)
    {
        if (node->key > pointer->key)
        {
            if (pointer->right == NULL)
            {
                pointer->right = node;
                node->deep++;
                break;
            }
            pointer = pointer->right;
            node->deep++;
        }
        if (node->key <= pointer->key)
        {
            if (pointer->left == NULL)
            {
                pointer->left = node;
                node->deep++;
                break;
            }
            pointer = pointer->left;
            node->deep++;
        }
    }
}

struct Node* find_minimum(struct Node* root)
{
    /*
     * find minimum key in tree
     * and return pointer to node with this key
     */

    struct Node* node = root;
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

struct Node* delete(struct Node* root, int key)
{
    /* delete element from tree */

    if (root == NULL)
    {
        return root;
    }
    if (key < root->key)
    {
        root->left = delete(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = delete(root->right, key);
    }
    else if ((root->right != NULL) && (root->left != NULL))
    {
        struct Node* minimum;
        minimum = find_minimum(root->right);
        root->key = minimum->key;
        root->right = delete(root->right, root->key);
    }
    else
    {
        if (root->left != NULL)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }
    return root;
}

void bfs(struct Tree *tree)
{
    /*
     * breadth-first search algorithm
     * https://ru.wikipedia.org/wiki/Поиск_в_ширину [ru]
     */

    struct Queue *queue;
    queue = new_queue();
    push_queue(queue, tree->head);

    while (check_empty_queue(queue) == 0)
    {
        struct Node* node;
        pop_queue(queue, &node);
        if (node->left != NULL)
        {
            push_queue(queue, node->left);
        }
        if (node->right != NULL)
        {
            push_queue(queue, node->right);
        }
        printf("deep is %d    Key is %d\n", node->deep, node->key);

    }
}

void dfs(struct Node *node)
{
    /*
     * depth-first search algorithm
     * https://ru.wikipedia.org/wiki/Поиск_в_глубину [ru]
     */

    printf("deep is %d    Key is %d\n", node->deep, node->key);
    if (node->left != NULL)
    {
        dfs(node->left);
    }
    if (node->right != NULL)
    {
        dfs(node->right);
    }
    return;
}

int main()
{
    struct Tree *tree;
    tree = new_tree();
    push(tree, 50);
    push(tree, 20);
    push(tree, 60);
    push(tree, 80);
    push(tree, 40);
    push(tree, 15);
    push(tree, 30);
    push(tree, 35);
    push(tree, 55);
    push(tree, 14);
    push(tree, 95);
    push(tree, 81);
    push(tree, 28);
    push(tree, 11);
    push(tree, 75);
    printf("<<< bfs is in progress >>>\n");
    bfs(tree);
    printf("<<< dfs is in progress >>>\n");
    dfs(tree->head);
    printf("<<< find_minimum is in progress >>>\n");
    struct Node* min = find_minimum(tree->head);
    printf("%d\n", min->key);
    printf("<<< deleting is in progress >>>\n");
    tree->head = delete(tree->head, 15);
    printf("<<< bfs is in progress >>>\n");
    bfs(tree);
    return  0;
}
