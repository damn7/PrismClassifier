#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Instance.h"
#include "AttributeValueSet.h"
#include "Classification.h"

typedef struct Data
{
    int attributeSize;
    struct Instance *instance;
    struct AttributeValueSet *attributeValueSet;
    struct Classification *classification;
}Data_t;

Data_t *dataConstruct();
Data_t *getData(char *fileName);
void setAttributeSize(Data_t *data);
Data_t *makeCopy(Data_t *data);
void printData(Data_t *data);
#endif // DATA_H_INCLUDED
