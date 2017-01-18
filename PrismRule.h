#ifndef PRISMRULE_H_INCLUDED
#define PRISMRULE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Data.h"
#include "Classification.h"
#include "RuleTest.h"

typedef struct PrismRule
{
    struct Data *data;
    struct Classification *classification;
    struct RuleTest *ruleTest;
    int errors;
    struct PrismRule *next;
}PrismRule_t;

PrismRule_t *prismRuleConstruct(Data_t *data, Classification_t *classification);
PrismRule_t *buildRules(Data_t *data);
PrismRule_t *addRule(PrismRule_t **startRule, PrismRule_t *lastRule, Data_t *data, Classification_t *classification);
int resultRule(PrismRule_t *rule, Instance_t *instance);
Data_t *coveredBy(PrismRule_t *rule, Data_t *data);
Data_t *notCoveredBy(PrismRule_t *rule, Data_t *data);
int contains(Data_t *data, Classification_t *classification);
void printPrismRules(PrismRule_t *rule);
#endif // PRISMRULE_H_INCLUDED
