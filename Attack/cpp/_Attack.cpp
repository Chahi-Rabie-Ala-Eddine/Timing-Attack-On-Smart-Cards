#include <iostream>
#include <math.h>
#include <algorithm>
#include<stdio.h> 
#include<stdlib.h> 
#include<sys/wait.h> 
#include<unistd.h> 

#include "../header/_BIGNUM.h"
#include "../header/_Constants.h"
#include "../header/_Attack.h"
#include "../header/_Generator.h"
#include "../header/_Statistics.h"
#include "../header/_System.h"

unsigned long int Medians[4];

/*Generate R and R-1*/
BIGS ComputeFactors(BIG mod)
{
	BIGS bigs {Equal(BigExponentiation(_2, SetValue(to_string(GetDecimalSize(mod))))), Inverse(Equal(BigExponentiation(_2, SetValue(to_string(GetDecimalSize(mod))))), mod)};

	return bigs;
}

/*Montgomery Multiplication*/
BIG MMAttack(BIG firstNum, BIG secondNum, BIG mod, BIG R, BIG  _R)
{
	BIG MultMont = operator*(ModularMultiplication(firstNum, R, mod), ModularMultiplication(secondNum, R, mod));
	BIG result = operator/(operator+(MultMont, operator*(ModularMultiplication(MultMont, operator-(R, Inverse(mod, R)), R), mod)), R);

	if(operator>(result, mod))
		result = Equal(operator-(result, mod));

	return ModularMultiplication(result, _R, mod);
}

/*Montgomery left to right fast exponentiation*/
BIG MSMAttack(BIG base, BIG exp, BIG mod, BIG R, BIG  _R)
{
	BIG result = Equal(base);
	string binaryExp = GetBinaryValue(exp);
	unsigned int size = GetBinarySize(exp);

	for(int i = 1; i < size; i++)
	{
		result = MMAttack(result, result, mod, R, _R);

		if(binaryExp[i] == '1')
			result = MMAttack(result, base, mod, R, _R);
	}

	return result;
}

/*Criteron to divide sample on sets*/
bool Criteron(BIG firstNum, BIG secondNum, BIG mod, BIG R, BIG _R)
{
	BIG MultMont = operator*(ModularMultiplication(firstNum, R, mod), ModularMultiplication(secondNum, R, mod));
	BIG intermediary = operator/(operator+(MultMont, operator*(ModularMultiplication(MultMont, operator-(R, Inverse(mod, R)), R), mod)), R);

	if(operator>(intermediary, mod))
		return true;

	return false;
}

/*Generate Universe related to Criteron*/
SPECIMEN GenerateUniverse(MESSAGES sample, BIG PartKey, BIG mod, BIG R, BIG _R)
{
	MESSAGES s1, s2, s3, s4;

	for(int i = 0; i < _SIZE; ++i)
	{
		BIG M = SetValue(sample[i]);
		BIG Mtemp = MontgomerySquare(MontgomeryLTRSAM(M, PartKey, mod), mod);
		BIG MtempxM = MontgomeryMultiplication(Mtemp, M, mod);

		if(Criteron(MtempxM, MtempxM, mod, R, _R))
			s1.push_back(sample[i]);
		
		else
			s2.push_back(sample[i]);

		if(Criteron(Mtemp, Mtemp, mod, R, _R))
			s3.push_back(sample[i]);

		else
			s4.push_back(sample[i]);

		Free({M, Mtemp, MtempxM});
	}

	SPECIMEN sets = {s1, s2, s3, s4};

    for(auto &element : sets)
        element.resize(min_element(begin(sets), end(sets), []( const auto &v1, const auto &v2 ){return v1.size() < v2.size();})->size());

	return sets;
}

/*Compute square and multiply Montgomery median time*/
double MedianMSQTime(MESSAGES sample)
{
	SIZE size = sample.size();
	clock_t start, end;
	double time;
	TIMES times;

	for(int i = 0; i < size; i++)
	{
		start = clock();
			GetSmartCardSignature(sample[i]);
		end = clock();

		time = double(end - start) / CPU_T;
		times.push_back(time);
	}

	return ComputeMedianTimes(times) / ms;
}

/*Decide which criteron is logical*/
void DefineLogicalCriteron(SPECIMEN specimen)
{
	for(int i = 0; i < 4; i++)
		Medians[i] = MedianMSQTime(specimen[i]);
}

/*Compute Medians*/
char DetermineBit()
{

	return ((abs((int)Medians[0] - (int)Medians[1])) > (abs((int)Medians[2] - (int)Medians[3]))) ? '1' : '0';
}

/*Clear previous medians*/
void ClearMemory()
{

	Medians[0] = 0; Medians[1] = 0; Medians[2] = 0; Medians[3] = 0;
}

/*RSA timing attack*/
string Attack(BIG n)
{
	BIG r = ComputeFactors(n)[0];
	BIG _r = ComputeFactors(n)[1];
	BIG KeyPart = _1;
	MESSAGES messages = GenerateSample(_LENGTH, _SIZE);
	
	for(int i = 0; i < (int)GetBinarySize(_512) ; i++)
	{
		SPECIMEN specimen = GenerateUniverse(messages, KeyPart, n, r, _r);
		DefineLogicalCriteron(specimen);
		KeyPart = SetBinaryValue((string)(GetBinaryValue(KeyPart) + DetermineBit()));
		ClearMemory();
	}

	return GetBinaryValue(KeyPart);
}

/*Get last bit and Check the result key using the smartcard*/
string GetFullKey(BIG d, BIG N)
{
	if(GetValue(MontgomeryLTRSAM(SetValue("1BCD66"), SetBinaryValue(GetValue(d) + '1'), N)) == GetSmartCardSignature("1BCD66"))
		return (string)(GetValue(d) + '1');

	if(GetValue(MontgomeryLTRSAM(SetValue("1BCD66"), SetBinaryValue(GetValue(d) + '0'), N)) == GetSmartCardSignature("1BCD66"))
		return (string)(GetValue(d) + '0');

	return "Invalid key !\n";
}

/*Main method*/
void _Timing_Attack(BIG N)
{
	cout << "TIMING ATTACK RUNNING...\n";
	GetFullKey(SetValue(Attack(N)), N);
}
