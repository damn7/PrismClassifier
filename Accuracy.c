#include "Accuracy.h"

Accuracy_t getAccuracy(char *rulesFileName, char *testFileName, int tokens)
{
    FILE *rulesFile = fopen(rulesFileName, "r");
    if (rulesFile == NULL)
    {
        printf("Rules File not Found\n");
        exit(EXIT_FAILURE);
    }

    FILE *testFile = fopen(testFileName, "r");
    if (testFile == NULL)
    {
        printf("Test File not Found\n");
        exit(EXIT_FAILURE);
    }

    Accuracy_t accuracy;
    accuracy.hits = accuracy.misses = 0;

    char rulesLine[MAX_CHARS],testLine[MAX_CHARS];
    while (fgets (testLine, MAX_CHARS, testFile) != NULL)
    {
        int missed = 1;
        rewind(rulesFile);
        while(fgets (rulesLine, MAX_CHARS, rulesFile) != NULL)
        {
            if(matches(rulesLine, testLine, tokens))
            {
                accuracy.hits++;
                missed = 0;
                break;
            }
        }
        if(missed)
        {
            accuracy.misses++;
        }
    }

    fclose(rulesFile);
    fclose(testFile);

    return accuracy;
}

int matches(char rulesLine[], char testLine[], int tokens)
{
    char rulesTokens[tokens][MAX_ATTRIBUTE_LEN];
    tokenize(rulesLine, rulesTokens);

    char testTokens[tokens][MAX_ATTRIBUTE_LEN];
    tokenize(testLine, testTokens);

    int tokenIndex;
    for(tokenIndex = 0; tokenIndex < tokens; tokenIndex++)
    {
        if(strcmp(rulesTokens[tokenIndex], "N/A") == 0)
            continue;
        else if(strcmp(rulesTokens[tokenIndex], testTokens[tokenIndex]) != 0)
            return 0;
    }
    return 1;
}

void tokenize(char line[], char tokenList[][MAX_ATTRIBUTE_LEN])
{
    char *cpy = strdup(line);
    char *token;
    int tokenIndex;
    for(token = strtok(cpy, ","), tokenIndex = 0;
        token && *token; token = strtok(NULL, ",\n"), tokenIndex++)
    {
        strcpy(tokenList[tokenIndex], token);
    }
}

void printAccuracy(Accuracy_t accuracy)
{
    printf("\n\nACCURACY\n\n");
    printf("Hits : %d\n", accuracy.hits);
    printf("Misses : %d\n",accuracy.misses);
    printf("Hit Percentage: %lf%\n", (100.0*accuracy.hits)/(accuracy.hits + accuracy.misses));
}
