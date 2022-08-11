typedef struct node1
{
    int data;
    struct node1 *next;
}node1;

typedef node1* int_Stack;

// Integer stack
void init_int_Stack(int_Stack *S);
int isEmpty_int_Stack(int_Stack S);
void push_int(int_Stack *S, int num);
int pop_int(int_Stack *S);
int peek_int(int_Stack S);
