#ifndef CONSTANTS_H
#define CONSTANTS_H

#define feistelLaps 16
#define sBoxes 8
#define outputSboxes 4

#define thirtyTwoBits 32
#define fourtyHeightBits 48
#define fiftySixBits 56
#define sixtyFourBits 64

#include <vector>
#include <string>

using namespace std;

// All binaries
extern vector<string> binaries;
// Incorrect Ciphers
extern string incorrectCiphers[32];
// Initial Permutation
extern int initialPermutation[64];
// Expansion Table
extern int expansionIndex[48];
// S-box Table
extern int sbox[8][4][16];
// f function Permutation 
extern int fFunctionPermutation[32];
// Final Permutation
extern int finalPermutation[64];
// Parity bit 
extern int parityBits[56];
// Number of shifts
extern int shifts[16];
// Key Compression 
extern int compressionIndex[48];
//undo
extern vector<vector<int>> undo;
//solutions;
extern vector<vector<vector<string>>> solutions;
//consideredSbox
extern array<array<int, 6>, 8> consideredSbox;

#endif // CONSTANTS_H
