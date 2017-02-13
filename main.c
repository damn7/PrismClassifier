#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Data.h"
#include "Prism.h"
#include "InterfaceWriter.h"
#include "Accuracy.h"

int main()
{
    Data_t *data = getData("datasets/contact-lenses.csv");
    printData(data);

    Prism_t *prism = buildClassifier(data);
    printPrismRules(prism->rules);

    iwrite(prism->rules, "rules/contact-lenses.csv", data->attributeSize);

    Accuracy_t accuracy = getAccuracy("rules/contact-lenses.csv", "testsets/contact-lenses.csv", data->attributeSize + 1);
    printAccuracy(accuracy);
    return 0;
}
