#ifndef GENERATOR_H
#define GENERATOR_H

using namespace std;

#include "./_Constants.h"

/*Generation text method*/
string GenerateText(SIZE sampleTextLength);

/*Generation method*/
MESSAGES GenerateSample(SIZE sampleTextLength, int sampleSize);

/*Store sample*/
void WriteSample(string fileName, MESSAGES sample);

/*Load sample*/
MESSAGES ReadSample(string fileName);

#endif // GENERATOR_H