#include<stdio.h>
#include<stdlib.h>



//fuctions:
void pushStack_num(stack *top, listi datan);
void pushStack_op(stack *top, listo datao);
listi popStack_num(stack *top);
listo popStack_op(stack *top);
void append(listi *num, int d);
void add_beg(listi *head, int data);
void delete_beg(listi *head);
void delete_end(listi *head);

int total_digits(listi num1);