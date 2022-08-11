typedef struct node2
{
    char ch;
    struct node2 *next;
}node2;

typedef node2* char_Stack;

// Character stack
void init_char_Stack(char_Stack *S);
int isEmpty_char_Stack(char_Stack S);
void push_char(char_Stack *S, char c);
char pop_char(char_Stack *S);
char peek_char(char_Stack S);
