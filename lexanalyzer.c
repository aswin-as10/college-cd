
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main()
{
    char input[100];
    int i;

    printf("Enter a program (press Ctrl+D to finish):\n");

    while (fgets(input, sizeof(input), stdin) != NULL)
    {
        i = 0;

        while (input[i] != '\0')
        {
            if (isalpha(input[i]))
            {
                char word[50];
                int j = 0;

                while (isalnum(input[i]))
                    word[j++] = input[i++];

                word[j] = '\0';

                if (strcmp(word, "int") == 0 ||
                    strcmp(word, "float") == 0 ||
                    strcmp(word, "char") == 0 ||
                    strcmp(word, "if") == 0 ||
                    strcmp(word, "else") == 0 ||
                    strcmp(word, "while") == 0 ||
                    strcmp(word, "return") == 0)
                    printf("%s - Keyword\n", word);
                else
                    printf("%s - Identifier\n", word);
            }
            else if (isdigit(input[i]))
            {
                printf("%c - Number\n", input[i]);
                i++;
            }
            else if (strchr("+-*/=%<>", input[i]))
            {
                printf("%c - Operator\n", input[i]);
                i++;
            }
            else if (strchr("();{},", input[i]))
            {
                printf("%c - Special Symbol\n", input[i]);
                i++;
            }
            else
                i++;
        }
    }

    return 0;
}
