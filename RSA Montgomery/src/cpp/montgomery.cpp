#include "../header/montgomery.h"
#include <gmp.h>
#include <iostream>
#include <string>
#include <cstring>

using namespace std ; 




///
///INITIALISE MONTGOMERY PARAMETERS
///CALCUL OF R, R^-1 MOD N, -N^-1
///
void montgomery::initialise(mpz_t a,mpz_t b, mpz_t n){

	mpz_init(x);
	mpz_init(y);
	mpz_init(N);
	mpz_init(R);
	mpz_init(Rreverse);
	mpz_init(Nreverse);
	
	mpz_set(x, a);
	mpz_set(y, b);
	mpz_set(N, n);

}

///
///CALCUL OF R
///
void montgomery::calculateR(){
	mpz_t two;
	mpz_init(two);
	mpz_set_ui(two, 2);

	mpz_t r; 
	mpz_init(r);
	mpz_set_ui(r, 1);
	
	
	while (mpz_cmp(r, N) < 0){
		
		mpz_mul(r, r, two);	
	}
	
	mpz_set(R, r);

	mpz_clear(r);
}

///
///CALCUL OF R^-1
///
void montgomery::calculateRreverse(){

	mpz_invert(Rreverse, R, N);
}

///
///CALCUL OF -N^-1
///
void montgomery::calculateNreverse(){
	mpz_invert(Nreverse, N, R);
	mpz_sub(Nreverse, R, Nreverse);
}

///
///mONTGOMERY FORM OF A NUMBER "a" 
///
void montgomery::montgomeryForm(mpz_t res, mpz_t a){

	mpz_init(res);
	mpz_mul(res, a, R);
	mpz_mod(res, res, N);
	mpz_set(x, res);
	//gmp_printf(" Montgomery Form: %Zd\n", res);
}

///
///MONTGOMERY REVERSE FORM
///
void montgomery::reverseMontgomeryTransformation(mpz_t res , mpz_t T){
	mpz_t tempo;
	mpz_init(tempo);

	mpz_mul(tempo, T, Nreverse);
	mpz_mod(tempo, tempo, R);
	mpz_mul(tempo, tempo, N);
	mpz_add(tempo, tempo, T);
	mpz_div(tempo, tempo, R);
	mpz_set(res, tempo);
}

///
///EXTRA REDUCTION OF MONTGOMERY
///
void montgomery::reduce(mpz_t res, mpz_t a){


	if (mpz_cmp(a, N) > 0 )	
		mpz_sub(res, a, N);
		

}

///
///MONTGOMERY MULTIPLICATION
///
void montgomery::montgomeryMultiplacation(mpz_t res, mpz_t a, mpz_t b){
	
	mpz_t a_montgomry;
	mpz_init(a_montgomry);
	mpz_t b_montgomry;
	mpz_init(b_montgomry);
	mpz_t T;
	mpz_init(T);
	mpz_t tempo;
	mpz_init(tempo);

	/*montgomery form of a and b*/
	montgomeryForm(a_montgomry, a);
	montgomeryForm(b_montgomry, b);

	/*find T' = T.R^-1  = (T + (T.(-N^-1))mod R) . N ) / R mod N  */
	mpz_mul(T, a_montgomry, b_montgomry);
	mpz_mul(tempo, T, Nreverse);
	mpz_mod(tempo, tempo, R);
	mpz_mul(tempo, tempo, N);
	mpz_add(tempo, tempo, T);
	mpz_div(tempo, tempo, R);
	//mpz_mod(tempo, tempo, N);

	/*calculate the result of mult and reduce if necessary*/
	reduce(tempo, tempo);
	reverseMontgomeryTransformation(tempo, tempo);
	

	mpz_set(res, tempo);
	//gmp_printf(" Montgomery mult : %Zd\n", res);
	

}

///
/// SQUARE AND MULTIPLY
///
void montgomery::squareAndMultiply(mpz_t result, mpz_t base,  mpz_t exp,  mpz_t n){

	char* s ;
	
	mpz_t tempo;
	mpz_init(tempo);
	mpz_set(tempo, base);
	mpz_t tempo_;
	mpz_init(tempo_);
	mpz_set(tempo_, tempo);
	mpz_set(n, N);
	

	/*get the binary form of the exposant*/
	char * r = mpz_get_str(nullptr, 2, exp);
	int size = strlen(r);

	/*SQUARE and Multiply when bit == 1 and only square whan bit == 0 */
	for (int i = 1; i < size; ++i)
	{
		montgomeryMultiplacation(tempo_, tempo_, tempo_);
		if (r[i] == '1')
		{
			montgomeryMultiplacation(tempo_, tempo, tempo_); 
			
		}	
	}


	mpz_set(result, tempo_);
	
}