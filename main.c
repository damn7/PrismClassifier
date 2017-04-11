#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Constants.h"
#include "Splitter.h"
#include "Data.h"
#include "Prism.h"
#include "InterfaceWriter.h"
#include "Accuracy.h"

int main(int argc, char **argv)
{
    if(argc < 6)
    {
        printf(USAGE);
        exit(-1);
    }
    split(argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));

    Data_t *data = getData("trainsets/input.data");
    printData(data);

    Prism_t *prism = buildClassifier(data);
    printPrismRules(prism->rules);

    iwrite(prism->rules, "rules/input.csv", data->attributeSize);

    Accuracy_t accuracy = getAccuracy("rules/input.csv", "testsets/input.data", data->attributeSize + 1);
    printAccuracy(accuracy);
    return 0;
}
