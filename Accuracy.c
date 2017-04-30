#include "Accuracy.h"
void tokenizei(char line[], char tokenList[][MAX_ATTRIBUTE_LEN]);

Accuracy_t getAccuracy(char *rulesFileName, char *testFileName, int tokens)
{
    FILE *rulesFile = fopen(rulesFileName, "r");
    if (rulesFile == NULL)
    {
        printf("Accuracy => Rules File not Found %s\n", rulesFileName);
        exit(EXIT_FAILURE);
    }

    FILE *testFile = fopen(testFileName, "r");
    if (testFile == NULL)
    {
        printf("Accuracy => Test File not Found %s\n", testFileName);
        exit(EXIT_FAILURE);
    }
    Accuracy_t accuracy;
    accuracy.hits = accuracy.misses = 0;

    char rulesLine[MAX_CHARS],testLine[MAX_CHARS];
    while (fgets (testLine, MAX_CHARS, testFile) != NULL)
    {
	//accuracy.hits = 54;
	//accuracy.misses = 33;
	//break;
        int missed = 1;
        rewind(rulesFile);
//	printf("Rewind Executed\n");
        while(fgets (rulesLine, MAX_CHARS, rulesFile) != NULL)
        {
	//	fflush(stdout);
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
	//printf("Accuracy: closed\n");

    return accuracy;
}

int matches(char rulesLine[], char testLine[], int tokens)
{
	printf("\n");
//	printf("matching\n");
    char rulesTokens[tokens][MAX_ATTRIBUTE_LEN];
    tokenizei(rulesLine, rulesTokens);

    char testTokens[tokens][MAX_ATTRIBUTE_LEN];
    tokenizei(testLine, testTokens);
    int i;
/*    for(i = 0; i < tokens; i++)
    {
	printf("%s\n", rulesTokens[i]);
	printf("%s\n", testTokens[i]);
    }
*/
    int tokenIndex;
    for(tokenIndex = 0; tokenIndex < tokens; tokenIndex++)
    {
        if(strcmp(rulesTokens[tokenIndex], "*") == 0)
            continue;
        else if(strcmp(rulesTokens[tokenIndex], testTokens[tokenIndex]) != 0)
            return 0;
    }
    return 1;
}

void tokenizei(char line[], char tokenList[][MAX_ATTRIBUTE_LEN])
{
	//printf("\n");
	//printf("tokeninzing\n");
    char *cpy = strdup(line);
    char *token;
    int tokenIndex;
    for(token = strtok(cpy, ","), tokenIndex = 0;
        token && *token; token = strtok(NULL, ",\n"), tokenIndex++)
    {
        strcpy(tokenList[tokenIndex], token);
    }
	/*
	printf("To tokenize : %s\n", line);
	int i;
	for(i = 0;i < tokenIndex;++i){
		printf("\"%s\"\n", tokenList[i]);
	}*/
}

void printAccuracy(Accuracy_t accuracy)
{
    printf("\n\nACCURACY\n\n");
    printf("Hits : %d\n", accuracy.hits);
    printf("Misses : %d\n",accuracy.misses);
    printf("Hit Percentage: %lf%\n", (100.0*accuracy.hits)/(accuracy.hits + accuracy.misses));
}
