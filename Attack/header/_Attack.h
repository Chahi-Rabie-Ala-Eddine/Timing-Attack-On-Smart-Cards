#ifndef ATTACK_H
#define ATTACK_H

/*Generate R and _R*/
BIGS ComputeFactors(BIG mod);

/*Montgomery multiplication reimplemnted for the attack*/
BIG MMAttack(BIG firstNum, BIG secondNum, BIG mod, BIG R, BIG  _R);

/*Montgomery left to right fast exponentiation using shift*/
BIG MSMAttack(BIG base, BIG exp, BIG mod, BIG R, BIG  _R);

/*Criteron to divide sample on sets*/
bool Criteron(BIG firstNum, BIG secondNum, BIG mod, BIG R, BIG _R);

/*Generate Universe related to Criteron*/
SPECIMEN GenerateUniverse(MESSAGES sample, BIG PartKey, BIG mod, BIG R, BIG _R);

/*Compute square and multiply Montgomery median time*/
double MedianMSQTime(MESSAGES sample);

/*Decide which criteron is logical*/
void DefineLogicalCriteron(SPECIMEN specimen, BIG d, BIG n, BIG r, BIG _r);

/*Main method*/
void _Timing_Attack(BIG N);

#endif // ATTACK_H