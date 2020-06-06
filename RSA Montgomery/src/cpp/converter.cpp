#include "../header/converter.h"

#include <math.h>

using namespace std;

//From Hexadecimal to Binary
string FromHexadecimalToBinary(string hexadecimal)
{
        unsigned long int i = 0;
        string binary = "";

        while (hexadecimal[i]) 
        {
            switch (hexadecimal[i]) 
            {
                case '0':
                    binary+= "0000";
                    break;
                case '1':
                    binary+= "0001";
                    break;
                case '2':
                    binary+="0010";
                    break;
                case '3':
                    binary+= "0011";
                    break;
                case '4':
                    binary+= "0100";
                    break;
                case '5':
                    binary+= "0101";
                    break;
                case '6':
                    binary+= "0110";
                    break;
                case '7':
                    binary+= "0111";
                    break;
                case '8':
                    binary+= "1000";
                    break;
                case '9':
                    binary+= "1001";
                    break;
                case 'A':
                case 'a':
                    binary+= "1010";
                    break;
                case 'B':
                case 'b':
                    binary+= "1011";
                    break;
                case 'C':
                case 'c':
                    binary+= "1100";
                    break;
                case 'D':
                case 'd':
                    binary+= "1101";
                    break;
                case 'E':
                case 'e':
                    binary+= "1110";
                    break;
                case 'F':
                case 'f':
                    binary+= "1111";
                    break;
                default:
                    break;
            }
            i++;
        }

        return binary;
}

//From Binary to hexadecimal
void CreateMap(unordered_map<string, char> *tempMap)
{
    (*tempMap)["0000"] = '0';
    (*tempMap)["0001"] = '1';
    (*tempMap)["0010"] = '2';
    (*tempMap)["0011"] = '3';
    (*tempMap)["0100"] = '4';
    (*tempMap)["0101"] = '5';
    (*tempMap)["0110"] = '6';
    (*tempMap)["0111"] = '7';
    (*tempMap)["1000"] = '8';
    (*tempMap)["1001"] = '9';
    (*tempMap)["1010"] = 'A';
    (*tempMap)["1011"] = 'B';
    (*tempMap)["1100"] = 'C';
    (*tempMap)["1101"] = 'D';
    (*tempMap)["1110"] = 'E';
    (*tempMap)["1111"] = 'F';
}

string FromBinaryToHexadecimal(string binary)
{
    if(binary.size() < 8)
        binary = "00" + binary;
        
    int temp = 0;
    string hexadecimal = "";
    unordered_map<string, char> tempMap;
    CreateMap(&tempMap);

    for (int i = 1; i <= (4 - (binary.find_first_of('.') != -1 ? binary.find_first_of('.') : binary.size()) % 4) % 4; i++)
        binary = '0' + binary;

    if (binary.find_first_of('.') != -1)
        for (int i = 1; i <= (4 - (binary.size() - (binary.find_first_of('.') != -1 ? binary.find_first_of('.') : binary.size()) - 1) % 4) % 4; i++)
            binary+= '0';

    while (true)
    {
        hexadecimal += tempMap[binary.substr(temp, 4)];
        temp += 4;

        if (temp == (int)binary.size())
            break;

        if (binary.at(temp) == '.')
        {
            hexadecimal += '.';
            temp++;
        }
    }

    return hexadecimal;
}

//From Decimal to Binary
string FromDecimalToBinary(int integer)
{
    int i = 0;
    unsigned long long int  decimal = 0;

    while (integer != 0)
    {
        decimal+= (integer % 2) * pow(10, i);
        integer/= 2;
        i++;
    }

    return to_string(decimal);
}

//From Binary to Decimal
int FrombinaryToDecimal(string ciphertext)
{
    int decimal = 0, base = 1;

    for (int i = (int)ciphertext.length() - 1; i >= 0; i--)
    {
        if (ciphertext[i] == '1')
            decimal += base;

        base = base * 2;
    }

    return decimal;
}
