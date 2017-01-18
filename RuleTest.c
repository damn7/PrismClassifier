#include "RuleTest.h"

RuleTest_t *ruleTestConstruct()
{
    RuleTest_t *newRuleTest = (RuleTest_t *)malloc(sizeof(RuleTest_t));
    if(newRuleTest == NULL)
    {
        printf("Not enough memory");
        exit(0);
    }
    newRuleTest->attributeIndex = -1;
    newRuleTest->value = NULL;
    newRuleTest->next = NULL;
    return newRuleTest;
}

RuleTest_t *addRuleTest(RuleTest_t *lastRuleTest, struct PrismRule *rule)
{
    if(rule->ruleTest == NULL)
    {
        rule->ruleTest = ruleTestConstruct();
        return rule->ruleTest;
    }
    lastRuleTest->next = ruleTestConstruct();
    return lastRuleTest->next;
}

int satisfies(RuleTest_t *ruleTest, Instance_t *instance)
{
    Attribute_t *attribute = getAttribute(instance, ruleTest->attributeIndex);
    if(attribute->value == ruleTest->value)
    {
        if(ruleTest->next == NULL)
            return 1;
        else
            return satisfies(ruleTest->next, instance);
    }
    return 0;
}

int isMentioned(int attributeIndex, RuleTest_t *ruleTest)
{
    if(ruleTest == NULL)
        return 0;
    if(ruleTest->attributeIndex == attributeIndex)
        return 1;
    return isMentioned(attributeIndex, ruleTest->next);
}

