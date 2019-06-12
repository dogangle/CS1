#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <limits.h>

struct stackula
{
    char name[20];
    struct stackula * next;

};

struct location
{
    char name[20], box1[20], box2[20];
};

// Define global structs
// stackula used for the stack, location used to store names

struct stackula * newNode (char * name)
{
    struct stackula * stackulaNode = (struct stackula*) malloc(sizeof(struct stackula));
    strcpy(stackulaNode->name, name);
    stackulaNode->next = NULL;
    return stackulaNode;
    // Creates a new node for the stack
}

void push(struct stackula** root, char * name)
{
    struct stackula * stackulaNode = newNode(name);
    stackulaNode->next = *root;
    *root = stackulaNode;
    // Pushes a value to the top of the stack
}

int isEmpty(struct stackula * root)
{
    return !root;
}

void pop(struct stackula** root)
{
    if (isEmpty(*root))
        return;
    char * popped;
    struct stackula* tmp = *root;
    *root = (*root)->next;
    strcpy(popped, tmp->name);
    free(tmp);
    // Pops the top value off of the stack
}

int peek(struct stackula* root, char * key)
{
    if (isEmpty(root))
        return INT_MIN;
    return strcmp(root->name, key);
    // Peeks at the top of the stack, returns 0 if the top of the stack is the same as the key
}
int main()
{
    struct stackula * root = NULL;
    int n, index;
    scanf("%d", &n);
    struct location * locations = (struct location*)malloc(sizeof(struct location)*n);
    // Declare and allocate
    for (index=0;index<n;index++) {
        scanf("%s %s %s", locations[index].name, locations[index].box1, locations[index].box2);
    }
    // Store locations and delivery information in an array of location structs
    printf("\n%s\n", locations[0].name);
    push(&root, locations[0].box1);
    push(&root, locations[0].box2);
    // Stackula visits first location, first two boxes are pushed to his stack
    strcpy(locations[0].box1, "END");
    strcpy(locations[0].box2, "END");
    // After the boxes are pushed, they are replaced with special key END to show Stackula already picked up the boxes
    index = 0;
    while (isEmpty(root)==0) {
    // Loop continues until stack is NULL
        if (peek(root, locations[index].name)==0) {
        // Loop until the top of the stack is one of the locations
            printf("%s\n", locations[index].name);
            while(peek(root, locations[index].name)==0)
                pop(&root);
            // Output the location Stackula visits, pop any boxes that are being delivered
            if (strcmp(locations[index].box1, "END")==0);
            else {
                push(&root,locations[index].box1);
                strcpy(locations[index].box1, "END");
            }
            if (strcmp(locations[index].box2, "END")==0);
            else {
                push(&root,locations[index].box2);
                strcpy(locations[index].box2, "END");
            }
            // If boxes at this location have already been picked up by Stackula do nothing,
            // else push the boxes to the top of the stack and replace them with END key
        }
        index++;
        index=index%n;
        // Cycle through n locations until stack is NULL
    }
    return EXIT_SUCCESS;
}
