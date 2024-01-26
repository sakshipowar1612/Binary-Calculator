#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include "ProBC0.h"

void init_s(exp_stack *s, int size)
{
    s->a = (char *)malloc(sizeof(char) * size);
    s->size = size;
    s->top = -1;
    return;
}
int isEmpty(exp_stack s)
{
    if (s.top == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int isFull(exp_stack s)
{
    if (s.top == s.size - 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void push(exp_stack *s, char c)
{
    if (isFull(*s))
    {
        return;
    }
    else
    {
        s->top++;
        s->a[s->top] = c;
        return;
    }
}
char peek(exp_stack *s)
{
    return s->a[s->top];
}
char pop(exp_stack *s)
{
    char ch = '#';
    if (!isEmpty(*s))
    {
        ch = s->a[s->top];
        s->top--;
    }
    return ch;
}
void display(exp_stack s)
{
    for (int i = s.top; i >= 0; i--)
    {
        printf("%c ", s.a[i]);
    }
    return;
}
int precedence(char c)
{
    if (c == '+')
    {
        return 10;
    }
    else if (c == '-')
    {
        return 10;
    }
    else if (c == '*')
    {
        return 20;
    }
    else if (c == '/')
    {
        return 20;
    }
    else if (c == '%')
    {
        return 20;
    }
    else if (c == '^')
    {
        return 30;
    }
    else if (c == '(')
    {
        return 5;
    }
    return 0;
}

