#include<stdio.h>
#include<stdlib.h>

typedef struct exp_stack
{
    char *a;
    int top;
    int size;
} exp_stack;

void init_s(exp_stack *s, int size);
int isEmpty(exp_stack s);
int isFull(exp_stack s);
void push(exp_stack *s, char c);
char peek(exp_stack *s);
char pop(exp_stack *s);
void display(exp_stack s);
int precedence(char c);


