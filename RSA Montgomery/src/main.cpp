#include <gmp.h>
#include <iostream>
#include "./header/rsaGenerator.h"
#include "./header/rsaPrinter.h"
#include "./header/rsa.h"


using namespace std ;




int main(int argc, char const *argv[])
{	
	/// 
	///	RSA PARAMETERS GENERATOR
	///
	string message ; 
	RSA_PARAMETERS x = rsaParametersGenerator(128);
	rsaParametersPrint(x);

	return 0;

}