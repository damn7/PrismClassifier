#include "Attribute.h"

Attribute_t *attributeConstruct(int attributeIndex, Value_t *value)
{
    Attribute_t *newAttribute = (Attribute_t *)malloc(sizeof(Attribute_t));
    if(newAttribute == NULL)
    {
        printf("Not enough memory");
        exit(0);
    }
    newAttribute->attributeIndex = attributeIndex;
    newAttribute->value = value;
    newAttribute->next = NULL;
    return newAttribute;
}

Attribute_t *addAttribute(Attribute_t **startAttribute, Attribute_t *lastAttribute, Value_t *value)
{
    if(*startAttribute == NULL)
    {
        *startAttribute = attributeConstruct(0, value);
        return *startAttribute;
    }
    else
        lastAttribute->next = attributeConstruct(lastAttribute->attributeIndex + 1, value);
    return lastAttribute->next;
}

Attribute_t *getAttribute(struct Instance *instance, int attributeIndex)
{
    Attribute_t *currentAttribute = instance->attribute;
    while(currentAttribute != NULL && currentAttribute->attributeIndex != attributeIndex)
        currentAttribute = currentAttribute->next;
    return currentAttribute;
}

void printAttribute(Attribute_t *startAttribute)
{
    Attribute_t *currentAttribute = startAttribute;
    while(currentAttribute != NULL)
    {
        printf("%s   ", currentAttribute->value->valueName);
        currentAttribute = currentAttribute->next;
    }
    printf("\n");
}

