#ifndef RSAGENERATOR_H
#define RSAGENERATOR_H
#include <string>
#include <gmp.h>
#include <vector>

#include "key.h"
#include "des.h"
#include "tripledes.h"
#include "MillerRabinTest.h"
#include "colors.h"


using namespace std ;


struct RSA_PARAMETERS{

	mpz_t N ;
	mpz_t p ;
	mpz_t q ;
	mpz_t d ;
	mpz_t e ;
	mpz_t phiN ;

};




char randomBit(unsigned int space);
string gen64Bit();
void randomGeneration(mpz_t, int);
void randomPrimeGeneration(mpz_t p, int size);
RSA_PARAMETERS rsaParametersGenerator(int RSA);
void privateKeyD(mpz_t d, mpz_t e, mpz_t phi);
void CarmichaelTotient(mpz_t phi, mpz_t p, mpz_t q);
void publicKeyE(mpz_t e);

#endif
