
#include <stdio.h>
#include <string.h>

int k = 0, z = 0, i = -1, j = 0, c = 0;
char a[16], stk[20];

void check();

int main()
{
    printf("GRAMMAR is E->E+E \n E->E*E \n E->(E) \n E->id\n");

    printf("Enter input string:\n");
    scanf("%15s", a);

    c = strlen(a);

    printf("stack \t input \t action\n");
    printf("$\t%s$\tINITIAL", a);

    for (k = 0; j < c; k++)
    {
        if (a[j] == 'i' && a[j + 1] == 'd')
        {
            stk[++i] = 'i';
            stk[++i] = 'd';
            stk[i + 1] = '\0';

            j += 2;

            printf("\n$%s\t%s$\tSHIFT->id", stk, a + j);
        }
        else
        {
            stk[++i] = a[j];
            stk[i + 1] = '\0';

            j++;

            printf("\n$%s\t%s$\tSHIFT->symbols", stk, a + j);
        }

        check();
    }

    if (i == 0 && stk[0] == 'E')
        printf("\n\nInput string ACCEPTED");
    else
        printf("\n\nInput string REJECTED");

    return 0;
}

void check()
{
    int changed = 1;

    while (changed)
    {
        changed = 0;

        if (i >= 1 && stk[i-1] == 'i' && stk[i] == 'd')
        {
            stk[i-1] = 'E';
            i--;
            stk[i+1] = '\0';

            printf("\n$%s\t%s$\tREDUCE TO E", stk, a+j);
            changed = 1;
        }

        else if (i >= 2 && stk[i-2] == 'E' &&
                 stk[i-1] == '+' && stk[i] == 'E')
        {
            stk[i-2] = 'E';
            i -= 2;
            stk[i+1] = '\0';

            printf("\n$%s\t%s$\tREDUCE TO E", stk, a+j);
            changed = 1;
        }

        else if (i >= 2 && stk[i-2] == 'E' &&
                 stk[i-1] == '*' && stk[i] == 'E')
        {
            stk[i-2] = 'E';
            i -= 2;
            stk[i+1] = '\0';

            printf("\n$%s\t%s$\tREDUCE TO E", stk, a+j);
            changed = 1;
        }

        else if (i >= 2 && stk[i-2] == '(' &&
                 stk[i-1] == 'E' && stk[i] == ')')
        {
            stk[i-2] = 'E';
            i -= 2;
            stk[i+1] = '\0';

            printf("\n$%s\t%s$\tREDUCE TO E", stk, a+j);
            changed = 1;
        }
    }
}

