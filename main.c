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
    char *fileName = argv[1];
    int N = atoi(argv[2]);
    int P = atoi(argv[3]);
    int C = atoi(argv[4]);
    int A = atoi(argv[5]);
    #pragma omp parallel shared(fileName, N, P, C, A) num_threads(5)
    {
	int nthread=omp_get_num_threads();
   	int id =omp_get_thread_num();
	char ID[100];
	sprintf(ID, "%d", id);
	//printf("%s\n",ID);
	
	printf("Splitting %d.............\n",id);
    	split(fileName, N, P, C, A, id, nthread);
	//printf("DONE\n");
	
	printf("Data  %d.............\n",id);
	char trainsetPath[100];
	trainsetPath[0] = '\0';
	strcat(strcat(strcat(strcat(trainsetPath, TRAINSETPATH), fileName), ID), ".data");
	//printf("%s\n",trainsetPath);
    	Data_t *data = getData(trainsetPath);
    	//printData(data);

	printf("Classifying %d.............\n",id);
    	Prism_t *prism = buildClassifier(data);
    	//printPrismRules(prism->rules);

	printf("Interface Writing %d.............\n",id);
	char rulesetPath[100];
	rulesetPath[0] = '\0';
	strcat(strcat(strcat(strcat(rulesetPath, RULESETPATH), fileName), ID), ".data");
	printf("%s\n", rulesetPath);
    	iwrite(prism->rules, rulesetPath, data->attributeSize);

	printf("Accuracy %d.............\n",id);
	char testsetPath[100];
	testsetPath[0] = '\0';
	strcat(strcat(strcat(strcat(testsetPath, TESTSETPATH), fileName), ID), ".data");
    	Accuracy_t accuracy = getAccuracy(rulesetPath, testsetPath, data->attributeSize + 1);
	/*if(accuracy){
		printf("accuracy not null\n");
	}
	if(accuracy == NULL){
                printf("accuracy null\n");
        }*/
	printf("accuracy %d\n", accuracy.hits);
    	printAccuracy(accuracy);
    }
    return 0;
}
