#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Data.h"
#include "Prism.h"

int main()
{
    Data_t *data = getData("datasets/contact-lenses.data");
    printData(data);

    Prism_t *prism = buildClassifier(data);
    printPrismRules(prism->rules);
    return 0;
}
