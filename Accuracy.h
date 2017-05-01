#ifndef ACCURACY_H_INCLUDED
#define ACCURACY_H_INCLUDED

#define MAX_CHARS 520
#define MAX_ATTRIBUTE_LEN 120
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Accuracy
{
    int hits;
    int misses;
    int id;
}Accuracy_t;

Accuracy_t getAccuracy(char *rulesFileName, char *testFileName, int tokenSize);
int matches(char rulesLine[], char testLine[], int tokens);
void printAccuracy(Accuracy_t accuracy);
#endif // ACCURACY_H_INCLUDED
