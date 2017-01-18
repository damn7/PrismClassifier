#include "Data.h"
#define MAX_CHARS 120

Data_t *dataConstruct()
{
    Data_t *newData = (Data_t *)malloc(sizeof(Data_t));
    if(newData == NULL)
    {
        printf("Not enough memory");
        exit(0);
    }
    newData->attributeSize = 0;
    newData->instance = NULL;
    newData->attributeValueSet = NULL;
    newData->classification = NULL;
    return newData;
}

Data_t *getData(char *fileName)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("File not Found\n");
        exit(EXIT_FAILURE);
    }

    Data_t *data = dataConstruct();
    Instance_t *instance = NULL;
    //Instance_t *prevInstance = NULL;

    char line[MAX_CHARS];
    char valueName[50];
    int lineIndex=0;
    while (fgets (line, MAX_CHARS, file) != NULL) /* read a line */
    {
        //printf("%s", line);
        AttributeValueSet_t *attributeValueSet = NULL;
        Value_t *value = NULL;
        Attribute_t *startAttribute = NULL; Attribute_t *attribute = NULL;
        Classification_t *classification = NULL;
        //Classification_t *classification = NULL;

        int attributeIndex = 0;
        int valueNameIndex = 0;
        int i = 0;
        while(1)
        {
            //add attributes
            if(line[i] == ',')
            {
                valueName[valueNameIndex] = '\0';
                //printf("%s\n", valueName);
                attributeValueSet = getAttributeValueSet(&(data->attributeValueSet), attributeIndex);
                //printf("%d\n",attributeValueSet->attributeIndex);
                value = getValue(&(attributeValueSet->value), valueName);
                //printf("%s\n", value->valueName);
                //attribute = addAttribute(&(instance->attribute), attribute, value);

                attribute = addAttribute(&(startAttribute), attribute, value);
                //printf("%d\n", data->instance->attribute->attributeIndex);

                //(data->attributeValueSet);
                //printf("AttributeValueSet printed\n");
                //printInstance(data->instance);
                //printf("Instance printed\n");
                //printClassification(data->classification);
                //printf("Classification printed\n");

                valueNameIndex = 0;
                attributeIndex++;
            }

            // add classification
            else if(line[i] == '\n')
            {
                valueName[valueNameIndex] = '\0';
                //printf("%s\n", valueName);
                classification = getClassification(&(data->classification), valueName);
                //printf("%s\n", classification->classificationName);
                break;
            }

            else
            {
                valueName[valueNameIndex] = line[i];
                valueNameIndex++;
            }
            i++;
        }
        instance = addInstance(&(data->instance), instance, startAttribute, classification);
    }
    //free(instance);
    //prevInstance->next = NULL;
    //free(instance);
    setAttributeSize(data);
    setValueSize(data->attributeValueSet);
    fclose(file);
    return data;
}

void setAttributeSize(Data_t *data)
{
    data->attributeSize = getAttributeSize(data->attributeValueSet);
}

Data_t *makeCopy(Data_t *data)
{
    Data_t *copyData = dataConstruct();
    copyData->attributeSize = data->attributeSize;
    copyData->attributeValueSet = data->attributeValueSet;
    copyData->classification = data->classification;
    Instance_t *instance = NULL;
    Instance_t *currentInstance = data->instance;
    while(currentInstance != NULL)
    {
        instance = addInstance(&(copyData->instance), instance, currentInstance->attribute, currentInstance->classification);
        currentInstance = currentInstance->next;
    }
    return copyData;
}

void printData(Data_t *data)
{
    printAttributeValueSet(data->attributeValueSet);
    printClassification(data->classification);
    //printInstance(data->instance);
}

