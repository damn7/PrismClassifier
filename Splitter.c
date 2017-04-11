#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Constants.h"
void split(char *fileName, int instances, int percentage, int classes, int attributes)
{

	char temp[1000], substr[1000]; // fix this value of 1000 appropriately if your file has very large lines
	char headerText[5000];  // fix this number 5000 appropriately if too many attributes
    char datasetName[100];

    //get the dataset name for proper naming of the files created.
    char *start = strrchr(fileName, '/') + 1;
    char *end = strchr(fileName, '.');
    int datasetNameLength = (int)(end - start);
    memcpy(datasetName, start, datasetNameLength);
    datasetName[datasetNameLength] = '\0';
    printf("%s\n", datasetName);

	int* count;
	int* trainingIndices;
	int* indices;
	FILE** tempFiles;

	int N = 0, P = 0, C = 0, A = 0;
	int i, j, k, m, t, lastIndex, found;

	FILE* dataFile;
	FILE* training1;
	FILE* training2;
	FILE* testing1;
	FILE* testing2;

	N = instances;
	P = percentage;
	C = classes;
	A = attributes;

	// error checks
	if(N <= 0 || P < 1 || P > 90 || C < 1 || A < 1)
	{
		printf(USAGE);
        exit(-1);
	}

	dataFile = fopen(fileName, "r");

	// file existence check
	if(dataFile == NULL)
	{
		printf("Could not read the file %s", fileName);
		exit(-1);
	}

	// array initializations
	//count = new int[C];
	count = (int *)malloc(C*sizeof(int));
	//tempFiles = new FILE*[C];
    tempFiles = (FILE **)malloc(C*sizeof(FILE *));

	for(i = 0; i < C; i++)
	{
		count[i] = 0; // count of items corresponding to class 'i'
		//itoa(i, substr, 10);
		sprintf(substr, "%d", i);

		// create temp file to store all items for class 'i'
		tempFiles[i] = fopen(substr, "w");
	}

	// read N lines from input data file
	for(i = 0; i < N; i++)
	{
		// read lines from file and count number of occurences of each class
		// simultaneously generate separate temp files with data of each class
	    fscanf(dataFile, "%s", temp);

		// get last index of comma character
		k = strlen(temp);
		lastIndex = -1;
		for(j = 0; j < k; j++)
		{
		    if(temp[j] == ',')
				lastIndex = j;
		}

		// construct substring
		for(j = lastIndex + 1; j < k; j++)
		{
			substr[j - lastIndex - 1] = temp[j];
		}
		substr[j - lastIndex - 1] = '\0';

		// substr was the class type - increment corresponding counters
		k = atoi(substr);
		count[k]++;

		// classify the values by-class in separate files
		// NOTE : To ensure compiler portability across systems,
		// we are NOT USING vectors from STL - using temp files instead
		fprintf(tempFiles[k], "%s\n", temp);
	}

	// close the main data file and all temp files
	fclose(dataFile);
	for(i = 0; i < C; i++)
	{
		printf("Class %d : %d\n", i, count[i]);
		fclose(tempFiles[i]);
	}

	// Create header text for ARFF
	strcat(headerText, "@RELATION Sample\n");
	for(i = 0; i < A; i++)
	{
		sprintf(substr, "@ATTRIBUTE a%d  real\n", (i + 1));
		strcat(headerText, substr);
	}

	strcat(headerText, "\n@ATTRIBUTE class {");
	for(i = 0; i < C; i++)
	{
		sprintf(substr, "%d", i);
		strcat(headerText, substr);
		if(i < C - 1)
			strcat(headerText, ", ");
		else
			strcat(headerText, "}");
	}
	strcat(headerText,"\n\n@DATA\n");

	printf("Header over\n");

	// now read all classified files - shuffle them and then put the data in appropriate training and test files
	char trainingDataPath[100];
	strcat(strcat(strcat(trainingDataPath, TRAINSETPATH), datasetName), ".data");
	printf("%s\n", trainingDataPath);
	training1 = fopen(trainingDataPath, "w");

	char trainingArffPath[100];
	strcat(strcat(strcat(trainingArffPath, TRAINSETPATH), datasetName), ".arff");
	training2 = fopen(trainingArffPath, "w");

	char testingDataPath[100];
	strcat(strcat(strcat(testingDataPath, TESTSETPATH), datasetName), ".data");
	testing1 = fopen(testingDataPath, "w");

	char testingArffPath[100];
	strcat(strcat(strcat(testingArffPath, TESTSETPATH), datasetName), ".arff");
	testing2 = fopen(testingArffPath, "w");

	// add header in arff files
	fprintf(training2, headerText);
	fprintf(testing2, headerText);

	// randomize the data from each of the files and put them in training file
	for(i = 0; i < C; i++)
	{
		if(count[i] > 0)  // ignore if no data from this class
		{
			// create list of indices in the temp file
			//indices = new int[count[i]];
            indices = (int *)malloc(count[i]*sizeof(int));
			for(j = 0; j < count[i]; j++)
				indices[j] = j;

			// shuffle the indices
			for(j = 0; j < count[i]; j++)
			{
				k = rand() % count[i];
				m = rand() % count[i];
				if(k != m)
				{
					t = indices[k];
					indices[k] = indices[m];
					indices[m] = t;
				}
			}

			t = (count[i] * P)/100; // number of samples to be picked up for training
			if((count[i] * P)%100 != 0)
				++t;  // effectively a ceil operation

			//trainingIndices = new int[t];
			trainingIndices = (int *)malloc(t*sizeof(int));

			for(j = 0; j < t; j++)
			{
				trainingIndices[j] = indices[j];
			}

			// open the temp file
			//itoa(i, substr, 10);
			sprintf(substr, "%d", i);
			tempFiles[i] = fopen(substr, "r");

			// read data from temp file and if current row index is
			// present in trainingIndices - the write to training files
			// else write to test files
			for(j = 0 ; j < count[i]; j++)
			{
				// read a row from temp file containing data from class i
				fscanf(tempFiles[i], "%s", temp);

				found = 0;

				// search the current index in trainingIndices
				for(k = 0; k < t; k++)
				{
					if(trainingIndices[k] == j)
					{
						// current index j is found in trainingIndices
						// put current row in training files
						found = 1;
						fprintf(training1, "%s\n", temp);
						fprintf(training2, "%s\n", temp);
						break;
					}
				}

				if(found == 0)
				{
					// current index j was not in trainingIndices
					// put current row in testing files
					fprintf(testing1, "%s\n", temp);
					fprintf(testing2, "%s\n", temp);
				}
			}

			fclose(tempFiles[i]);
		}
	}

	fclose(training1);
	fclose(training2);
	fclose(testing1);
	fclose(testing2);

	// delete all temporary files
	for(i = 0; i < C; i++)
	{
		sprintf(temp, "%d", i);
		remove(temp);
	}

	return 0;
}
