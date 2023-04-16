/*
* Eadan Plotnizky and Naama Scandarion
* Course:  CIS5371/CIS 4634
* Professor: Mehrdad Nojoumian 
*
* Description: Header file for des.cpp
*/

#include <iostream>
#include <string>
#include <bitset>

using namespace std;

//Converts Decimal to Binary
string DecToBin (int n);
//Function to shift array n positions
string LeftShift(string key, int shift);
//Function to create 16 48bit encryption and decryption subkeys
void EncryptionSubKeyGenerator(string masterKey);
void DecryptionSubKeyGenerator(string masterKey);
//Function to convert plaintext message to 8 bit binary string using the bitset library and to_string() method.
string ToBinary64(string messeage);
//Converts binary string to ASCII text using Bitset
string BinToText(string bin);
//Function to create blocks of 64bits and apply initial permutaion on each block
string InitialPermutation(string block64);
//Encryption Functions:

//Expansion Function
string Expansion(string binaryText);
//XOR Function
string XOR(string a, string b);
//f Function
string F32(string plainRight, string subKey);
//Encryption
string Encryption64(string block64);
// Function to perform ECB Mode Of Operation
string ECB ();
//Decryption Function
string Decryption64(string masterKey);
//Function to organize binary string to 64bits blocks
void Organize64(string text);
