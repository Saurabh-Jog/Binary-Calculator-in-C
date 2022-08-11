#include<stdlib.h>
#include"list.h"
#include<stdio.h>

// Doubly Linked List
void init_List(List *L)
{
    *L = NULL;
    return;
}

void append_first(List* L, int d)
{
    node *nn = (node*)malloc(sizeof(node));
    if (!nn) return;
    nn->digit = d;
    nn->previous = NULL;
    nn->next = *L;

    if (!*L) 
    {
        *L = nn;
        return;
    }
    
    node *p = *L;
    p->previous = nn;
    *L = nn;
    return;
}

void append_last(List *L, int d)
{
    node *nn = (node*)malloc(sizeof(node));
    nn->digit = d;
    nn->next = NULL;
    nn->previous = NULL;

    if (!*L)
    {
        *L = nn;
        return;
    }
    
    node *p = *L;
    while (p->next) p = p->next;
    p->next = nn;
    nn->previous = p;
    return;
}

void traverse(List L)
{
    node *p = L;
    while (p)
    {
        printf("%d", p->digit);
        p = p->next;
    }
    printf("\n");
    return;
}

int sizeofList(List L)
{
    if (!L) return 0;
    node *p = L;
    int i = 1;
    while (p->next)
    {
        i++;
        p = p->next;
    }
    return i;
}

