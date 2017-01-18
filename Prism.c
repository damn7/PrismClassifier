#include "Prism.h"

Prism_t *prismConstruct(Data_t *data)
{
    Prism_t *newPrism = (Prism_t *)malloc(sizeof(Prism_t));
    if(newPrism == NULL)
    {
        printf("Not enough memory");
        exit(0);
    }
    newPrism->data = data;
    newPrism->rules = NULL;
    return newPrism;
}

Prism_t *buildClassifier(Data_t *data)
{
    Prism_t *newPrism = prismConstruct(data);
    newPrism->rules = buildRules(data);
    return newPrism;
}
