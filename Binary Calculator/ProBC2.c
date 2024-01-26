#include <stdio.h>
#include <stdlib.h>
#include "ProBC1.c"
#include "ProBC2.h"

typedef struct stackNode
{
    listi data_num;
    listo data_op;
    struct stackNode *nex;
} stackNode;
typedef stackNode *stack;

void pushStack_num(stack *top, listi datan)
{
    stackNode *newNode = (stackNode *)malloc(sizeof(stackNode));
    newNode->data_num = datan;
    newNode->nex = *top;
    *top = newNode;
}
void pushStack_op(stack *top, listo datao)
{
    stackNode *newNode = (stackNode *)malloc(sizeof(stackNode));
    newNode->data_op = datao;
    newNode->nex = *top;
    *top = newNode;
}

listi popStack_num(stack *top)
{
    if (*top == NULL)
    {
        printf("Error: Empty Stack\n");
        exit(EXIT_FAILURE);
    }
    listi data1 = (*top)->data_num;
    stackNode *temp = *top;
    *top = (*top)->nex;
    free(temp);
    return data1;
}

listo popStack_op(stack *top)
{
    if (*top == NULL)
    {
        printf("Error: Empty Stack\n");
        exit(EXIT_FAILURE);
    }
    listo data2 = (*top)->data_op;
    stackNode *temp = *top;
    *top = (*top)->nex;
    free(temp);
    return data2;
}

void append(listi *num, int d)
{
    InnerNode *nn, *k;
    nn = createInnerNode(d);

    if (*num == NULL)
    {
        *num = nn;
        return;
    }
    else
    {
        k = *num;
        while (k->next != NULL)
        {
            k = k->next;
        }
        k->next = nn;
    }
    return;
}
void add_beg(listi *head, int data)
{
    listi nn;
    nn = (listi)malloc(sizeof(InnerNode));
    if (nn)
    {
        nn->data = data;
        nn->next = NULL;
    }
    else
    {
        return;
    }
    if (*head == NULL)
    {
        *head = nn;
        return;
    }
    else
    {
        nn->next = *head;
        *head = nn;
    }
    return;
}
void delete_beg(listi *head)
{
    InnerNode *p;
    p = *head;
    if (*head == NULL)
    {
        return;
    }
    *head = p->next;
    free(p);
    return;
}
void delete_end(listi *head)
{
    InnerNode *p, *q;
    p = *head;
    if (*head == NULL)
    {
        return;
    }
    while (p->next != NULL)
    {
        q = p;
        p = p->next;
    }
    q->next = NULL;
    return;
}
int isZero(listi l)
{
    if (l == NULL)
        return 1;
    if (l->next == NULL)
        return 1;
    listi p = l->next;
    while (p)
    {
        if (p->data != '0')
            return 0;
        p = p->next;
    }
    return 0;
}

int total_digits(listi num1)
{
    listi p = num1;
    int count = 0;
    while (p)
    {
        count = count + 1;
        p = p->next;
    }
    return count;
}

void forward_list(listi *head1, listi *head2)
{
    listi p;
    p = *head1;
    listi q = NULL;
    while (p)
    {
        add_beg(&q, p->data);
        p = p->next;
    }
    *head2 = q;
    return;
}
int compare(listi num1, listi num2)
{

    InnerNode *p1 = num1;
    InnerNode *p2 = num2;

    forward_list(&num1, &p1);
    forward_list(&num2, &p2);
    int len1 = total_digits(num1);
    int len2 = total_digits(num2);

    if (len1 > len2)
    {
        return 1;
    }
    else if (len1 < len2)
    {
        return 2;
    }
    // If lengths are equal, compare digits from most significant to least significant
    while (p1 && p2)
    {
        if (p1->data > p2->data)
        {
            return 1;
        }
        else if (p1->data < p2->data)
        {
            return 2;
        }

        p1 = p1->next;
        p2 = p2->next;
    }
    // If all digits are equal, the numbers are equal
    return 0;
}
int isnegative(listi num)
{
    listi r_num = NULL;
    forward_list(&num, &r_num);
    if (!r_num)
    {
        printf("Error");
        return 0;
    }

    if (r_num->data == 45)
    {
        return 1;
    }
    return 0;
}
int whichismax(listi *num1, listi *num2)
{
    InnerNode *p_rnum1 = NULL, *p_rnum2 = NULL;
    forward_list(num1, &p_rnum1);
    forward_list(num2, &p_rnum2);
    int n = total_digits(*num1);
    int same = 0;
    int i = 0;
    while (i < n)
    {
        if (p_rnum1->data == p_rnum2->data)
        {
            same = 0;
        }
        else if (p_rnum1->data > p_rnum2->data)
        {
            same = 1;
            return same;
        }
        else if (p_rnum1->data < p_rnum2->data)
        {
            same = 2;
            return same;
        }
        p_rnum1 = p_rnum1->next;
        p_rnum2 = p_rnum2->next;
        i++;
    }
    return same;
}
void removeMSBzeroes(listi *l)
{
    InnerNode *l1 = NULL;
    forward_list(l, &l1);
    InnerNode *temp;
    while (l1->data == 0 && l1->next)
    {
        temp = l1;
        l1 = l1->next;
        free(temp);
    }
    listi l2 = NULL;
    forward_list(&l1, &l2);
    *l = l2;
    return;
}
listi sub(listi *num1, listi *num2);
listi add(listi *num1, listi *num2)
{
    listi p;
    listi q;
    listi r = NULL;
    p = *num1, q = *num2;
    int carry = 0;
    int ispneg = isnegative(p);
    if (ispneg == 1)
    {
        delete_end(&p);
        int whomax = compare(p, q);
        if (whomax == 1)
        {
            r = sub(&q, &p);
        }
        else if (whomax == 2)
        {
            r = sub(&q, &p);
        }
        else if (whomax == 0)
        {
            append(&r, 0);
        }
        return r;
    }

    while ((p != NULL) || (q != NULL))
    {
        int result = 0;
        result = (p ? p->data : 0) + (q ? q->data : 0) + carry;
        carry = result / 10;
        if (carry != 0)
        {
            result = result % 10;
        }
        append(&r, result);
        if (p != NULL)
            p = p->next;
        if (q != NULL)
            q = q->next;
    }
    if (carry != 0)
    {
        append(&r, carry);
    }

    return r;
}
listi sub(listi *num1, listi *num2)
{

    listi ans;
    ans = NULL;
    InnerNode *p = *num1, *q = *num2;
    int ispneg = isnegative(p);
    if (ispneg == 1)
    {
        delete_end(&p);
        ans = add(&p, &q);
        append(&ans, 45);
        return ans;
    }

    int num1_digit = total_digits(p);
    int num2_digit = total_digits(q);
    if (num1_digit > num2_digit)
    {
        int borrow = 0;
        while (p != NULL || q != NULL)
        {
            int result = 0;
            int digit1 = p->data;
            result = (p ? digit1 : 0) - (q ? q->data : 0) - borrow;
            if (result < 0)
            {
                result = result + 10;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }
            append(&ans, result);
            if (p)
                p = p->next;
            if (q)
                q = q->next;
        }
    }
    else if (num1_digit < num2_digit)
    {
        int borrow = 0;
        while (p != NULL || q != NULL)
        {
            int result = 0;
            int digit1 = q->data;
            result = (q ? digit1 : 0) - (p ? p->data : 0) - borrow;
            if (result < 0)
            {
                result = result + 10;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }
            append(&ans, result);
            if (p)
                p = p->next;
            if (q)
                q = q->next;
        }
        append(&ans, 45);
    }

    else if (num1_digit == num2_digit)
    {
        InnerNode *p = *num1, *q = *num2;
        int which = compare(*num1, *num2);
        if (which == 1)
        {
            while (p != NULL || q != NULL)
            {

                int result = 0;
                int digit1 = p->data;

                if (q != NULL && p != NULL && p->data < q->data)
                {
                    digit1 = 10 + digit1;
                    (p->next)->data = (p->next)->data - 1;
                }
                result = (p ? digit1 : 0) - (q ? q->data : 0);
                append(&ans, result);
                if (p)
                    p = p->next;
                if (q)
                    q = q->next;
            }
        }
        else if (which == 2)
        {
            while (p != NULL || q != NULL)
            {
                // printf("#\n");
                int result = 0;
                int digit1 = q->data;
                if (q != NULL && p != NULL && q->data < p->data)
                {
                    digit1 = 10 + digit1;
                    if (q->next != NULL)
                    {
                        (q->next)->data = (q->next)->data - 1;
                    }
                }
                result = (q ? digit1 : 0) - (p ? p->data : 0);
                // printf("result = %d\n", result);
                append(&ans, result);
                p = p->next;
                q = q->next;
            }
            append(&ans, 45);
        }
        else if (which == 0)
        {
            append(&ans, 0);
        }
    }
    return ans;
}

listi mult(listi *num1, listi *num2)
{
    InnerNode *p, *q;
    q = *num2;
    int ispneg = isnegative(*num1);
    if (ispneg == 1)
    {
        delete_end(num1);
    }
    listi step0 = NULL;
    int i = 0;
    while (q)
    {
        p = *num1;
        int j = i;
        listi step1 = NULL;
        if (j != 0)
        {
            while (j)
            {
                append(&step1, 0);
                j--;
            }
        }
        int carry = 0;
        while (p)
        {
            int result = 0;
            result = (p ? p->data : 0) * (q ? q->data : 0) + carry;
            carry = result / 10;
            if (carry != 0)
            {
                result = result % 10;
            }
            append(&step1, result);
            if (p)
                p = p->next;
        }
        if (carry != 0)
        {
            append(&step1, carry);
        }
        step0 = add(&step0, &step1);
        if (q)
            q = q->next;
        i++;
    }

    if (ispneg == 1)
    {
        append(&step0, 45);
    }
    print_listi(step0);
    return step0;
}
void separate_digit(long long num, listi *head)
{
    int digit;
    while (num != 0)
    {
        digit = num % 10;
        append(head, digit);
        num = num / 10;
    }
    return;
}
listi division(listi *divident, listi *divisor)
{
    int len_divident = total_digits(*divident);
    int len_divisor = total_digits(*divisor);
    int isdivineg = isnegative(*divident);
    if (isdivineg == 1)
    {
        delete_end(divident);
    }

    listi ans = NULL;
    int addone = 0;
    if (len_divident == len_divisor)
    {
        if (whichismax(divident, divisor) == 0)
        {
            append(&ans, 1);
            return ans;
        }
        if (whichismax(divident, divisor) == 1)
        {

            int first_max = whichismax(divident, divisor);
            // printf("max = %d\n", first_max);
            int max_digi = total_digits(*divident) >= total_digits(*divisor);
            // printf("max_d = %d\n", max_digi);
            while (first_max != 2 && max_digi != 0)
            {
                *divident = sub(divident, divisor);
                addone = addone + 1;
                // printf("addone = %d\n", addone);
                first_max = whichismax(divident, divisor);
                max_digi = total_digits(*divident) >= total_digits(*divisor);
            }
            append(&ans, addone);
            if (isdivineg == 1)
            {
                append(&ans, 45);
            }

            return ans;
        }
        if (whichismax(divident, divisor) == 2)
        {
            append(&ans, 0);
            return ans;
        }
    }
    else if (len_divident > len_divisor)
    {
        int equal_digi = total_digits(*divident) == total_digits(*divisor);
        // printf("equal_d = %d\n", equal_digi);
        while (equal_digi == 0)
        {
            // printf("haaa\n");
            *divident = sub(divident, divisor);
            removeMSBzeroes(divident);
            addone = addone + 1;
            // printf("addone = %d\n", addone);
            equal_digi = total_digits(*divident) == total_digits(*divisor);
            // printf("equ = %d\n", equal_digi);
        }
        if (total_digits(*divident) == total_digits(*divisor))
        {
            addone = addone + division(divident, divisor)->data;
        }
        separate_digit(addone, &ans);
        if (isdivineg == 1)
        {
            append(&ans, 45);
        }
        return ans;
        return NULL;
    }
}

listi evaluateAndPerformOperations(listo_outer head)
{
    stack stack1 = NULL;

    listo_outer currentOuter = head;
    listo_outer Ans;
    while (currentOuter != NULL)
    {
        listi innerCurrent = currentOuter->innerList;
        listo operatorCurrent = currentOuter->operatorList;

        if (innerCurrent != NULL)
        {
            pushStack_num(&stack1, innerCurrent);
        }
        else if (operatorCurrent != NULL)
        {
            // printf("%c", operatorCurrent->op);
            listi num2 = popStack_num(&stack1);
            listi num1 = popStack_num(&stack1);
            listi ans = NULL;
            switch (operatorCurrent->op)
            {
            case '+':
                // printf("operator = %c", operatorCurrent->op);
                ans = add(&num1, &num2);
                // print_listi(ans);
                break;
            case '-':
                // printf("operator = %c", operatorCurrent->op);
                ans = sub(&num1, &num2);
                // print_listi(ans);
                break;
            case '*':
                // printf("operator = %c", operatorCurrent->op);
                ans = mult(&num1, &num2);
                break;
            case '/':
                // printf("operator = %c", operatorCurrent->op);
                ans = division(&num1, &num2);
                break;
            default:
                printf("Error: Invalid Operator\n");
                exit(EXIT_FAILURE);
            }
            printf("printing ans = \n");
            print_listi(ans);
            pushStack_num(&stack1, ans);
            // operatorCurrent = operatorCurrent->next;
        }

        currentOuter = currentOuter->next;
    }

    if (stack1 == NULL)
    {
        printf("Error: Empty Expression\n");
        exit(EXIT_FAILURE);
    }

    return popStack_num(&stack1);
}


