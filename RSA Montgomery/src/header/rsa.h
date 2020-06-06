#ifndef RSA_H
#define RSA_H

#include <string>
#include <gmp.h>

#include "rsaGenerator.h"
#include "montgomery.h"

using namespace std ; 

string rsaEncrypt(mpz_t d, string m, mpz_t N );
string rsaDecrypt(mpz_t e, string c, mpz_t N );
string rsaSign(mpz_t d, string m, mpz_t N );
bool verifySig(string s, string m, mpz_t e, mpz_t N);

#endif
