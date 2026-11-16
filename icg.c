
#include <stdio.h>
#include <ctype.h>
#include <string.h>

char stk[64];
int top = -1;

char expr[32], pex[32];
int pcnt = 0;

void push(char ch) {
    stk[++top] = ch;
}

char pop() {
    return stk[top--];
}

int rank(char ch, int stk_rank) {
    if(ch == '+' || ch == '-') return 1;
    if(ch == '*' || ch == '/') return 2;
    if(ch == '^') return stk_rank ? 3 : 4;
    if(ch == '(') return stk_rank ? 0 : 5;
    return -1;
}

void inpos() {
    char ch, temp;

    push('(');
    strcat(expr, ")");

    for(int i = 0; expr[i] != '\0'; i++) {
        ch = expr[i];

        if(isalpha(ch))
            pex[pcnt++] = ch;

        else if(ch == ')') {
            while((temp = pop()) != '(')
                pex[pcnt++] = temp;
        }
        else {
            while(rank(stk[top], 1) >= rank(ch, 0))
                pex[pcnt++] = pop();

            push(ch);
        }
    }

    pex[pcnt] = '\0';
}


void icg() {
    char ch, a1, a2, res = '0';

    printf("\nIntermediate Code:\n");

    for(int i = 0; pex[i] != '\0'; i++) {
        ch = pex[i];

        if(isalpha(ch))
            push(ch);

        else {
            a2 = pop();
            a1 = pop();

            printf("t%c = ", res);

            if(isdigit(a1)) printf("t");
            printf("%c ", a1);

            printf("%c ", ch);

            if(isdigit(a2)) printf("t");
            printf("%c\n", a2);

            push(res++);
        }
    }
}


int main() {
    printf("Enter Expression: ");
    scanf("%31s", expr);

    inpos();
    icg();

    return 0;
}
