#include<stdlib.h>
#include"char_stack.h"


// Character Stack
void init_char_Stack(char_Stack *S)
{
    *S = NULL;
    return;
}

int isEmpty_char_Stack(char_Stack S)
{
    return !S;
}

void push_char(char_Stack *S, char c)
{   
    node2 *nn = (node2*)malloc(sizeof(node2));
    nn->ch = c;
    nn->next = NULL;

    if (!*S)
    {
        *S = nn;
        return;
    }

    nn->next = *S;
    *S = nn;
    return;
}

char pop_char(char_Stack *S)
{   
    char x = '$';
    if (isEmpty_char_Stack(*S)) return x;

    node2 *p = *S;
    x = p->ch;
    *S = p->next;
    free(p);
    return x;   
}

char peek_char(char_Stack S)
{   
    int x = '$';
    if (isEmpty_char_Stack(S)) return x;
    return S->ch;
}
