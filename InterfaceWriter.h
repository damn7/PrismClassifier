#ifndef INTERFACEWRITER_H_INCLUDED
#define INTERFACEWRITER_H_INCLUDED

#define MAX_CHARS 120
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Value.h"
#include "PrismRule.h"

typedef struct InterfaceWriter
{
    struct Value *value;
}InterfaceWriter_t;

void iwrite(PrismRule_t *rule, char *fileName, int attributeSize);
void buildInterfaceWriter(RuleTest_t *ruleTest, InterfaceWriter_t interfaceWriter[]);
#endif // INTERFACEWRITER_H_INCLUDED
