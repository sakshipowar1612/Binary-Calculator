#include <stdio.h>
#include <stdlib.h>
#include "ProBC2.c"

int main()
{
    long long noOfchar;
    printf("Enter no. of characters you want to store: ");
    scanf("%lld", &noOfchar);

    char *mathematical_exp;
    mathematical_exp = (char *)malloc(noOfchar * sizeof(char));

    // Clear the input buffer
    while (getchar() != '\n')
        ;

    int size = 0;
    char op_digit;
    while (1)
    {
        scanf(" %c", &op_digit);
        if (op_digit == '$')
        {
            break;
        }
        mathematical_exp[size] = op_digit;
        size++;
    }
    printf("size = %d\n", size);

    // printf("\nmathematical expression = \n");

    // int u_size = 0;
    // while (u_size < size)
    // {
    //     printf("%c", mathematical_exp[u_size]);
    //     u_size++;
    // }
    // printf("\n");
    // char *E = mathematical_exp;

    exp_stack s1;
    init_s(&s1, 50);
    char c;
    char postfix[50];
    int i = 0, j = 0;
    while (mathematical_exp[i] != '\0')
    {
        c = mathematical_exp[i];
        if (isdigit(c))
        {
            postfix[j++] = c;
            if (!isdigit(mathematical_exp[i + 1]))
            {
                postfix[j++] = '#';
            }
        }
        else if (c == '(')
        {
            push(&s1, c);
        }
        else if (c == ')')
        {
            while (!isEmpty(s1) && peek(&s1) != '(')
            {
                postfix[j++] = pop(&s1);
                postfix[j++] = '#';
            }
            if (peek(&s1) == '(')
            {
                pop(&s1);
            }
        }
        else
        {
            if (c == '+' || c == '-' || c == '/' || c == '*' || c == '%')
            {
                if (isEmpty(s1))
                {
                    push(&s1, c);
                }
                else
                {
                    while (!isEmpty(s1) && precedence(peek(&s1)) >= precedence(c))
                    {
                        postfix[j++] = pop(&s1);
                        postfix[j++] = '#';
                    }
                    push(&s1, c);
                }
            }
        }

        i++;
    }
    while (!isEmpty(s1))
    {
        postfix[j++] = pop(&s1);
        postfix[j++] = '#';
    }
    printf("\n");
    printf("postfix = ");
    for (int i = 0; i < j; i++)
    {
        printf("%c ", postfix[i]);
    }

    listo_outer head = createOuterNode();
    listo_outer currentOuter = head;

    char ch;
    int e = 0;
    while (postfix[e] != '\0')
    {
        ch = postfix[e];
        if (isdigit(ch))
        {
            // Read an integer, add it to the current outer node
            addInnerNode(currentOuter, ch - '0');
        }
        else if (ch == '#')
        {
            // Read a character, check if it is '#'
            // Add a new outer node
            currentOuter = addOuterNode(&head);
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '#')
        {

            addOperatorNode(currentOuter, ch);
        }
        e++;
    }
    printf("\n");
    printLinkedList(head);
    free(mathematical_exp);
    listi result;
    result = evaluateAndPerformOperations(head);
    removeMSBzeroes(&result);
    listi ans = NULL;
    forward_list(&result, &ans);
    printf("ans = ");

    if (isnegative(result) == 1)
    {
        delete_beg(&ans);
        printf("-");
    }

    print_listi(ans);
    free(result);
    return 0;
}