#include <iostream>
#include "../header/MillerRabinTest.h"

using namespace std;

///INITIALIZATION
MillerRabinTest::MillerRabinTest()
{
   		mpz_init(MillerRabinTest::m);
    	mpz_init(MillerRabinTest::a);
    	mpz_init(MillerRabinTest::n);
    
}


///DECOMPOSITION OF M
void MillerRabinTest::decompose(mpz_t n_, mpz_t* m)
{
    mpz_t  k,r,n;
    mpz_init_set(n,n_);
    mpz_sub_ui(n,n,1);
    mpz_init_set_ui(k,0);
    mpz_init(r);
    mpz_tdiv_qr_ui(*m,r,n,2);
    while (mpz_cmp_d(r , 0) == 0 )
    {
    	
    	mpz_set(n,*m);
    	mpz_add_ui(k,k,1);
    	mpz_tdiv_qr_ui(*m,r,n,2);

    }
    mpz_set(*m,n);
}

///GENERATE RANDOM NUMBER
void MillerRabinTest::randomNumber(mpz_t a, mpz_t n)
{
	gmp_randstate_t state ; 
	gmp_randinit_mt(state);
	mpz_urandomm(a,state, n);
}

///PRIMALITY TEST
bool MillerRabinTest::PrimalityTest(mpz_t n, mpz_t m)
{	bool prime = false ;
	int k = 0;

	mpz_t a, two , one_positif ,one_negatif ,n_dec , zero;
	mpz_init(a);
	mpz_init(n_dec);
	mpz_init(zero);
	mpz_init_set_ui(two , 2);
	mpz_init_set_ui(one_positif , 1);
	mpz_init_set_ui(one_negatif , -1);
	mpz_init_set_ui(zero , 0);
	mpz_sub_ui(n_dec, n, 1);

	if (mpz_congruent_p(n,zero,two))
	{
		return false;
	}

	while ( k < 1 )
	{	
		//random

		randomNumber(a, n_dec);

		//test0
		mpz_t b0 ;
		mpz_init(b0);
		mpz_powm(b0, a, m, n);
		if ( mpz_congruent_p(b0, one_positif, n) > 0 || mpz_congruent_p(b0, one_negatif, n ) > 0 || mpz_congruent_p(b0, n_dec, n ) > 0 )
		{	
			prime = true ; 		

		}else{ // calcul des bk

			bool stop = false;
			int j = 0;
			while ((!prime && !stop ) && ( j < 1000 ) )
			{	
				mpz_powm(b0, b0, two ,n);
				
				if ( ( mpz_congruent_p(b0, n_dec, n ) > 0)  )
				{	
					prime = true ;
					stop = true ;

				}else if( mpz_congruent_p(b0, one_positif, n) > 0 )

				{	
					prime = false ; 
					stop = true ;
				}

				j++;
			}
		}
		
		k++;
	}
	return prime ;
}