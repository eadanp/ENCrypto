/*
* Carolina Campos , Eadan Plotnizky and Naama Scandarion
* Course:  CIS5371/CIS 4634
* Professor: Mehrdad Nojoumian 
*
* Description: Header file for RSA Public-Key Encryption implememtation
*/
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <math.h>
#include "IntFin_lib_h.h"
using namespace std;

//Algorithm to convert binary string to decimal value. taken from https://www.geeksforgeeks.org/program-binary-decimal-conversion/
InfInt binaryToDecimal(string n);

//Function that overloads the power function in the math.h library so that works with big integers
InfInt pow(InfInt base, InfInt exponent);

//Function for converting a decimal to its binary form in reverse order
InfInt RevDecToBin (InfInt n);

//Function for converting a decimal to its binary form 
InfInt DecToBin (InfInt n);

//Function for generating N bit binary string and uses binaryToDecimal(string n) to returns its decimal value
InfInt randomGenerator(int bitsize);

//Function that overloads randomGenerator to create upper and lower bounds
InfInt randomGenerator(InfInt upperBound, InfInt lowerBound);

//Function for converting text to ascii
InfInt convertToASCII(string text);

//Function for converting ascii to text
//string asciiToText(InfInt number);

//Function to perform modular exponentiation using the "Square And Multiply" aproach
InfInt SquareAndMultiply(InfInt base, InfInt exponent, InfInt modulus);

//Function to perform a Miller-Rabin primality test on an integer
bool millerRabin(InfInt oddInt);

//Function to generate a random prime number of N bit 
InfInt PrimeNumberGenerator(int bitsize);

//Function to divide two InfInts
InfInt division(InfInt a, InfInt b);

//` to find modular multiplicative inverse
InfInt modInverse(InfInt e, InfInt n);

//Function to generate e
InfInt generateE(InfInt p, InfInt q);

//Function to pad message
InfInt paddingMsg(InfInt decMsg, InfInt r);

//Function to unpad decrypted msg
InfInt unpaddingMsg(InfInt decrMsg, InfInt r);

//Function to generate p and q
vector<InfInt> generatePandQ();

//Function to generate n
InfInt generateN(InfInt p, InfInt q);

//Function to get public key
vector<InfInt> generatePublicKey(InfInt p, InfInt q);

//function for encryption
InfInt encryption(vector<InfInt> publicKey, InfInt decMsg, InfInt r);

//