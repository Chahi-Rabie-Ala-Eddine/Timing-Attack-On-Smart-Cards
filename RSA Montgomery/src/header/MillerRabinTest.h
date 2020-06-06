#ifndef MILLERRABINTEST_H
#define MILLERRABINTEST_H

#include <gmp.h>

class MillerRabinTest
{
    public:
    	mpz_t m;
    	mpz_t a;
    	mpz_t n;

        MillerRabinTest();
        MillerRabinTest(mpz_t a);
        /** it decompose n-1 to m*2^k  */
        void decompose(mpz_t n, mpz_t* m);
        /* return an random number between 2 and n */ 
        void randomNumber(mpz_t a,mpz_t n);
        /* it test if n is prime */
        bool PrimalityTest(mpz_t n, mpz_t m);



};

#endif // MILLERRABINTEST_H
