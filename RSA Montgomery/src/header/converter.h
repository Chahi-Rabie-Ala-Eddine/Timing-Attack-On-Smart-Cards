#ifndef CONVERTER_H
#define CONVERTER_H

#endif // CONVERTER_H

#include <unordered_map>

using namespace std;

//From Hexadecimal to Binary
string FromHexadecimalToBinary(string binary);

//From Binary to hexadecimal
void CreateMap(unordered_map<string, char> *um);

string FromBinaryToHexadecimal(string binary);

//From Decimal to Binary
string FromDecimalToBinary(int integer);

//From Binary to Decimal
int FrombinaryToDecimal(string ciphertext);
