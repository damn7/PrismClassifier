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
    Accuracy_t maxAccuracy;
    maxAccuracy.hits = maxAccuracy.misses = 0;
    maxAccuracy.id = -1;
    #pragma omp parallel shared(fileName, N, P, C, A, maxAccuracy) num_threads(PROCESSORS)
    {
	int nthread=omp_get_num_threads();
   	int id =omp_get_thread_num();
	char ID[100];
	sprintf(ID, "%d", id);
	//printf("%s\n",ID);
	
	//printf("Splitting %d.............\n",id);
    	split(fileName, N, P, C, A, id, nthread);
	//printf("DONE\n");
	
	//printf("Data  %d.............\n",id);
	char trainsetPath[100];
	trainsetPath[0] = '\0';
	strcat(strcat(strcat(strcat(trainsetPath, TRAINSETPATH), fileName), ID), ".data");
	//printf("%s\n",trainsetPath);
    	Data_t *data = getData(trainsetPath);
    	//printData(data);

	//printf("Classifying %d.............\n",id);
    	Prism_t *prism = buildClassifier(data);
    	//printPrismRules(prism->rules);

	//printf("Interface Writing %d.............\n",id);
	char rulesetPath[100];
	rulesetPath[0] = '\0';
	strcat(strcat(strcat(strcat(rulesetPath, RULESETPATH), fileName), ID), ".data");
	//printf("%s\n", rulesetPath);
    	iwrite(prism->rules, rulesetPath, data->attributeSize);

	//printf("Accuracy %d.............\n",id);
	char testsetPath[100];
	testsetPath[0] = '\0';
	strcat(strcat(strcat(strcat(testsetPath, TESTSETPATH), fileName), ID), ".data");
    	Accuracy_t accuracy = getAccuracy(rulesetPath, testsetPath, data->attributeSize + 1);

	accuracy.id = id;
	int diff = accuracy.hits * maxAccuracy.misses - maxAccuracy.hits * accuracy.misses;
	if(maxAccuracy.id == -1 || diff > 0 || (diff == 0 && accuracy.hits > maxAccuracy.hits))
	{
	    maxAccuracy.hits = accuracy.hits;
	    maxAccuracy.misses = accuracy.misses;
	    maxAccuracy.id = accuracy.id;
	}
	/*if(accuracy){
		printf("accuracy not null\n");
	}
	if(accuracy == NULL){
                printf("accuracy null\n");
        }*/
	//printf("accuracy %d\n", accuracy.hits);
    	printAccuracy(accuracy);
    }

    printf("\nMAX ACCURACY\n");
    printAccuracy(maxAccuracy);

    int id;
    char ID[100], path[100];
    
    for(id = 0;id < PROCESSORS; id++)
    {
	if(id != maxAccuracy.id)
	{
	    //remove the trainset files except the one with the maximum accuracy.
	    ID[0] = path[0] = '\0';
            sprintf(ID, "%d", id);
	    strcat(strcat(strcat(strcat(path, TRAINSETPATH), fileName), ID), ".data");
	    remove(path);
	    path[0] = '\0';
	    strcat(strcat(strcat(strcat(path, TRAINSETPATH), fileName), ID), ".arff");
	    remove(path);
	    
	    //remove the testset files except the one with the maximum accuracy.
	    path[0] = '\0';
	    strcat(strcat(strcat(strcat(path, TESTSETPATH), fileName), ID), ".data");
	    remove(path);
	    path[0] = '\0';
	    strcat(strcat(strcat(strcat(path, TESTSETPATH), fileName), ID), ".arff");
	    
 	    //remove the ruleset files except the one with the maximum accuracy.
	    path[0] = '\0';
	    strcat(strcat(strcat(strcat(path, RULESETPATH), fileName), ID), ".data");
	    remove(path);
	}
    }


    return 0;
}
