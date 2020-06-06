#include <iostream>

#include "../header/_BIGNUM.h"
#include "../header/_Constants.h"

using namespace std;

//								//
//	       Initialisation      	//
//								//

/*Set Big number value*/
BIG SetValue(string value)
{
	BIG number;
	mpz_init(number.Number);
	mpz_set_str(number.Number, const_cast<char*>(value.c_str()), 16);

	return number;
}

void SetValue(BIG number, string value)
{
	mpz_init(number.Number);
	mpz_set_str(number.Number, const_cast<char*>(value.c_str()), 16);
}

/*Set Big number whit binary value*/
BIG SetBinaryValue(string value)
{
	BIG number;
	mpz_init(number.Number);
	mpz_set_str(number.Number, const_cast<char*>(value.c_str()), 2);

	return number;
}

void SetBinaryValue(BIG number, string value)
{
	mpz_init(number.Number);
	mpz_set_str(number.Number, const_cast<char*>(value.c_str()), 2);
}

//								//
//	       Informations      	//
//								//

/*Get Big number hexadeciaml size*/
unsigned int GetSize(BIG const& number)
{

	return static_cast<int>(mpz_sizeinbase(number.Number, 16));
}

/*Get Big number binary size*/
unsigned int GetBinarySize(BIG const& number)
{

	return static_cast<int>(mpz_sizeinbase(number.Number, 2));
}

unsigned int GetDecimalSize(BIG const& number)
{

	return static_cast<int>(mpz_sizeinbase(number.Number, 10));
}

/*Get Big number value*/
string GetValue(BIG const& number)
{
	char* temp = NULL;
	string value(mpz_get_str(temp, 16, number.Number));
	for (auto & character: value) character = toupper(character);
    
    return (string)value;
}

/*Get Big number value*/
string GetBinaryValue(BIG const& number)
{
	char* temp = NULL;
	string value(mpz_get_str(temp, 2, number.Number));
    
    return (string)value;
}
//								//
//	       	   Storage      	//
//								//

/*Initialise a Big number value using another one*/
BIG Equal(BIG Number)
{
	BIG result = SetValue(GetValue(Number));

	return result;
}

//								//
//	     	 Comparaison   		//
//								//

/*Check if the two numbers are equals*/
bool operator==(BIG const& firstNum, BIG const& secondNum)
{

	return (mpz_cmp(firstNum.Number, secondNum.Number)  == 0) ? true : false;
}

/*Check if the two numbers are different*/
bool operator!=(BIG const& firstNum, BIG const& secondNum)
{
	
	return (mpz_cmp(firstNum.Number, secondNum.Number) != 0) ? true : false;
}

/*Check if the first number is greater than the second*/
bool operator>(BIG const& firstNum, BIG const& secondNum)
{

	return (mpz_cmp(firstNum.Number, secondNum.Number) > 0) ? true : false;
}

/*Check if the first number is smaller than the second*/
bool operator<(BIG const& firstNum, BIG const& secondNum)
{

	return (mpz_cmp(firstNum.Number, secondNum.Number) < 0) ? true : false;
}

/*Check if the number is odd*/
bool IsOdd(BIG const& Num)
{

	return (mpz_odd_p (Num.Number) != 0) ? true : false;
}

/*Check if the number is even*/
bool IsEven(BIG const& Num)
{

	return (mpz_even_p (Num.Number) != 0) ? true : false;
}

//								//
//	      	Arithmetic 			//
//								//

/*Addition*/
BIG operator+(BIG const& firstNum, BIG const& secondNum)
{
	BIG result;
	mpz_init(result.Number);
	mpz_add (result.Number , firstNum.Number, secondNum.Number);

	return result;
}

/*Substraction*/
BIG operator-(BIG const& firstNum, BIG const& secondNum)
{
	BIG result;
	mpz_init(result.Number);
	mpz_sub (result.Number , firstNum.Number, secondNum.Number);

	return result;
}

/*Multiplication*/
BIG operator*(BIG const& firstNum, BIG const& secondNum)
{
	BIG result;
	mpz_init(result.Number);
	mpz_mul (result.Number , firstNum.Number, secondNum.Number);

	return result;
}

/*Division*/
BIG operator/(BIG const& firstNum, BIG const& secondNum)
{
	BIG result;
	mpz_init(result.Number);
	mpz_div(result.Number , firstNum.Number, secondNum.Number);

	return result;
}

/*Incrementation*/
void Increment(BIG Num)
{

	mpz_add_ui (Num.Number, Num.Number, 1);
}

/*Decrementation*/
void Decrement(BIG Num)
{
	
	mpz_sub_ui(Num.Number, Num.Number, 1);
}

/*Square*/
BIG Square(BIG const& Num)
{

	return operator*(Num, Num);
}

/*Simple exponentiation : mpz_t power unsigned long*/
BIG SimpleExponentiation(BIG const& base, unsigned long int exponent)
{
	BIG result;
	mpz_init(result.Number);
	mpz_pow_ui (result.Number, base.Number, exponent);

	return result;
}

/*Big exponentiation : mpz_t power mpz_t*/
BIG BigExponentiation(BIG const& base, BIG const& exponent)
{
	BIG result = Equal(base);
	BIG exp = Equal(exponent);

	do{
		result = operator*(result, base);
		Decrement(exp);
	}while(operator>(exp, _1));

	return result;
}

//								//
//	     Low level operations 	//
//								//

/*Left shift*/
void LeftShift(BIG Num, unsigned long int bitsShifted)
{

	mpz_mul_2exp(Num.Number , Num.Number, bitsShifted);
}

/*Right shift*/
void RightShift(BIG Num, unsigned long int bitsShifted)
{

	mpz_div_2exp(Num.Number , Num.Number, bitsShifted);
}

//								//
//	     Modular Arithmetic 	//
//								//

/*Compute module*/
BIG Mod(BIG const& Num, BIG const& mod)
{
	BIG result;
	mpz_init(result.Number);
	mpz_mod(result.Number, Num.Number, mod.Number);

	return result;
}

/*Compute inverse*/
BIG Inverse(BIG const& Num, BIG const& mod)
{
	BIG result;
	mpz_init(result.Number);
	int func = mpz_invert (result.Number, Num.Number, mod.Number);

	if(func == 0)
		throw invalid_argument("There is no invert");

	return result;
}

/*Modular multiplication*/
BIG ModularMultiplication(BIG const& firstNum, BIG const& secondNum, BIG const& mod)
{

	return Mod(operator*(firstNum, secondNum), mod);
}

/*Modular exponentiation*/
BIG ModularExponentiation(BIG const& Num, BIG const& exp, BIG const& mod)
{
	BIG result;
	mpz_init(result.Number);
	mpz_powm (result.Number, Num.Number, exp.Number, mod.Number);

	return result;
}

//								//
//	     	Cryptography  		//
//								//

/*Normal left to right fast expnonentiation*/
BIG NormalLTRSAM(BIG const& base, BIG const& exp, BIG const& mod)
{
	BIG _base = Equal(base);
	string binaryExp = GetBinaryValue(exp);
	unsigned int size = GetBinarySize(exp);

	for(int i = 1; i < size; i++)
	{
		_base = Equal(Square(_base));

		if(binaryExp[i] == '1')
			_base = Equal(operator*(_base, base));
	}
	
	return Mod(_base,mod);
}

/*Montgomery Multiplication*/
BIG MontgomeryMultiplication(BIG const& firstNum, BIG const& secondNum, BIG const& mod)
{
	if(IsEven(mod))
		throw invalid_argument("Modulo must be odd [Z/nZ SYSTEM] !\n");

	BIG R = Equal(BigExponentiation(_2, SetValue(to_string(GetDecimalSize(mod)))));
	BIG _R = Inverse(R, mod);
	BIG MultMont = operator*(ModularMultiplication(firstNum, R, mod), ModularMultiplication(secondNum, R, mod));
	BIG intermediary = operator/(operator+(MultMont, operator*(ModularMultiplication(MultMont, operator-(R, Inverse(mod, R)), R), mod)), R);

	mpz_clear(R.Number);
	mpz_clear(MultMont.Number);

	if(operator>(intermediary, mod))
	{
		return ModularMultiplication(operator-(intermediary, mod), _R, mod);
	}

	return ModularMultiplication(intermediary, _R, mod);
}

/*Montgomery Square*/
BIG MontgomerySquare(BIG const& Num, BIG const& mod)
{

	return MontgomeryMultiplication(Num, Num, mod);
}

/*Montgomery left to right fast exponentiation using shift*/
BIG MontgomeryLTRSAM(BIG const& base, BIG const& exp, BIG const& mod)
{
	BIG result = Equal(base);
	string binaryExp = GetBinaryValue(exp);
	unsigned int size = GetBinarySize(exp);

	for(int i = 1; i < size; i++)
	{
		result = Equal(MontgomerySquare(result, mod));

		if(binaryExp[i] == '1')
			result = Equal(MontgomeryMultiplication(result, base, mod));
	}
	
	return result;
}

/*Print Big number value*/
void PrintBigNumber(BIG const& number)
{

	gmp_printf("%ZX\n",number.Number);
}

//								//
//	      Memory Managment  	//
//								//

/*Free Big number memory*/
void Free(BIGS bigs)
{
	for(auto &big : bigs)
		mpz_clear(big.Number);
}


// Other //

bool Coprime(BIG a, BIG b)
{
	mpz_t test;
	mpz_init(test);
	mpz_gcd (test, a.Number, b.Number);

	char* temp = NULL;
	string value(mpz_get_str(temp, 16, test));

	if(value == "1")
	{
		mpz_clear(test);
		return true;
	}

	mpz_clear(test);
	
	return false;
}
