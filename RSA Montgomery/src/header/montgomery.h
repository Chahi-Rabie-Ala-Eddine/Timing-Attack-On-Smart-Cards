#ifndef MONTGOMERY_H
#define MONTGOMERY_H

#include <gmp.h>

class montgomery{

public:
	mpz_t R;
	mpz_t N;
	mpz_t x;
	mpz_t y;
	mpz_t Rreverse;
	mpz_t Nreverse;
	

	
	void initialise(mpz_t ,mpz_t ,mpz_t );
	void montgomeryForm(mpz_t, mpz_t) ;
	void montgomeryMultiplacation(mpz_t, mpz_t, mpz_t);
	void reverseMontgomeryTransformation(mpz_t , mpz_t);
	void reduce(mpz_t, mpz_t);
	void calculateR();
	void calculateRreverse();
	void calculateNreverse();
	void squareAndMultiply(mpz_t , mpz_t , mpz_t , mpz_t );



};

#endif
