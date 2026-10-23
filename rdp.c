
#include <stdio.h>
#include <string.h>

char op[2], arg1[5], arg2[5], result[5];

int main(void)
{
    FILE *inputFile, *outputFile;

    inputFile = fopen("input.txt", "r");
    outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL)
    {
        printf("Error while opening file\n");

        if (inputFile != NULL)
            fclose(inputFile);

        if (outputFile != NULL)
            fclose(outputFile);

        return 1;
    }

    while (fscanf(inputFile, "%1s%4s%4s%4s",
                  op, arg1, arg2, result) == 4)
    {
        if (strcmp(op, "+") == 0)
        {
            fprintf(outputFile,
                    "MOV R0,%s\nADD R0,%s\nMOV %s,R0\n",
                    arg1, arg2, result);
        }
        else if (strcmp(op, "-") == 0)
        {
            fprintf(outputFile,
                    "MOV R0,%s\nSUB R0,%s\nMOV %s,R0\n",
                    arg1, arg2, result);
        }
        else if (strcmp(op, "*") == 0)
        {
            fprintf(outputFile,
                    "MOV R0,%s\nMUL R0,%s\nMOV %s,R0\n",
                    arg1, arg2, result);
        }
        else if (strcmp(op, "/") == 0)
        {
            fprintf(outputFile,
                    "MOV R0,%s\nDIV R0,%s\nMOV %s,R0\n",
                    arg1, arg2, result);
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Target code generated in output.txt\n");

    return 0;
}





