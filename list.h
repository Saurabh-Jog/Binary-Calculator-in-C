typedef struct node
{
    int digit;
    struct node *next;
    struct node *previous;
}node;

typedef node* List;

// Doubly Linked List
void init_List(List *L);
void append_first(List* L, int d);
void append_last(List *L, int d);
void traverse(List L);
int sizeofList(List L);