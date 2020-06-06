#include "../header/utils.h"

#include <iostream>
#include <map>
#include <math.h>
#include <algorithm>
#include <iterator>

using namespace std;

//Permutation
string Permutation(string unpermuted, const int times , const int position[])
{
    string permuted = "";

    for(int i = 0; i < times; i++)
        permuted += unpermuted[position[i] - 1];

    return permuted;
}

//Xor
string XorStrings(string firstOperand, string secondOperand)
{
    string result = "";

    for (int i = 0; i < (int)firstOperand.size(); i++)
    {
        if(firstOperand[i] != secondOperand[i])
            result+= "1";
        else
            result+= "0";
    }

    return result;
}

//Left shift
string LeftShift(string part, int shiftValue)
{
    reverse(part.begin(), part.begin() + shiftValue);
    reverse(part.begin() + shiftValue, part.end());
    reverse(part.begin(), part.end());

    return part;
}

//Split two parts
string* SplitTwoParts(string str)
{
    string* parts = new string[2]{str.substr(0, str.size()/2), str.substr(str.size()/2, str.size()/2)};

    return (string*) parts;
}
