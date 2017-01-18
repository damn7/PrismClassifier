#include "Value.h"

Value_t *ValueConstruct(int valueIndex, char *valueName)
{
    Value_t *newValue = (Value_t *)malloc(sizeof(Value_t));
    if(newValue == NULL)
    {
        printf("Not enough memory");
        exit(0);
    }
    newValue->valueIndex = valueIndex;
    strcpy(newValue->valueName, valueName);
    newValue->next = NULL;
    return newValue;
}

Value_t *getValue(Value_t **startValue, char *valueName)
{
    if(*startValue == NULL)
    {
        *startValue = ValueConstruct(0, valueName);
        return *startValue;
    }
    Value_t *currentValue = *startValue;
    Value_t *prevValue = NULL;
    while(currentValue != NULL)
    {
        if(strcmp(currentValue->valueName, valueName) == 0)
        {
            return currentValue;
        }
        prevValue = currentValue;
        currentValue = currentValue->next;
    }
    prevValue->next = ValueConstruct(prevValue->valueIndex+1, valueName);
    return prevValue->next;
}

int getValueSize(Value_t *startValue)
{
    int valueSize = 0;
    Value_t *currentValue = startValue;
    while(currentValue != NULL)
    {
        valueSize++;
        currentValue = currentValue->next;
    }
    return valueSize;
}

void printValue(Value_t *startValue)
{
    Value_t *currentValue = startValue;
    while(currentValue != NULL)
    {
        printf("%s   ", currentValue->valueName);
        currentValue = currentValue->next;
    }
    printf("\n");
}
