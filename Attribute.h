#ifndef ATTRIBUTE_H_INCLUDED
#define ATTRIBUTE_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include "Instance.h"
#include "Value.h"

typedef struct Attribute
{
    int attributeIndex;
    struct Value *value;
    struct Attribute *next;
}Attribute_t;

Attribute_t *attributeConstruct(int attributeIndex, Value_t *value);
Attribute_t *addAttribute(Attribute_t **startAttribute, Attribute_t *lastAttribute, Value_t *value);
Attribute_t *getAttribute(struct Instance *instance, int attributeIndex);
void printAttribute(Attribute_t *startAttribute);
#endif // ATTRIBUTE_H_INCLUDED
