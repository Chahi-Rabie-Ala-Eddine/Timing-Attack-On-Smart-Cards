#ifndef DES_H
#define DES_H

#include "key.h"

#include <vector>

class des
{
    private:
    key desKey;
    string text;

    public:
    des(string text, key desKey);
    void SetKey(key Deskey);
    void SetText(string text);
    string From64to56();
    vector<string> BinaryKeyGeneration();
    vector<string> HexadecimalKeyGeneration();
    string initialPermutationStep();
    string GetNeededSbox(string expanded, int sboxNumber);
    string SboxesStep(string expanded);
    string Feistel(vector<string> key);
    string DesEncryption();
    string DesDecryption();
    void DesEncryptionPrinter();
    void DesDecryptionPrinter();
};

#endif // DES_H
