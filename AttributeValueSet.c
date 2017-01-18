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

void setValueSize(AttributeValueSet_t *startAttributeValueSet)
{
    AttributeValueSet_t *currentAttributeValueSet = startAttributeValueSet;
    while(currentAttributeValueSet != NULL)
    {
        currentAttributeValueSet->valueSize = getValueSize(currentAttributeValueSet->value);
        currentAttributeValueSet = currentAttributeValueSet->next;
    }
}

int getAttributeSize(AttributeValueSet_t *startAttributeValueSet)
{
    AttributeValueSet_t *currentAttributeValueSet = startAttributeValueSet;
    int attributeSize = 0;
    while(currentAttributeValueSet != NULL)
    {
        attributeSize++;
        currentAttributeValueSet = currentAttributeValueSet->next;
    }
    return attributeSize;
}

void printAttributeValueSet(AttributeValueSet_t *startAttributeValueSet)
{
    printf("ATTRIBUTE VALUE SET\n\n");
    AttributeValueSet_t *currentAttributeValueSet = startAttributeValueSet;
    while(currentAttributeValueSet != NULL)
    {
        printf("Attribute %d:  ", currentAttributeValueSet->attributeIndex);
        printValue(currentAttributeValueSet->value);
        currentAttributeValueSet = currentAttributeValueSet->next;
    }
    printf("\n");
}

