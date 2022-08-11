#include"list.h"
#include"int_stack.h"
#include"char_stack.h"

typedef struct Num
{
    List num;
    int point;
    int sign;
}Num;


typedef struct node3
{
    Num N;
    struct node3 *next;
}node3;

typedef node3* Num_Stack;


// Num Stack
void init_Num_Stack(Num_Stack *S);
int isEmpty_Num_Stack(Num_Stack S);
void push_Num(Num_Stack* S, Num N1);
Num pop_Num(Num_Stack *S);
Num peek_Num(Num_Stack S);

// Calculator
void clean(Num* N);
void init_Num(Num *N, char *s);
int is_integer(Num N);
void print_Num(Num N);
int max_Num(Num N1, Num N2);
void sign_change(Num *N);
Num* add(Num N1, Num N2);
Num* multiply(Num N1, Num N2);
Num* divide(Num N1, Num N2);
Num* exponent(Num N1, Num N2);

// Expression Evaluation
int isOperand(char c);
int isOperator(char symbol);
int precedence(char opr);
int check_expression(char *expr);
void standardize(char *expr, char *infix);
void infix_to_postfix(char* infix, char* postfix, char_Stack* S);
Num evaluate_postfix(char str[]);