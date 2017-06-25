#include "Node.h"

Node *newNode(PIECES *board, Move* move)
{
    Node *newNode;
    newNode = malloc(sizeof(Node)); 
    if(!newNode)
    {
        perror("Out of memory! Cannot create a new node!");
        return NULL;
    }

    int cpBoard[64];

    int x, y;

    for(x = 0; x < 8; x++)
    {
        for(y = 0; y < 8; y++)
        {
            cpBoard[x + (y * 8)] = board[x + (y * 8)];
        }
    }

    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->weight = 0;
    newNode->board = cpBoard;
    newNode->move = move;

    return newNode;
}



int getWeight(Node *node) { return node->weight; }

void insert(Node *insert, Node *root)
{
   if(!root)
   {
      insert->parent = NULL;
      insert->child = NULL;
   }
   else
   {
       if(!root->child)
       {
           root->child = insert;
           insert->parent = root;
           insert->child = NULL;
       }
       else
       {
           Node *temp = root;
           while(temp->child != NULL)
           {
               temp = temp->child;
           }
           temp->child = insert;
           insert->parent = temp;
           insert->child = NULL;
       }
   }
}

void destroyNode(Node *nodeToDestroy)
{
    if(!nodeToDestroy)
    {
        printf("Node is already emtpy. Skipping.");
    }

    if(!nodeToDestroy->child)
    {
        nodeToDestroy->parent = NULL;
        nodeToDestroy->weight = 0;
        free(nodeToDestroy);
    }
    else
    {
        nodeToDestroy->parent->child = nodeToDestroy->child;
        nodeToDestroy->child->parent = nodeToDestroy->parent;
        
        nodeToDestroy->parent = NULL;
        nodeToDestroy->weight = 0;

        free(nodeToDestroy);
    }
}
