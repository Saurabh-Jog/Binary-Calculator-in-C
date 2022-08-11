#include<stdlib.h>
#include<limits.h>
#include"int_stack.h"

// Integer stack
void init_int_Stack(int_Stack *S)
{
    *S = NULL;
    return;
}

int isEmpty_int_Stack(int_Stack S)
{
    return !S;
}

void push_int(int_Stack *S, int num)
{   
    node1 *nn = (node1*)malloc(sizeof(node1));
    nn->data = num;
    nn->next = NULL;

    nn->next = *S;
    *S = nn;
    return;
}

int pop_int(int_Stack *S)
{   
    int x = INT_MIN;
    if (isEmpty_int_Stack(*S)) return x;

    node1 *p = *S;
    x = p->data;
    *S = p->next;
    free(p);
    return x;   
}

int peek_int(int_Stack S)
{   
    int x = INT_MIN;
    if (isEmpty_int_Stack(S)) return x;
    return S->data;
}


