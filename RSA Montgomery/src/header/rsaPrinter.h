#include "../header/rsa.h"
#include "../header/rsaGenerator.h"


void rsaParametersPrint(RSA_PARAMETERS x) ; 
string rsaEncryptionPrint(mpz_t, string, mpz_t) ;
string rsaDecryptionPrint(mpz_t, string, mpz_t) ;
string rsaSignPrint(mpz_t, string, mpz_t) ;
void rsaVerificationSign(string s, string m, mpz_t e, mpz_t N) ; 
void rsaPrintAll(RSA_PARAMETERS x, string m) ;