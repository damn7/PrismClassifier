#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Data.h"

int main()
{
    Data_t *data = getData("/home/sakar/Downloads/UCI/iris/temp.data");
    printData(data);
    return 0;
}
