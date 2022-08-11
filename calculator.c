#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"calculator.h"
// #include"list.h"
// #include"int_stack.h"
// #include"char_stack.h"
// #include"num_stack.h"

// Num Stack
void init_Num_Stack(Num_Stack *S)
{
    *S = NULL;
    return;
}

int isEmpty_Num_Stack(Num_Stack S)
{
    return !S;
}

void push_Num(Num_Stack* S, Num N1)
{
    node3 *nn = (node3*)malloc(sizeof(node3));
    nn->N = N1;
    nn->next = NULL;

    nn->next = *S;
    *S = nn;
    return;
}

Num pop_Num(Num_Stack *S)
{   
    node3 *p = *S;
    Num N1 = p->N;
    *S = p->next;
    free(p);
    return N1;   
}

Num peek_Num(Num_Stack S)
{   
    return S->N;
}



// Calculator
void clean(Num* N) // Removes extra zeroes at the beginning
{
    node* p = N->num;  
    while (p->next) p = p->next;
    int i = 1;
    int size = sizeofList(N->num);

    while (!p->digit && i <= size - N->point - 1)
    {   
        p = p->previous;
        node *q = N->num;
        while (q->next) q = q->next;
        q->previous->next = NULL;
        free(q);
        i++;
    }
    return;
}
  
void init_Num(Num *N, char *s) // Initialize Num with given number (string)
{
    init_List(&(N->num));
    N->sign = 1; 
    int p = 0;
    
    int i = 0;
    while (s[i] != '\0')
    {   
        if (s[i] == '.')
        {
            p = i;
            i++;
            continue;
        }
        
        int d = s[i] - '0';
        append_first(&N->num, d);
        i++;
        
    }

    if (!p) // No decimal point
    {
        append_first(&N->num, 0);
        N->point = 1;
    }
    
    else // Decimal point is present
    {
        N->point = i - p - 1;
    }
    return;

    clean(N);
}

int is_integer(Num N) // Checks whether given number is an integer or not
{   
    node *p = N.num; 
    for (int i = 1; i <= N.point; i++)
    {
        if (p->digit != 0) return 0;
        p = p->next;
    }
    return 1;
}

void print_Num(Num N) // prints the number
{
    if (N.sign == -1) printf("-");

    node* p = N.num;
    int_Stack S;
    init_int_Stack(&S);
    while (p)
    {
        push_int(&S, p->digit);
        p = p->next;
    }

    int size = sizeofList(N.num);
    
    for (int i = 0; i < size - N.point; i++) // digits before decimal point
    {   
        printf("%d", pop_int(&S));
    }

    if (is_integer(N))
    {
        printf("\n");
        return;
    }
    printf("."); 
    while (!isEmpty_int_Stack(S)) // digits after decimal point
    {
        printf("%d", pop_int(&S));
    }
    printf("\n");
    return;
}

int max_Num(Num N1, Num N2) // checks for maximum of two numbers without considering their sign  
{
    if (N1.point != N2.point)
    {   
        int diff = 0;
        if (N1.point > N2.point)
        {
            diff = N1.point - N2.point;
            for (int i = 0; i < diff; i++)
            {
                append_first(&N2.num, 0);
                N2.point++;
            }  
        }
        else 
        {
            diff = N2.point - N1.point;
            for (int i = 0; i < diff; i++)
            {
                append_first(&N1.num, 0);
                N1.point++;
            }  
        }
    }

    // print_Num(N1);
    // print_Num(N2);

    if (sizeofList(N1.num) > sizeofList(N2.num)) return 1;
    if (sizeofList(N1.num) < sizeofList(N2.num)) return 2;

    node *p = N1.num;
    node *q = N2.num;
    while (p->next) p = p->next;
    while (q->next) q = q->next;

    while (p && q)
    {
        if (p->digit > q->digit) return 1;
        else if (p->digit < q->digit) return 2;
        p = p->previous;
        q = q->previous;
    }
 
    return 1;    
}

void sign_change(Num *N) // Changes sign of given number
{
    N->sign *= -1;
    return;
}

Num* add(Num N1, Num N2) // addition
{   
    int new_point = N1.point;
    if (N1.point != N2.point)
    {   
        int diff = 0;
        if (N1.point > N2.point)
        {
            diff = N1.point - N2.point;
            for (int i = 0; i < diff; i++)
            {
                append_first(&N2.num, 0);
                N2.point++;
            }  
        }
        else 
        {
            diff = N2.point - N1.point;
            new_point = N2.point;
            for (int i = 0; i < diff; i++)
            {
                append_first(&N1.num, 0);
                N1.point++;
            }  
        }
    }

    Num *N = (Num*)malloc(sizeof(Num)); 
    N->num = NULL;
    N->point = new_point;

    if (N1.sign == N2.sign ) // same sign
    {
        N->sign = N1.sign;
        node *p = N1.num;
        node *q = N2.num;
        int sum = 0;
        int carry = 0;

        while (p && q)
        {
            sum = p->digit + q->digit + carry;
            int new_digit = sum % 10;
            carry = sum / 10;
            append_last(&N->num, new_digit);
            p = p->next;
            q = q->next;
        }

        node *r;
        if (p) r = p;
        else r = q;
        
        while (r)
        {
            sum = r->digit + carry;
            int new_digit = sum % 10;
            carry = sum / 10;
            append_last(&N->num, new_digit);
            r = r->next;
        }
        
        if (carry) append_last(&N->num, carry);

        return N;
    }

    else // opposite sign
    {   
        node *p, *q;
        if (max_Num(N1, N2) == 1)
        {
            p = N1.num;
            q = N2.num;
            N->sign = N1.sign;
        }
        else
        {
            p = N2.num;
            q = N1.num;
            N->sign = N2.sign;
        }
        
        int diff = 0;
        int borrow = 0;
        while (p && q)
        {
            diff = p->digit - q->digit - borrow;
            int new_digit;
            if (diff >= 0)
            {
                new_digit = diff;
                borrow = 0;
            }
            else
            {
                new_digit = 10 + diff;
                borrow = 1;
            }
            append_last(&N->num, new_digit);
            p = p->next;
            q = q->next;
        }
        
        while (p)
        {
            int diff = p->digit - borrow;
            int new_digit;
            if (diff >= 0)
            {
                new_digit = diff;
                borrow = 0;
            }
            else
            {
                new_digit = 10 + diff;
                borrow = 1;
            }
            append_last(&N->num, new_digit);
            p = p->next;
        }   
    }
    clean(N);
    return N;   
}

Num* multiply(Num N1, Num N2) // multiplication
{
    Num* N = (Num*)malloc(sizeof(Num));
    init_Num(N, "0");

    node *p = NULL;
    node *q = N2.num;
    int factor = 0;

    while (q)
    {
        p = N1.num;
        int product = 0;
        int carry = 0;
        Num N3;
        N3.num = NULL;
        N3.sign = 1;
        N3.point = 1;

        while (p)
        {
            product = q->digit * p->digit + carry;
            int new_digit = product % 10;
            carry = product / 10;
            append_last(&N3.num, new_digit);
            p = p->next;
        }
        while (carry)
        {
            int new_digit = carry % 10;
            carry = carry / 10;
            append_last(&N3.num, new_digit);
        }
        
        for (int i = 0; i < factor; i++) append_first(&N3.num, 0);
        N = add(*N, N3);
        factor++;
        q = q->next;
    }

    if (N1.sign == N2.sign) N->sign = 1;
    else N->sign = -1;
    N->point = N1.point + N2.point;
    clean(N);
    return N;
}

Num* divide(Num N1, Num N2) // Division
{   
    int new_sign = 1;
    if (N1.sign != N2.sign) new_sign = -1;
    N1.sign = 1;
    N2.sign = -1;

    // digits before decimal point
    Num N3 ;
    init_Num(&N3, "0");
    Num I;
    init_Num(&I, "1");
    
    while (max_Num(N1, N2) == 1)
    {   
        N1 = *add(N1, N2);
        N3 = *add(N3, I);
    }

    // digits after decimal point
    Num N4;
    init_Num(&N4, "100000");
    Num N5 = *multiply(N1, N4);
    Num N6;
    init_Num(&N6, "0");

    while (max_Num(N5, N2) == 1)
    {   
        N5 = *add(N5, N2);
        N6 = *add(N6, I);
    }

    Num N7;
    init_Num(&N7, "0.00001");
    Num *N = add(N3, *multiply(N6, N7));
    N->sign = new_sign;

    if (!is_integer(*N))
    {
        node *p = N->num;
        p->next->previous = NULL;
        N->num = p->next;
        N->point--;
        free(p);
    }
    
    return N;
}

Num* exponent(Num N1, Num N2) // Power
{
    Num N3;
    init_Num(&N3, "1");
    Num N4;
    init_Num(&N4, "1");
    sign_change(&N4);

    Num* N = &N1;

    while (max_Num(N3, N2) == 2)
    {
        N = multiply(*N, N1);
        N2 = *add(N2, N4);
    }
    return N;
} 



// Expression Evaluation
int isOperand(char c)
{
    return ((c >= '0' && c <= '9') || c == '.'); 
}

int isOperator(char symbol)
{
	if(symbol == '^' || symbol == '*' || symbol == '/' || symbol == '+' || symbol =='-')
	{
		return 1;
	}
	else
	{
	return 0;
	}
}

int precedence(char opr)
{
    if(opr == '(' ){
        return 1;
    }

    else if(opr =='+' || opr == '-'){
        return 2;
    }

    else if(opr =='*' || opr == '/'){
        return 3;
    }

    else if(opr =='^'){
        return 4;
    }

    else{
        return 0;
    }
}

int check_expression(char *expr)
{
    int i = 0;
    while (expr[i] != '\0')
    {   
        if (!isOperand(expr[i]) && !isOperator(expr[i]) && expr[i] != '(' && expr[i] != ')') return 0;
        if (isOperator(expr[i]))
        {   
            if (i == 0) return 0;
            if (expr[i+1] == '\0') return 0;
            if (isOperator(expr[i+1])) return 0;
        }
        if(expr[i] == '/' && expr[i+1] == '0') return 0;
        i++; 
    }

    i = 0;
    int flag = 0;
    while (expr[i] != '\0')
    {
        if (expr[i] == '(') flag++;
        if (expr[i] == ')') flag--;
        if (flag == -1) break;
        i++;
    }

    if (flag != 0) return 0;
    return 1;
}

void standardize(char *expr, char *infix)
{
    int i = 0;
    int j = 0;
    while (expr[i] != '\0')
    {
        if (expr[i-1] == '(')
        {
            if (expr[i] == '+' || expr[i] == '-')
            {
                infix[j] = '0';
                j++;
            }
        }
        
        infix[j] = expr[i];
        i++;
        j++;
    }
    infix[j] = '\0';
}

void infix_to_postfix(char* infix, char* postfix, char_Stack* S)
{
    int i = 0;
    int j = 0;
    
    while (infix[i] != '\0')
    {
        if (isOperator(infix[i]) || infix[i] == '(' || infix[i] == ')')
        {   
            if (isEmpty_char_Stack(*S) || infix[i] == '(')
            {
                push_char(S, infix[i]);
                i++;
            }
            
            else if (infix[i] == ')') // pop all operators till '('
            {
                while (peek_char(*S) != '(')
                {
                    postfix[j] = pop_char(S);
                    j++;
                    if (infix[i+1] != '\0')
                    {
                        postfix[j] = ' ';
                        j++;
                    }
                }
                pop_char(S); // pop '('
                i++;
            }
            
            else if (isOperator(infix[i]))
            {
                if (precedence(infix[i]) > precedence(peek_char(*S)))
                {
                    push_char(S, infix[i]);
                }
                
                else
                {
                    while (precedence(infix[i]) <= precedence(peek_char(*S)))
                    {
                        postfix[j] = pop_char(S);
                        j++;
                        if (infix[i+1] != '\0')
                        {
                            postfix[j] = ' ';
                            j++;
                        }
                    }
                    push_char(S, infix[i]);
                }
                i++;
            }
        }

        else
        {   
            while (isOperand(infix[i]) && infix[i] != '\0')
            {
                postfix[j] = infix[i];
                j++;
                i++;
            }
           
            if (infix[i] != '\0')
            {
                postfix[j] = ' ';
                j++;
            }
            
        }
    }
    if (!isEmpty_char_Stack(*S))
    {
        postfix[j] = ' ';
        j++;
    }
    
    while(!isEmpty_char_Stack(*S))
    {
        postfix[j] = pop_char(S);
        j++;
        if (!isEmpty_char_Stack(*S))
        {
            postfix[j] = ' ';
            j++;
        }
    }
    postfix[j] = '\0';
    return;
}

Num evaluate_postfix(char str[])
{
    Num_Stack S1;
    init_Num_Stack(&S1);

    int i = 0;
    while (str[i] != '\0')
    {
        if (isOperand(str[i]))
        {   
            char num[30];
            int j = 0;

            while (str[i] != ' ')
            {
                num[j] = str[i];
                j++;
                i++;
            }
            num[j] = '\0';
            Num N;
            init_Num(&N, num);
            push_Num(&S1, N);
        }

        else
        {
            Num N2 = pop_Num(&S1);
            Num N1 = pop_Num(&S1);
            Num result;
            
            switch (str[i])
            {
            case '+':
                result = *add(N1, N2);
                break;

            case '-':
                sign_change(&N2);
                result = *add(N1, N2);
                break;
            
            case '*':
                result = *multiply(N1, N2);
                break;
            
            case '/':
                result = *divide(N1, N2);
                break;
            
            case '^':
                result = *exponent(N1, N2);
                break;
            }
            push_Num(&S1, result);
            i++;
        }
        if (str[i] != '\0') i++;
    }

    Num ans = pop_Num(&S1);
    return ans;
}
