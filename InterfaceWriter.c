#include "InterfaceWriter.h"

void iwrite(PrismRule_t *rule, char *fileName, int attributeSize)
{
    FILE *file = fopen(fileName, "w");
    if (file == NULL)
    {
        printf("File not Found\n");
        exit(EXIT_FAILURE);
    }

    PrismRule_t *currentPrismRule = rule;
    while(currentPrismRule != NULL)
    {
        InterfaceWriter_t interfaceWriter[attributeSize];
        int attributeIndex;

        for(attributeIndex = 0; attributeIndex < attributeSize; attributeIndex++)
            interfaceWriter[attributeIndex].value = NULL;

        buildInterfaceWriter(currentPrismRule->ruleTest, interfaceWriter);

        for(attributeIndex = 0; attributeIndex < attributeSize; attributeIndex++)
        {
            if(interfaceWriter[attributeIndex].value == NULL)
            {
                fprintf(file, "%s,", "N/A");
            }
            else
            {
                fprintf(file, "%s,", interfaceWriter[attributeIndex].value->valueName);
            }
        }
        fprintf(file, "%s\n", currentPrismRule->classification->classificationName);

        currentPrismRule = currentPrismRule->next;
    }
    fclose(file);
}

void buildInterfaceWriter(RuleTest_t *ruleTest, InterfaceWriter_t interfaceWriter[])
{
    RuleTest_t *currentRuleTest = ruleTest;
    while(currentRuleTest != NULL)
    {
        interfaceWriter[currentRuleTest->attributeIndex].value = currentRuleTest->value;
        currentRuleTest = currentRuleTest->next;
    }
}
