
#include <stdio.h>
#include <string.h>

char input[100];
int i = 0, error = 0;

void E(void);
void T(void);
void Eprime(void);
void Tprime(void);
void F(void);

int main(void)
{
    printf("Recursive Descent Parser for expressions using '+' and '*'\n");
    printf("Enter an arithmetic expression: ");

    scanf("%99s", input);

    i = 0;
    error = 0;

    E();

    if (strlen(input) == (size_t)i && error == 0)
        printf("\nAccepted\n");
    else
        printf("\nRejected\n");

    return 0;
}

void E(void)
{
    T();
    Eprime();
}

void Eprime(void)
{
    if (input[i] == '+')
    {
        i++;
        T();
        Eprime();
    }
}

void T(void)
{
    F();
    Tprime();
}

void Tprime(void)
{
    if (input[i] == '*')
    {
        i++;
        F();
        Tprime();
    }
}

void F(void)
{
    if (input[i] == 'a')
    {
        i++;
    }
    else if (input[i] == '(')
    {
        i++;
        E();

        if (input[i] == ')')
            i++;
        else
            error = 1;
    }
    else
    {
        error = 1;
    }
}
