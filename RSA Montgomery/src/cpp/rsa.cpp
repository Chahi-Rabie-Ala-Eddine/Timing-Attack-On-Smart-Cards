#include <iostream>
#include <boost/algorithm/string.hpp>
#include <cstring>
#include <gmp.h>

#include "../header/rsa.h"


using namespace std ;

///
///RSA ENCRYPTION
///PARAMETERS MESSAGE,PRIVATE KEY D, N
/// RETURN STRING
///

string rsaEncrypt(mpz_t d, string m, mpz_t N )
{
	montgomery montSpace ; 

	mpz_t message ; 
	mpz_init(message) ;

	mpz_t cipher ; 
	mpz_init(cipher) ;

	/*STRING TO MPZ_T*/
	char* c = const_cast<char*>(m.c_str());
	mpz_set_str(message, c, 16);



	/*SQUARE AND MULTIPLY*/
	montSpace.initialise(message, d, N) ;
	montSpace.calculateR();
	montSpace.calculateRreverse();
	montSpace.calculateNreverse();
	montSpace.squareAndMultiply(cipher, message, d, N);

	
	
	/*MPZ_T TO STRING*/
	char * out = mpz_get_str(nullptr, 16, cipher);
	string output(out) ;

	boost::to_upper(output);
	return output ;

}

///
///RSA DECRYPTION
///PARAMETERS CIPHERED MESSAGE,PUBLIC KEY E, N
/// RETURN STRING
///

string rsaDecrypt(mpz_t e, string c, mpz_t N )
{
	montgomery montSpace ; 
	
	mpz_t message ; 
	mpz_init(message) ;

	mpz_t cipher ; 
	mpz_init(cipher) ;

	/*STRING TO MPZ_T*/
	char* ch = const_cast<char*>(c.c_str());
	mpz_set_str(cipher, ch, 16);

	/*SQUARE AND MULTIPLY*/
	montSpace.initialise(cipher, e, N) ;
	montSpace.calculateR();
	montSpace.calculateRreverse();
	montSpace.calculateNreverse();
	montSpace.squareAndMultiply(message, cipher, e, N);

	/*MPZ_T TO STRING*/
	char * out = mpz_get_str(nullptr, 16, message);
	string output(out) ;
	boost::to_upper(output);

	return output ;

}


///
///RSA SIGNATURE
///PARAMETERS MESSAGE,PRIVATE KEY D, N
/// RETURN STRING
///

string rsaSign(mpz_t d, string m, mpz_t N )
{
	return rsaEncrypt(d, m, N) ;
}


///
///RSA SIGNATURE VERIFICATION
///PARAMETERS MESSAGE, SIGNATURE, PRIVATE KEY D,PUBLIC KEY E, N
/// RETURN STRING
///
bool verifySig(string s, string m, mpz_t e, mpz_t N)
{
	string c = rsaDecrypt(e, s, N);

	boost::to_upper(m);
	boost::to_upper(c);
	if ( c == m )
		return true;
	else
		return false;
}