#ifndef INSTANCE_H_INCLUDED
#define INSTANCE_H_INCLUDED

#include "Attribute.h"
#include "Classification.h"

typedef struct Instance
{
    struct Attribute *attribute;
    struct Classification *classification;
    struct Instance *next;
}Instance_t;

Instance_t *InstanceConstruct();
Instance_t *addInstance(Instance_t **startInstance, Instance_t *lastInstance, struct Attribute *attribute, Classification_t *classification);
void printInstance(Instance_t *startInstance);
#endif // INSTANCE_H_INCLUDED
