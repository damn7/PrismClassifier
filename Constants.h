#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#define DATASETPATH "datasets/"
#define TESTSETPATH "testsets/"
#define TRAINSETPATH "trainsets/"
#define USAGE "Usage : java Split <fileName> <N> <P> <C> <A>  \nfileName = Fully qualified path of the file which has the complete data set\nN = number of samples and N > 0 \nP is the percentage of samples to be used for training. 1 <= P < 90 \nC = number of classes > 0  \nA = number of attributes (EXCEPT THE CLASS TYPE COLUMN) > 0 \nClass type should always be in the LAST column AND MUST be an integer in the range 0 to (C - 1)."

#endif // CONSTANTS_H_INCLUDED
