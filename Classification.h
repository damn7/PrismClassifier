#ifndef CLASSIFICATION_H_INCLUDED
#define CLASSIFICATION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Classification
{
    int classificationIndex;
    char classificationName[50];
    struct Classification *next;
}Classification_t;

Classification_t *ClassificationConstruct(int classificationIndex, char *classificationName);
Classification_t *getClassification(Classification_t **startClassification, char *classificationName);
void printClassification(Classification_t *startClassification);

#endif // CLASS_H_INCLUDED
