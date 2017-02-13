#ifndef VALUE_H_INCLUDED
#define VALUE_H_INCLUDED

#define MAX_ATTRIBUTE_LEN 20
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct Value
{
    char valueName[MAX_ATTRIBUTE_LEN];
    int valueIndex;
    struct Value *next;
}Value_t;

Value_t *ValueConstruct(int valueIndex, char *valueName);
Value_t *getValue(Value_t **startValue, char *valueName);
int getValueSize(Value_t *startValue);
void printValue(Value_t *startValue);
#endif // VALUE_H_INCLUDED
