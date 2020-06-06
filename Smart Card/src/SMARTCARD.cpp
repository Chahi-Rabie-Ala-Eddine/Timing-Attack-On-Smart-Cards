#include <iostream>
#include <string.h>
#include <algorithm>

#include "./header/_Constants.h"
#include "./header/_Signature.h"
#include "./header/_BIGNUM.h"

using namespace std;

int main(int argc, char const *argv[])
{
	if(argc > 1)
		ComputeRSASignature(d_, SetValue((string)argv[1]), n_);

	Free({n_, d_});

	return 0;
}