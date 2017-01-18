#ifndef PRISM_H_INCLUDED
#define PRISM_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "Data.h"
#include "PrismRule.h"

typedef struct Prism
{
    struct Data *data;
    struct PrismRule *rules;
}Prism_t;

Prism_t *prismConstruct(Data_t *data);
Prism_t *buildClassifier(Data_t *data);
#endif // PRISM_H_INCLUDED
