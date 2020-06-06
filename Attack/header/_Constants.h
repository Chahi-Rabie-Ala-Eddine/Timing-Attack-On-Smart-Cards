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
typedef vector<string> 				   MESSAGES;
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

/*Utils*/
extern unsigned long int Medians[4];

#endif //CONSTANTS_H
