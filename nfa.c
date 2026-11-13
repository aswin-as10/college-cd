#include <stdio.h>
#define MAX 20

int n;
int epsilon[MAX][MAX];
int closure[MAX];
int visited[MAX];

void eclosure(int state)
{
    int i;

    visited[state] = 1;
    closure[state] = 1;

    for (i = 0; i < n; i++)
    {
        if (epsilon[state][i] == 1 && visited[i] == 0)
        {
            eclosure(i);
        }
    }
}

int main(void)
{
    int i, j, state;

    printf("Enter no of states: ");

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX)
    {
        printf("Invalid number of states\n");
        return 1;
    }

    printf("Enter epsilon transition matrix:\n");
    printf("Enter 1 if epsilon transition, else 0\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &epsilon[i][j]);
        }
    }

    for (state = 0; state < n; state++)
    {
        for (i = 0; i < n; i++)
        {
            closure[i] = 0;
            visited[i] = 0;
        }

        eclosure(state);

        printf("Epsilon-closure(q%d) = { ", state);

        for (i = 0; i < n; i++)
        {
            if (closure[i] == 1)
            {
                printf("q%d ", i);
            }
        }

        printf("}\n");
    }

    return 0;
}
