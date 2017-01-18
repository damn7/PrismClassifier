#include "PrismRule.h"

PrismRule_t *prismRuleConstruct(Data_t *data, Classification_t *classification)
{
    PrismRule_t *newPrismRule = (PrismRule_t *)malloc(sizeof(PrismRule_t));
    if(newPrismRule == NULL)
    {
        printf("Not enough memory");
        exit(0);
    }
    newPrismRule->data = data;
    newPrismRule->classification = classification;
    newPrismRule->ruleTest = NULL;
    newPrismRule->errors = 0;
    newPrismRule->next = NULL;
    Instance_t *instance = data->instance;
    while(instance != NULL)
    {
        if(instance->classification != classification)
            newPrismRule->errors++;
        instance = instance->next;
    }
    return newPrismRule;
}

PrismRule_t *buildRules(Data_t *originalData)
{
    //printf("Inside build Rules\n");
    PrismRule_t *startRule = NULL; PrismRule_t *rule = NULL;
    RuleTest_t *ruleTest = NULL;
    Classification_t *currentClassification = originalData->classification;

    while(currentClassification != NULL)
    {
        //printf("Inside classification\n");
        Data_t *data = makeCopy(originalData);
        int checkRuleIndex = 0;
        while(contains(data, currentClassification))
        {
            //printf("Inside Making a Rule\n");
            rule = addRule(&startRule, rule, data, currentClassification);
            //printf("%d\n", rule->classification->classificationIndex);
            Data_t *ruleData = makeCopy(data);
            int checkAttributeIndex = 0;
            while(rule->errors != 0)
            {
                //printf("Inside Adding a Test\n");
                ruleTest = addRuleTest(ruleTest, rule);
                int bestCorrect = 0;
                int bestCovers = 0;
                int attributeUsed = 0;

                AttributeValueSet_t *currentAttributeValueSet = ruleData->attributeValueSet;
                while(currentAttributeValueSet != NULL)
                {
                    //printf("Inside Checking an Attribute\n");
                    if(isMentioned(currentAttributeValueSet->attributeIndex, rule->ruleTest))
                    {
                        attributeUsed++;
                        currentAttributeValueSet = currentAttributeValueSet->next;
                        continue;
                    }

                    int valueSize = currentAttributeValueSet->valueSize;
                    int covers[valueSize];
                    memset(covers, 0, sizeof(covers));
                    int correct[valueSize];
                    memset(correct, 0, sizeof(correct));

                    Instance_t *currentInstance = ruleData->instance;
                    //printInstance(currentInstance);
                    while(currentInstance != NULL)
                    {
                        Attribute_t *attribute = getAttribute(currentInstance, currentAttributeValueSet->attributeIndex);
                        covers[attribute->value->valueIndex]++;
                        if(currentInstance->classification == currentClassification)
                            correct[attribute->value->valueIndex]++;
                        currentInstance = currentInstance->next;
                    }

                    Value_t *currentValue = currentAttributeValueSet->value;
                    while(currentValue != NULL)
                    {
                        //printf("Inside Adding a Value\n");
                        //printf("Value = %s\n", currentValue->valueName);
                        //printf("correct = %d   covers = %d\n", correct[currentValue->valueIndex], covers[currentValue->valueIndex]);
                        int diff = correct[currentValue->valueIndex] * bestCovers - bestCorrect * covers[currentValue->valueIndex];
                        if(ruleTest->attributeIndex == -1 || diff > 0 || (diff == 0 && correct[currentValue->valueIndex] > bestCorrect))
                        {
                            bestCorrect = correct[currentValue->valueIndex];
                            bestCovers = covers[currentValue->valueIndex];
                            ruleTest->attributeIndex = currentAttributeValueSet->attributeIndex;
                            ruleTest->value = currentValue;
                            rule->errors = bestCovers - bestCorrect;
                        }
                        //printf("%s\n", currentValue->valueName);
                        currentValue = currentValue->next;
                    }
                    //printf("%d\n", currentAttributeValueSet->attributeIndex);
                    currentAttributeValueSet = currentAttributeValueSet->next;
                }
                ruleData = coveredBy(rule, ruleData);
                //printInstance(ruleData->instance);
                if(attributeUsed == ((originalData->attributeSize) - 1))
                {
                    break;
                }
                //printf("CheckAttributeIndex = %d\n", checkAttributeIndex);
                checkAttributeIndex++;
            }
            data = notCoveredBy(rule, data);
            //printInstance(data->instance);
            //printf("CheckRuleIndex = %d\n", checkRuleIndex);
            checkRuleIndex++;
            //printPrismRules(startRule);
        }
        //printf("CheckCurrentClassificationIndex = %d\n", currentClassification->classificationIndex);
        currentClassification = currentClassification->next;
    }
    return startRule;
}

PrismRule_t *addRule(PrismRule_t **startRule, PrismRule_t *lastRule, Data_t *data, Classification_t *classification)
{
    if(*startRule == NULL)
    {
        *startRule = prismRuleConstruct(data, classification);
        return *startRule;
    }
    lastRule->next = prismRuleConstruct(data, classification);
    return lastRule->next;
}

int resultRule(PrismRule_t *rule, Instance_t *instance)
{
    if(rule->ruleTest == NULL || satisfies(rule->ruleTest, instance))
        return rule->classification->classificationIndex;
    return -1;
}

Data_t *coveredBy(PrismRule_t *rule, Data_t *data)
{
    Data_t *newData = dataConstruct();
    newData->attributeValueSet = data->attributeValueSet;
    newData->classification = data->classification;
    Instance_t *currentInstance = data->instance;
    Instance_t *instance = NULL;
    while(currentInstance != NULL)
    {
        if(resultRule(rule, currentInstance) != -1)
            instance = addInstance(&(newData->instance), instance, currentInstance->attribute, currentInstance->classification);
        currentInstance = currentInstance->next;
    }
    return newData;
}

Data_t *notCoveredBy(PrismRule_t *rule, Data_t *data)
{
    Data_t *newData = dataConstruct();
    newData->attributeSize = data->attributeSize;
    newData->attributeValueSet = data->attributeValueSet;
    newData->classification = data->classification;
    Instance_t *currentInstance = data->instance;
    Instance_t *instance = NULL;
    while(currentInstance != NULL)
    {
        if(resultRule(rule, currentInstance) == -1)
            instance = addInstance(&(newData->instance), instance, currentInstance->attribute, currentInstance->classification);
        currentInstance = currentInstance->next;
    }
    return newData;
}

int contains(Data_t *data, Classification_t *classification)
{
    Instance_t *currentInstance = data->instance;
    while(currentInstance != NULL)
    {
        if(currentInstance->classification == classification)
            return 1;
        currentInstance = currentInstance->next;
    }
    return 0;
}

void printPrismRules(PrismRule_t *rule)
{
    printf("\n\nRULES GENERATED\n\n");
    PrismRule_t *currentPrismRule = rule;
    int ruleIndex = 0;
    while(currentPrismRule != NULL)
    {
        printf("Rule %d:  ", ruleIndex);
        printf("If  ");
        RuleTest_t *currentRuleTest = currentPrismRule->ruleTest;
        while(currentRuleTest != NULL)
        {
            printf("A%d = ", currentRuleTest->attributeIndex);
            printf("%s  ", currentRuleTest->value->valueName);
            if(currentRuleTest->next == NULL)
                printf("then  Class = ");
            else
                printf("and  ");
            currentRuleTest = currentRuleTest->next;
        }
        printf("%s\n", currentPrismRule->classification->classificationName);
        currentPrismRule = currentPrismRule->next;
        ruleIndex++;
    }
}
