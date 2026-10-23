
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20
#define SIZE 100

char production[MAX][SIZE];
char first[26][SIZE], follow[26][SIZE];
char nonTerminals[26];
int n, ntCount = 0;

int isPresent(char str[], char ch)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == ch)
            return 1;
    return 0;
}

int addToSet(char str[], char ch)
{
    if (!isPresent(str, ch))
    {
        int len = strlen(str);
        str[len] = ch;
        str[len + 1] = '\0';
        return 1;
    }
    return 0;
}

int rhsStart(int p)
{
    return (production[p][1] == '-' &&
            production[p][2] == '>') ? 3 : 2;
}

int main()
{
    int i, j, k, changed;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX)
        return 1;

    printf("Enter productions (use # for epsilon):\n");

    for (i = 0; i < n; i++)
    {
        scanf("%99s", production[i]);

        char lhs = production[i][0];

        if (!isupper((unsigned char)lhs))
        {
            printf("Invalid non-terminal.\n");
            return 1;
        }

        if (!isPresent(nonTerminals, lhs))
        {
            addToSet(nonTerminals, lhs);
            ntCount++;
        }
    }

    /* Calculate FIRST sets */
    do
    {
        changed = 0;

        for (i = 0; i < n; i++)
        {
            char lhs = production[i][0];
            int pos = rhsStart(i);
            int nullable = 1;

            if (production[i][pos] == '#')
            {
                changed |= addToSet(first[lhs - 'A'], '#');
                continue;
            }

            while (production[i][pos] != '\0')
            {
                char symbol = production[i][pos];

                if (!isupper((unsigned char)symbol))
                {
                    changed |= addToSet(first[lhs - 'A'], symbol);
                    nullable = 0;
                    break;
                }

                for (j = 0; first[symbol - 'A'][j] != '\0'; j++)
                    if (first[symbol - 'A'][j] != '#')
                        changed |= addToSet(
                            first[lhs - 'A'],
                            first[symbol - 'A'][j]);

                if (!isPresent(first[symbol - 'A'], '#'))
                {
                    nullable = 0;
                    break;
                }

                pos++;
            }

            if (nullable && production[i][pos] == '\0')
                changed |= addToSet(first[lhs - 'A'], '#');
        }
    } while (changed);

    /* Start symbol gets $ in FOLLOW */
    addToSet(follow[production[0][0] - 'A'], '$');

    /* Calculate FOLLOW sets */
    do
    {
        changed = 0;

        for (i = 0; i < n; i++)
        {
            char lhs = production[i][0];
            int start = rhsStart(i);

            for (j = start; production[i][j] != '\0'; j++)
            {
                char symbol = production[i][j];

                if (!isupper((unsigned char)symbol))
                    continue;

                int nullable = 1;

                for (k = j + 1; production[i][k] != '\0'; k++)
                {
                    char next = production[i][k];

                    if (!isupper((unsigned char)next))
                    {
                        changed |= addToSet(
                            follow[symbol - 'A'], next);
                        nullable = 0;
                        break;
                    }

                    for (int t = 0; first[next - 'A'][t] != '\0'; t++)
                        if (first[next - 'A'][t] != '#')
                            changed |= addToSet(
                                follow[symbol - 'A'],
                                first[next - 'A'][t]);

                    if (!isPresent(first[next - 'A'], '#'))
                    {
                        nullable = 0;
                        break;
                    }
                }

                if (nullable)
                    for (k = 0; follow[lhs - 'A'][k] != '\0'; k++)
                        changed |= addToSet(
                            follow[symbol - 'A'],
                            follow[lhs - 'A'][k]);
            }
        }
    } while (changed);

    printf("\nFIRST sets:\n");
    for (i = 0; i < ntCount; i++)
    {
        char nt = nonTerminals[i];
        printf("FIRST(%c) = { ", nt);

        for (j = 0; first[nt - 'A'][j] != '\0'; j++)
            printf("%c ", first[nt - 'A'][j]);

        printf("}\n");
    }

    printf("\nFOLLOW sets:\n");
    for (i = 0; i < ntCount; i++)
    {
        char nt = nonTerminals[i];
        printf("FOLLOW(%c) = { ", nt);

        for (j = 0; follow[nt - 'A'][j] != '\0'; j++)
            printf("%c ", follow[nt - 'A'][j]);

        printf("}\n");
    }

    return 0;
}



E=TR
R=+TR
R=#
T=FY
Y=*FY
Y=#
F=(E)
F=i
