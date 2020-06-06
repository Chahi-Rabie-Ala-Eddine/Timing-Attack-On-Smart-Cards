#include "../header/des.h"
#include "../header/key.h"
#include "../header/tripledes.h"

//triple des encryption
string TripleDesEnryption(string plaintext, string k1, string k2, string k3)
{	 
	key k;
    k.SetContent(k1);
    des* DES = new des(plaintext,k.GetContent());
    
    /*First step*/
    string cipher = DES->DesEncryption();
    
    /*Second step*/
    DES->SetText(cipher);
    DES->SetKey(k2);
    string cipher2 = DES->DesDecryption();
    
    /*Third step*/
    DES->SetText(cipher2);
    DES->SetKey(k3);
    string cipher3 = DES->DesEncryption();
    
    return cipher3;
}

//triple des decryption
string TripleDesDecryption(string ciphertext, string k1, string k2, string k3)
{
	key k;
    k.SetContent(k3);
    des* DES = new des(ciphertext,k.GetContent());
    
    /*First step*/
    string plaintext1 = DES->DesDecryption();
    
    /*Second step*/
    DES->SetText(plaintext1);
    DES->SetKey(k2);
    string plaintext2 = DES->DesEncryption();
    
    /*Third step*/
    DES->SetText(plaintext2);
    DES->SetKey(k1);
    string plaintext3 = DES->DesDecryption();
	
	return plaintext3;
}

