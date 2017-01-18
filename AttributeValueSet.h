#ifndef ATTRIBUTEVALUESET_H_INCLUDED
#define ATTRIBUTEVALUESET_H_INCLUDED

#include "Value.h"

typedef struct AttributeValueSet
{
    int valueSize;
    int attributeIndex;
    struct Value *value;
    struct AttributeValueSet *next;
}AttributeValueSet_t;

AttributeValueSet_t *AttributeValueSetConstruct(int attributeIndex);
AttributeValueSet_t *getAttributeValueSet(AttributeValueSet_t **startAttributeValueSet, int attributeIndex);
void setValueSize(AttributeValueSet_t *startAttributeValueSet);
int getAttributeSize(AttributeValueSet_t *startAttributeValueSet);
void printAttributeValueSet(AttributeValueSet_t *startAttributeValueset);

#endif // ATTRIBUTESET_H_INCLUDED
