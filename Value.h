#ifndef VALUE_H_INCLUDED
#define VALUE_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct Value
{
    char valueName[50];
    int valueIndex;
    struct Value *next;
}Value_t;

Value_t *ValueConstruct(int valueIndex, char *valueName);
Value_t *getValue(Value_t **startValue, char *valueName);
int getValueSize(Value_t *startValue);
void printValue(Value_t *startValue);
#endif // VALUE_H_INCLUDED
