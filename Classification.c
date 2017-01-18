#include "Classification.h"

Classification_t *ClassificationConstruct(int classificationIndex, char *classificationName)
{
    Classification_t *newClassification = (Classification_t *)malloc(sizeof(Classification_t));
    if(newClassification == NULL)
    {
        printf("Not enough memory");
        exit(0);
    }
    newClassification->classificationIndex = classificationIndex;
    strcpy(newClassification->classificationName, classificationName);
    newClassification->next = NULL;
    return newClassification;
}

Classification_t *getClassification(Classification_t **startClassification, char *classificationName)
{
    if(*startClassification == NULL)
    {
        *startClassification = ClassificationConstruct(0, classificationName);
        return *startClassification;
    }
    Classification_t *currentClassification = *startClassification;
    Classification_t *prevClassification = NULL;
    while(currentClassification != NULL)
    {
        if(strcmp(currentClassification->classificationName, classificationName) == 0)
        {
            return currentClassification;
        }
        prevClassification = currentClassification;
        currentClassification = currentClassification->next;
    }
    prevClassification->next = ClassificationConstruct(prevClassification->classificationIndex+1, classificationName);
    return prevClassification->next;
}

void printClassification(Classification_t *startClassification)
{
    printf("CLASSIFICATION\n\n");
    Classification_t *currentClassification = startClassification;
    while(currentClassification != NULL)
    {
        printf("%s   ", currentClassification->classificationName);
        currentClassification = currentClassification->next;
    }
    printf("\n\n");
}

