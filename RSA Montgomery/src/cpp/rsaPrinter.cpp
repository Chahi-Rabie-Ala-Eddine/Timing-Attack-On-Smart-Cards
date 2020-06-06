#include <gmp.h>
#include <boost/algorithm/string.hpp>

#include "../header/colors.h"
#include "../header/rsaPrinter.h"

///
/// THIS METHOD PRINT THE PARAMETERS OF rsa
///PARAMETERS : RSA_PARAMETERS X
///
void rsaParametersPrint(RSA_PARAMETERS x) 
{	

	
	char* e = mpz_get_str(nullptr, 16, x.e );
	char* d = mpz_get_str(nullptr, 16, x.d );
	char* q = mpz_get_str(nullptr, 16, x.q );
	char* p = mpz_get_str(nullptr, 16, x.p );
	char* N = mpz_get_str(nullptr, 16, x.N );
	char* phiN = mpz_get_str(nullptr, 16, x.phiN );

	boost::to_upper(e);
	boost::to_upper(d);
	boost::to_upper(q);
	boost::to_upper(p);
	boost::to_upper(N);
	boost::to_upper(phiN);

	cout << endl << YELLOW << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl ; 

	cout << CYAN << "RSA PARAMETERS GENERATION : " << WHITE <<  endl << endl ;

	cout << "RSA PUBLIC KEY e : " << e << endl ;
	cout << "RSA PRIVATE KEY d : " << d << endl ;
	cout << "RSA PRIVATE KEY Q : " << q << endl ;
	cout << "RSA PRIVATE KEY P : " << p << endl ;
	cout << "RSA MODULE N : " << N << endl ; 
	cout << "RSA CARMICHAEL TOTIENT : " << phiN << endl ;


	cout << endl << YELLOW << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << WHITE << endl ; 
}

///
/// ENCRYPT A MESSAGE WITH RSA 
///PARAMETERS : STRING MESSAGE, MPZ_T N AND THE KEY D (MPZ_T)
///
string rsaEncryptionPrint(mpz_t d, string m, mpz_t N)
{	


	string cipher = rsaEncrypt(d, m, N );

	cout << endl << " RSA Encryption : { "  << m << " } ---> { " << cipher << " } " << endl <<endl ;

	cout << endl << YELLOW << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << WHITE << endl ;

	return cipher ;

}

///
/// DECCRYPT A CIPHERED WITH RSA 
///PARAMETERS : STRING MESSAGE, MPZ_T N AND THE KEY E (MPZ_T)

string rsaDecryptionPrint(mpz_t e, string c, mpz_t N)
{	


	string message = rsaDecrypt(e, c, N);

	cout << endl << "RSA Decryption : { "  << c << " } ---> { "<< message << " } " << endl <<endl ;

	cout << endl << YELLOW << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << WHITE << endl ;

	return message ;

}
///
/// PRINT A RSA SIGNATURE
///PARAMETERS : STRING MESSAGE, MPZ_T N AND THE KEY D (MPZ_T)
///

string rsaSignPrint(mpz_t d, string m, mpz_t N)
{

	string cipher = rsaSign(d, m, N );

	cout << endl << "RSA SIGNATURE : { "  << m << " } ---> { "<< cipher << " } " << endl <<endl ;

	cout << endl << YELLOW << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << WHITE << endl ;

	return cipher ;
}
///
///WE VERIFY IF THE SIGNATURE IS CORRECT
///PARAMETERS : STRING MESSAGE,STRING SIGNAURE, MPZ_T N AND THE KEY E (MPZ_T)
///
void rsaVerificationSign(string s, string m, mpz_t e, mpz_t N) 
{
	if (verifySig( s, m, e, N) )
		cout << GREEN << "SIGNATURE VERIFIED " << YELLOW << endl << endl<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << WHITE << endl ;
	else
		cout << RED << "SIGNATURE FAILED " << YELLOW << endl << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << WHITE << endl ;

}

///
///PRINT ALL FROM GENERATION TO VERIFICATION OF SIGNATURE
///
void rsaPrintAll(RSA_PARAMETERS x, string m)
{

	rsaParametersPrint( x ) ;
	string c = rsaEncryptionPrint( x.d, m, x.N ) ;
	string t = rsaDecryptionPrint( x.e, c, x.N ) ;
	string s = rsaSignPrint( x.d, m, x.N ) ;
	rsaVerificationSign(s, m, x.e, x.N) ;
} 