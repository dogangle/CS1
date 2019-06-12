#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct InstructNode {
    int opPriority, height;
    char name[20];
    struct InstructNode *left;
    struct InstructNode *right;
    } InstructNode;

typedef struct Instruct{
    int opType, opPriority;
    char name[20];
    } Instruct;

// Define global structs Instruct and InstructNode

int height(InstructNode * node)
{
    if(node==NULL)
        return 0;
    return node->height;
}
// Determine the current height of the node

int getBalance(InstructNode* node)
{
    if(node==NULL)
        return 0;
    return height(node->left) - height(node->right);
}
// Determine how balanced the AVL tree is

int greater(int left, int right)
{
    if (left>right)
        return left;
    return right;
}
// Determine the greater value of two heights (left and right)

InstructNode * newNode(int data, char * name)
{
    InstructNode * node = (InstructNode *)malloc(sizeof(InstructNode));
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    // Create and allocate memory for a new node, set left/right to NULL
    node->opPriority = data;
    strcpy(node->name, name);
    printf("ADDED\n");
    // Copy data to new node from data-struct array
    return node;
}

InstructNode * rotateRight(InstructNode * node)
{
    InstructNode * oldLeft = node->left;
    InstructNode * tmp = oldLeft->right;
    oldLeft->right = node;
    node->left = tmp;
    // Define node variables and rotate to the right

    node->height = greater(height(node->left), height(node->right))+1;
    oldLeft->height = greater(height(oldLeft->left), height(oldLeft->right))+1;
    // Correct height

    return oldLeft;
}

InstructNode * rotateLeft(InstructNode * node)
{
    InstructNode * oldRight = node->right;
    InstructNode * tmp = oldRight->left;
    oldRight->left = node;
    node->right = tmp;
    // Define node variables and rotate to the left

    node->height = greater(height(node->left), height(node->right))+1;
    oldRight->height = greater(height(oldRight->left), height(oldRight->right))+1;
    // Correct height

    return oldRight;
}

InstructNode * insertNode(InstructNode* node, int data, char * name)
{
    if (node==NULL) {
        return (newNode(data, name));
    }
    // Add new node to AVL tree when we reach NULL

    if (data < node->opPriority){
        node->left = insertNode(node->left, data, name);
    }
    // Traverse left if priority is lesser..

    else if (data > node->opPriority){
        node->right = insertNode(node->right, data, name);
    }
    // Or traverse right if priority is greater

    else {
        printf("REDUNDANT\n");
        return node;
    }
    // If priority is equal, program has already been added and is redundant

    node->height = 1 + greater(height(node->left), height(node->right));
    // Correct height

    int balance=getBalance(node);
    if (balance > 1 && data < node->left->opPriority)
        return rotateRight(node);

    else if (balance < -1 && data > node->right->opPriority)
        return rotateLeft(node);

    else if (balance > 1 && data > node->left->opPriority){
        node->left = rotateLeft(node->left);
        return rotateRight(node); }

    else if (balance < -1 && data < node->right->opPriority){
        node->right = rotateRight(node->right);
        return rotateLeft(node); }

    else
        return node;

    // Check to see if tree is unbalanced, rebalance by rotating if necessary


}

InstructNode * searchNode (InstructNode * node, int data)
{
    if (node==NULL || node->opPriority == data)
        return node;

    if (node->opPriority < data)
        return searchNode(node->right, data);

    return searchNode(node->left, data);
    // Recursively search the tree for the specified priority, or until node == NULL (program does not exist)

}

int main()
{
    int count,i;
    InstructNode * root = NULL;
    InstructNode * tmp = NULL;
    scanf("%d", &count);
    Instruct * commands = (Instruct *)malloc(count * sizeof(Instruct));
    // Declare and allocate memory

    for (i=0;i<count;i++) {

        scanf("%d", &commands[i].opType);
        // Store operation type in struct array

        if (commands[i].opType==1){
            scanf("%s %d", commands[i].name, &commands[i].opPriority);
            root = insertNode(root, commands[i].opPriority, commands[i].name);
        }
        // If operation is type 1, scan the name and priority and add it to the AVL tree

        if (commands[i].opType==2){
            scanf("%d", &commands[i].opPriority);
            tmp = searchNode(root, commands[i].opPriority);
            if (tmp == NULL)
                printf("NON-EXISTANT\n");
            else
                printf("%s\n",tmp->name);
        }
        // If operation is type 2, scan the priority number and search the AVL for that node
        // If node is NULL, program does not exist
    }

    return EXIT_SUCCESS;
}
