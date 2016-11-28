#include "AttributeValueSet.h"

AttributeValueSet_t *AttributeValueSetConstruct(int attributeIndex)
{
    AttributeValueSet_t *newAttributeValueSet = (AttributeValueSet_t *)malloc(sizeof(AttributeValueSet_t));
    if(newAttributeValueSet == NULL)
    {
        printf("Not enough memory");
        exit(0);
    }
    newAttributeValueSet->valueSize = 0;
    newAttributeValueSet->attributeIndex = attributeIndex;
    newAttributeValueSet->value = NULL;
    newAttributeValueSet->next = NULL;
    return newAttributeValueSet;
}

AttributeValueSet_t *getAttributeValueSet(AttributeValueSet_t **startAttributeValueSet, int attributeIndex)
{
    if(*startAttributeValueSet == NULL)
    {
        *startAttributeValueSet = AttributeValueSetConstruct(attributeIndex);
        return *startAttributeValueSet;
    }
    AttributeValueSet_t *currentAttributeValueSet = *startAttributeValueSet;
    AttributeValueSet_t *prevAttributeValueSet = NULL;
    while(currentAttributeValueSet != NULL)
    {
        if(currentAttributeValueSet->attributeIndex == attributeIndex)
        {
            return currentAttributeValueSet;
        }
        prevAttributeValueSet = currentAttributeValueSet;
        currentAttributeValueSet = currentAttributeValueSet->next;
    }
    prevAttributeValueSet->next = AttributeValueSetConstruct(attributeIndex);
    return prevAttributeValueSet->next;
}

void printAttributeValueSet(AttributeValueSet_t *startAttributeValueSet)
{
    AttributeValueSet_t *currentAttributeValueSet = startAttributeValueSet;
    while(currentAttributeValueSet != NULL)
    {
        printf("%d   ", currentAttributeValueSet->attributeIndex);
        printValue(currentAttributeValueSet->value);
        currentAttributeValueSet = currentAttributeValueSet->next;
    }
    printf("\n");
}

