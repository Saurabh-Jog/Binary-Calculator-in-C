#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"calculator.h"

int main()
{   
    printf("press 'CTRL + d' or enter '$' to exit the calculator.\n");

    while (1)
    {   
        char expr[100];
        char infix[100];
        char postfix[200];
        char_Stack S;
        init_char_Stack(&S);
        printf("Expression: ");
        gets(expr);
        if (expr[0] == '$')
        {
            break;
        }
        
        if (check_expression(expr))
        {
            standardize(expr, infix);
            infix_to_postfix(infix, postfix, &S);
            
            // printf("%s\n", infix);
            // printf("%s\n", postfix);
            printf("Ans: ");
            print_Num(evaluate_postfix(postfix));
        }
        else
        {
            printf("Invalid Expression\n");
        }
    }
}