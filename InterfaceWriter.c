#include "InterfaceWriter.h"
#include "errno.h"

void iwrite(PrismRule_t *rule, char *fileName, int attributeSize)
{
    FILE *file = fopen(fileName, "wb");
    printf("opening %s\n", fileName);
    if (file == NULL)
    {
	perror("Error");
	printf("Error No : %d %d\n", errno, ENOENT);
        printf("Interface Writer => File not Found. %s\n", fileName);
	printf("failed %s\n", fileName);
        //exit(EXIT_FAILURE);
        return ;
    }
    printf("opened %s\n", fileName);

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
                fprintf(file, "%s,", "*");
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
