#include <iostream>

#include "../header/_Constants.h"
#include "../header/_BIGNUM.h"

/*SignMessage*/
void ComputeRSASignature(BIG d, BIG message, BIG mod)
{
	
	cout << GetValue(MontgomeryLTRSAM(message, d, mod));
}

