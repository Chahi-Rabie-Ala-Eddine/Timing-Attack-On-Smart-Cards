#include <iostream>
#include <random>
#include <fstream>

#include "../header/_Constants.h"
#include "../header/_Generator.h"

using namespace std;

/*Generate random text*/
string GenerateText(SIZE sampleTextLength)
{
    string hexadecimal;
    static auto& hexForm = "0123456789ABCDEF";

    thread_local static mt19937 generated
    {
    	random_device
    	{

    	}()
    };

    thread_local static uniform_int_distribution<SIZE> pick(0, sizeof(hexForm) - 2);

    hexadecimal.reserve(sampleTextLength);

    while(--sampleTextLength)
        hexadecimal += hexForm[pick(generated)];

    return (string)hexadecimal;
}

/*Generation method*/
MESSAGES GenerateSample(SIZE sampleTextLength, int sampleSize)
{
    MESSAGES sample;

    for(int i = 0; i < (int)sampleSize; i++)
        sample.push_back(GenerateText(sampleTextLength));
    
    return sample;
}

/*Store sample*/
void WriteSample(string fileName, MESSAGES sample)
{
	if(sample.size() < _SIZE)
	{
		printf("There is an error : [size of sample is < than setsSize]\n");
		exit(EXIT_FAILURE);
	}

	else
	{
		ofstream Samplefile(fileName + ".smp");

		if(Samplefile.is_open())
		{
			for(int i = 0; i < _SIZE; ++i)
				Samplefile << sample[i] << "\n";

			Samplefile.close();

			printf("Writing succes !\n");
		}

		else
		{
			printf("Cannot write file !\n");
			exit(EXIT_FAILURE);
		}
	}
}

/*Load sample*/
MESSAGES ReadSample(string fileName)
{
	MESSAGES sample;
	char* line = NULL;
	size_t length = 0;

	FILE* file = fopen(const_cast<char*>((fileName + ".smp").c_str()), "r");

	if(file == NULL)
		exit(EXIT_FAILURE);

	while ((getline(&line, &length, file)) != -1) 
	{
		string str(line);
		sample.push_back(str.substr(0, str.size()-1)); 
	}
	
	fclose(file);
	
	if(line)
		free(line);

	return sample;
}
