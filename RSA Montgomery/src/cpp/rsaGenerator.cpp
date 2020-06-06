#include <random>
#include <iostream>
#include <cstring>

#include "../header/const.h"
#include "../header/rsaGenerator.h"
#include "../header/key.h"
#include "../header/des.h"
#include "../header/tripledes.h"
#include "../header/converter.h"

using namespace std;

vector<unsigned int> e_public(5) ;
vector<unsigned int> RSAModuleValues(8);



///
///	 initialise N size's for the verification of RSA module
///
void InitRsaModuleValues()
{	
	RSAModuleValues.push_back(32);
	RSAModuleValues.push_back(64);
	RSAModuleValues.push_back(128);
	RSAModuleValues.push_back(256);
	RSAModuleValues.push_back(512);
	RSAModuleValues.push_back(1024);
	RSAModuleValues.push_back(2048);
	RSAModuleValues.push_back(4096);
}

///
/// IT VERIFY IF THE SIZE OF THE RSA MODULE IS A POW OF TWO , BETWEEN 2⁵ AND 2¹¹
/// PARAMETERS : RSA SIZE
///	RETURN : boolean 
///
bool verifyRsaModule(int RSA)
{	
	InitRsaModuleValues();
	for (int i = 0; i < RSAModuleValues.size(); ++i)
	{
		if( RSA == RSAModuleValues[i])
			return true ;
	}
	return false ;
}


///
///GENERATE A RANDOM BIT
/// RETURN : CHAR
char  randomBit(unsigned int space)
{
	random_device random;  
	mt19937 fromRange(
		random()
	);  
	uniform_int_distribution<int> between(0,space-1);

	return  between(fromRange);
}

///
/// GENERATE 64 BITS
///RETURN : STRING
string gen64Bit()
{
	string Key = "" ;
	char r ;
	/*generate k*/
	for (int i = 0; i < 64 ; ++i)
	{
		r = randomBit(2) + 48 ;
		Key = Key + r ; 
		
			
	}
	return Key ;
	
}

/// GENERATE A RANDOM  NUMBER MPZ_T
void randomGeneration(mpz_t p, int size){

	string temp, k1, k2, k3 ;
	string blocks = "" ;
	string temp1 = "" ;
	
	/*GENERATE SEMI ALEATOIRE PARAMETERS FOR THE TRIPLE DES*/
	temp = gen64Bit();
	k1 = FromBinaryToHexadecimal(gen64Bit());
	k2 = FromBinaryToHexadecimal(gen64Bit());
	k3 = FromBinaryToHexadecimal(gen64Bit());
	temp1 = TripleDesEnryption(FromBinaryToHexadecimal(temp),k1, k2, k3);
	blocks = temp1 ;

	/*VERIFY IF SIZE IS < 64 BITS*/

	if(size == 8)
		blocks.resize(2);
	else if (size == 16)
		blocks.resize(4);
	else if (size == 32)
		blocks.resize(8);
	else
		{
			/*GENERATE 64 BITS*/

			int nb_bloc = size / DES_K_SIZE ;
			
				
			for (int i = 1; i < nb_bloc; ++i)
			{		
					temp1 = TripleDesEnryption(FromBinaryToHexadecimal(temp),k1, k2, k3);
					blocks += temp1 ;			
					temp = gen64Bit() ;		
			}
		}

	/*FORCE THE GENERATED NUMBER TO BE ODD */
	temp1 =  FromHexadecimalToBinary(blocks) ;
	temp1[0] = '1' ;
	temp1[temp1.size() - 1] = '1';
		
	/*SAVE THE RESULT*/
	char* gmp = const_cast<char*>(temp1.c_str());
	mpz_set_str(p, gmp, 2);	

}
///
///GENERATE A RANDOME PRIME NUMBER 
///
void randomPrimeGeneration(mpz_t p, int size)
{	
	/*GENERATE A RANDOM NUMBER*/
	randomGeneration(p, size);


	/*FIND A PRIME NUMBER FROM THE GENERATED ONE */
	while ( mpz_probab_prime_p(p, 1000 ) == 0 )
		mpz_add_ui(p, p, 2) ;
}

///
/// CHOOSE E VALUE 
///
void init_e()
{
	e_public[0] = 3 ;
	e_public[1] = 5 ;
	e_public[2] = 17 ;
	e_public[3] = 257 ;
	e_public[4] = 65537 ;
}

///
//GENERATE PUBLIC KEY E FOR RSA
///
void publicKeyE(mpz_t e)
{	
	init_e();
	int randomIndex = (int) randomBit(5) ;
	mpz_set_ui(e, e_public[randomIndex] );
}

/// 
///Carmichael’s totient function ϕ(n)
///
void CarmichaelTotient(mpz_t phi, mpz_t p, mpz_t q)
{	
	mpz_t p_;
	mpz_init(p_);
	mpz_t q_; 
	mpz_init(q_);

	
	mpz_sub_ui(p_, p, 1);
	mpz_sub_ui(q_, q, 1);

	mpz_mul(phi, p_, q_);
}
///
///CALCULATE THE PRIVATE KEY
///
void privateKeyD(mpz_t d, mpz_t e, mpz_t phi)
{	
	mpz_invert(d, e, phi);
}
///
///RSA GENERATOR
///
RSA_PARAMETERS rsaParametersGenerator(int RSA)
{
	RSA_PARAMETERS rsa;
	int size_N = RSA ;
	int sizeP = 0 ;
	int sizeQ = 0 ;
	mpz_t res ; 
	mpz_init(res);
	mpz_t pgcd ; 
	mpz_init(pgcd);
	mpz_t abs ; 
	mpz_init(abs);
	int sizeOfN ;

	/*INIT*/
	mpz_init(rsa.N) ;
	mpz_init(rsa.p) ;
	mpz_init(rsa.q) ;
	mpz_init(rsa.e) ;
	mpz_init(rsa.d) ;
	mpz_init(rsa.phiN) ;

	/*verify the size of RSA module*/

	if ( !verifyRsaModule(RSA) )
	{
		cout << RED << "ERROR ! VERIFY YOUR RSA KEY'S SIZE" << WHITE << endl  ; 
		exit(0) ;
	}


	do
	{
		/*GENERATE PUBLIC KEY E*/
		publicKeyE(rsa.e);

		do
		{
			/*GENERATE P AND Q */
			sizeP = size_N / 2 ;
			sizeQ = sizeP  ;

			/*Generate P A RANDOM PRIME NUMBER*/
			do{
				randomPrimeGeneration(rsa.p, sizeP);
				mpz_mod(res, rsa.p, rsa.e);

			}while( mpz_cmp_ui(res, 1) == 0 );
		
	
			/*Generate Q A RANDOM PRIME NUMBER*/
			do{
				randomPrimeGeneration(rsa.q, sizeQ);
				mpz_mod(res, rsa.q, rsa.e);
				mpz_sub(abs, rsa.p, rsa.q);
				mpz_abs(abs, abs);

			}while( mpz_cmp_ui(res, 1) == 0 && mpz_cmp(res, rsa.e) > 0 );
	
			/*CALCULATE N*/
			mpz_mul(rsa.N, rsa.p, rsa.q);

			sizeOfN = mpz_sizeinbase(rsa.N, 2);

		}while (sizeOfN != size_N ) ;

		/*	CALCULATE PHI N */
		CarmichaelTotient(rsa.phiN, rsa.p, rsa.q);

		mpz_gcd(pgcd, rsa.phiN, rsa.e) ;

	}while (mpz_cmp_ui(pgcd, 1) != 0 );

	/*Calculate the private key*/
	privateKeyD(rsa.d, rsa.e, rsa.phiN);

	mpz_mul( pgcd, rsa.e, rsa.d);
	mpz_mod(pgcd, pgcd, rsa.phiN);

	return rsa ;

}
