#include <stdio.h>
#include <stdlib.h>

typedef struct InnerNode
{
    int data;
    struct InnerNode *next;
} InnerNode;

// Inner node structure for operators
typedef struct OperatorNode
{
    char op;
    struct OperatorNode *next;
} OperatorNode;

typedef InnerNode *listi;
typedef OperatorNode *listo;

// Outer node structure
typedef struct OuterNode
{
    listi innerList;
    listo operatorList; // New inner list for operators
    struct OuterNode *next;
} OuterNode;

typedef OuterNode *listo_outer;


listi createInnerNode(int data);
listo createOperatorNode(char op);
listo_outer createOuterNode();
void addInnerNode(listo_outer outer, int data);
void addOperatorNode(listo_outer outer, char op);
listo_outer addOuterNode(listo_outer *head);
void printLinkedList(listo_outer head);
void print_listi(listi num_list);
void freeLinkedList(listo_outer head);