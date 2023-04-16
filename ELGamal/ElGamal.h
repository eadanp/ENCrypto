/*
* Eadan Plotnizky and Naama Scandarion
* Course:  CIS5371/CIS 4634
* Professor: Mehrdad Nojoumian 
*
* Description: Header file for ElGamal Public-Key Encryption implememtation
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include "infint_lib/InfInt.h"
using namespace std;
//Function to get current time
char* whatIsTheTime();

//Algorithm to convert binary string to decimal value. taken from https://www.geeksforgeeks.org/program-binary-decimal-conversion/
InfInt binaryToDecimal(string n);

//Function that overloads the power function in the math.h library so that works with big integers
InfInt pow(InfInt base, InfInt exponent);

//Function for converting a decimal to its binary form in reverse order
string RevDecToBin (InfInt n);

//Function for converting a decimal to its binary form 
string DecToBin (InfInt n);

//Function for generating N bit binary string and uses binaryToDecimal(string n) to returns its decimal value
InfInt randomGenerator(int bitsize);

//Function that overloads randomGenerator to create upper and lower bounds
InfInt randomGenerator(InfInt upperBound, InfInt lowerBound);

//Function for converting text to ascii
InfInt convertToASCII(string text);

//Function for converting ascii to text
string asciiToText(InfInt number);

//Function to perform modular exponentiation using the "Square And Multiply" aproach
InfInt SquareAndMultiply(InfInt base, InfInt exponent, InfInt modulus);

//Function to perform a Miller-Rabin primality test on an integer
bool millerRabin(InfInt oddInt);

//Function to generate a random prime number of N bit 
InfInt PrimeNumberGenerator(int bitsize);

//Function for encrypting a message with a N size bit key
void encryption(int bitsize, string message);

//Function for decryption
void decryption();