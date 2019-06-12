#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct Show{
    int req;
    char name[20], reqname[20];
    } Show;

typedef struct ShowNode{
    struct ShowNode * parent;
    struct ShowNode * left;
    struct ShowNode * right;
    int value;
    char name[20];
} ShowNode;

// Define structs to store data and form heap

ShowNode * insert(ShowNode *, ShowNode *);
ShowNode * findNextParent(ShowNode *);
ShowNode * findRoot(ShowNode *);
void cleanTree(ShowNode *);

// Declare functions


int main()
{
    int shows,i,j=0,t;
    ShowNode * lastInsert = NULL;
    ShowNode * root = NULL;
    scanf("%d\n", &shows);
    Show * showdata = (Show *)malloc(shows * sizeof(Show));
    // Declare & allocate memory

    for (i=0;i<shows;i++){
        scanf("%s %d", showdata[i].name, &showdata[i].req);
        if (showdata[i].req==1)
            scanf("%s", showdata[i].reqname);
    }
    // Store data in struct array

    for (i=0;i<shows;i++) {
        if (showdata[i].req==0) {
            ShowNode * newNode;
            newNode = (ShowNode *) malloc(sizeof(ShowNode));
            newNode->parent = NULL;
            newNode->left = NULL;
            newNode->right = NULL;
            newNode->value = j;
            j++;
            // Create new node

            strcpy(newNode->name, showdata[i].name);
            // Copy data to node

            for (t=0;t<shows;t++) {
                if (strcmp(showdata[i].name, showdata[t].reqname)==0)
                    strcpy(showdata[t].reqname, "YES");
            }
            // Label all shows with show i as a prerequisite with YES

            strcpy(showdata[i].name, "END");
            // Replace show name with END because it is being added to heap
            lastInsert = insert(newNode, lastInsert);
            // Add show to heap
            root = findRoot(newNode);
            break;
        }
    }
    i=0;
    while (j<shows) {
        if (showdata[i].req==0 && strcmp(showdata[i].name, "END")!=0) {
            ShowNode * newNode;
            newNode = (ShowNode *) malloc(sizeof(ShowNode));
            newNode->parent = NULL;
            newNode->left = NULL;
            newNode->right = NULL;
            newNode->value = j;
            j++;
            // Create new node

            strcpy(newNode->name, showdata[i].name);
            // Copy data to node
            for (t=0;t<shows;t++) {
                if (strcmp(showdata[i].name, showdata[t].reqname)==0)
                    strcpy(showdata[t].reqname, "YES");
            }
            // Label all shows with show i as a prerequisite with YES

            strcpy(showdata[i].name, "END");
            // Replace show name with END because it is being added to heap
            lastInsert = insert(newNode, lastInsert);
            // Add show to heap
            root = findRoot(newNode);
            i=-1;
        }
        // Shows with no prerequisite that have not been added already are inserted to the heap in order of priority

        else if (showdata[i].req==1 && strcmp(showdata[i].name, "END")!=0) {
            if (strcmp(showdata[i].reqname, "YES")==0){
                ShowNode * newNode;
                newNode = (ShowNode *) malloc(sizeof(ShowNode));
                newNode->parent = NULL;
                newNode->left = NULL;
                newNode->right = NULL;
                newNode->value = j;
                j++;
                // Create new node

                strcpy(newNode->name, showdata[i].name);
                // Copy data to node

                for (t=0;t<shows;t++) {
                    if (strcmp(showdata[i].name, showdata[t].reqname)==0)
                        strcpy(showdata[t].reqname, "YES");
                }
                // Label all shows with show i as a prerequisite with YES

                strcpy(showdata[i].name, "END");
                // Replace show name with END because it is being added to heap

                lastInsert = insert(newNode, lastInsert);
                // Add show to heap
                root = findRoot(newNode);
                i=-1;
            }
        }
        i++;
        i=i%shows;
    }
    free(showdata);
    cleanTree(findRoot(lastInsert));
    // Free memory
    return EXIT_SUCCESS;
}

ShowNode * insert(ShowNode * newNode, ShowNode * lastInsert)
{
    printf("%s\n", newNode->name);
    // Print out show name when it is added to heap
    ShowNode * nextParent;

    if (lastInsert == NULL) {
        return newNode;
    }
    // Base case

    nextParent = findNextParent(lastInsert);
    newNode->parent = nextParent;
    // Find next parent

    if (nextParent->left == NULL) {
        nextParent->left = newNode;
    }
    else {
        nextParent->right = newNode;
    }
    // Either insert left or right

    return newNode;


}

ShowNode * findNextParent(ShowNode * curNode)
{
    while(1) {
        if (curNode->parent == NULL) {
            while (curNode->left != NULL)
                curNode = curNode->left;
            return curNode;
        }
        // Fill previous row with values
        if (curNode->parent->left == curNode) {
            if (curNode->parent->right != NULL)
                curNode = curNode->parent->right;
                // Go right
            else
                return curNode->parent;
                // no right child

            while(curNode->left != NULL)
                curNode = curNode->left;
                // Go left

            return curNode;
        }

        curNode = curNode->parent;
    }
}

ShowNode * findRoot(ShowNode * root)
{
    if (root == NULL)
        return NULL;
    // Base case
    if (root->parent == NULL)
        return root;
    return findRoot(root->parent);
}

void cleanTree(ShowNode * root)
{
    if (root==NULL)
        return;
    cleanTree(root->left);
    root->left = NULL;
    cleanTree(root->right);
    root->right = NULL;
    free(root);
    // FREE MEMORY
}

