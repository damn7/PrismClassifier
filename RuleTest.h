#ifndef RULETEST_H_INCLUDED
#define RULETEST_H_INCLUDED

#include "Value.h"
#include "PrismRule.h"
#include "Instance.h"

typedef struct RuleTest
{
    int attributeIndex;
    struct Value *value;
    struct RuleTest *next;
}RuleTest_t;

RuleTest_t *ruleTestConstruct();
RuleTest_t *addRuleTest(RuleTest_t *lastRuleTest, struct PrismRule *rule);
int satisfies(RuleTest_t *ruleTest, Instance_t *instance);
int isMentioned(int attributeIndex, RuleTest_t *ruleTest);
#endif // RULETEST_H_INCLUDED
