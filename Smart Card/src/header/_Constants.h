#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
#include <chrono>

#include "./_BIGNUM.h"

/*DEFINES*/
#define CPU_T double(CLOCKS_PER_SEC);
#define ms 100

/*TYPES*/
typedef vector<double>::size_type 	   vectorSize;
typedef string::size_type 			   SIZE;
typedef vector<string> 				   SIGNATURE;
typedef vector<vector<string>> 		   SPECIMEN;
typedef vector<vector<vector<string>>> UNIVERSE;
typedef vector<double> 				   TIMES;

/*CONSTANTS SIZES*/
#define _SIZE 3500
#define _LENGTH 5
#define sameExecDiff 2

/*CONSTANTS BIGS*/
const BIG _0 = SetValue("0");
const BIG _1 = SetValue("1");
const BIG _2 = SetValue("2");
const BIG _2048 = SetValue("800");
const BIG _1024 = SetValue("400");
const BIG _512 = SetValue("200");
const BIG _256 = SetValue("100");
const BIG _128 = SetValue("80");
const BIG _64 = SetValue("40");
const BIG n_ = SetValue("A32C8EF5AEE5768A5E37A91057C542690E03464D4CD088FB6EB1996A731F598CB44EB2A4522CD50A5D0F785ACAC3076320B8D8C97843CCB88DC9743F28616209");
const BIG d_ = SetValue("414505FBDF8EFC3758E3106CEFE880F6D267B5B8852036CAF913D6F7613FBD6AD6A0E55FD07711381A2134759A4CBEF540703AA22D2330681BAB1E4B3BEF0AD5");

/*Utils*/
extern unsigned long int reducNumber;
extern unsigned long int indexGuess;
extern unsigned long int reductions[4];

#endif //CONSTANTS_H
