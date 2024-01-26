#include<stdio.h>
#include<stdlib.h>
#include "ProBC0.c"
#include "ProBC1.h"
// Inner node structure for numbers

listi createInnerNode(int data)
{
    listi newNode = (listi)malloc(sizeof(InnerNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

listo createOperatorNode(char op)
{
    listo newNode = (listo)malloc(sizeof(OperatorNode));
    newNode->op = op;
    newNode->next = NULL;
    return newNode;
}

listo_outer createOuterNode()
{
    listo_outer newNode = (listo_outer)malloc(sizeof(OuterNode));
    newNode->innerList = NULL;
    newNode->operatorList = NULL;
    newNode->next = NULL;
    return newNode;
}

void addInnerNode(listo_outer outer, int data)
{
    listi newNode = createInnerNode(data);
    newNode->next = outer->innerList;
    outer->innerList = newNode;
}

void addOperatorNode(listo_outer outer, char op)
{
    listo newNode = createOperatorNode(op);
    newNode->next = outer->operatorList;
    outer->operatorList = newNode;
}

listo_outer addOuterNode(listo_outer *head)
{
    listo_outer newNode = createOuterNode();
    listo_outer p = *head;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = newNode;
    return newNode;
}

void printLinkedList(listo_outer head)
{
    listo_outer current = head;
    while (current != NULL)
    {
        listi innerCurrent = current->innerList;
        listo operatorCurrent = current->operatorList;

        while (innerCurrent != NULL)
        {
            printf("%d ", innerCurrent->data);
            innerCurrent = innerCurrent->next;
        }

        while (operatorCurrent != NULL)
        {
            printf("%c ", operatorCurrent->op);
            operatorCurrent = operatorCurrent->next;
        }

        printf(" ");
        current = current->next;
    }
    printf("\n");
}

void print_listi(listi num_list){
    listi p = num_list;
    while (p)
    {
        printf("%d ",p->data );
        p = p->next;
    }
    printf("\n");
}

void freeLinkedList(listo_outer head)
{
    listo_outer current = head;
    while (current != NULL)
    {
        listi innerCurrent = current->innerList;
        while (innerCurrent != NULL)
        {
            listi temp = innerCurrent;
            innerCurrent = innerCurrent->next;
            free(temp);
        }

        listo operatorCurrent = current->operatorList;
        while (operatorCurrent != NULL)
        {
            listo temp = operatorCurrent;
            operatorCurrent = operatorCurrent->next;
            free(temp);
        }

        listo_outer temp = current;
        current = current->next;
        free(temp);
    }
}
