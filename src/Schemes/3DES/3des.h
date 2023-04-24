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
#include "../DES/des.h"

using namespace std;

//Function to preform triple des encryption
string tripleDesEncryption(string message, string masterKey1, string masterKey2, string masterKey3);
//Function to preform triple des decryption
string tripleDesDecryption(string message, string masterKey1, string masterKey2, string masterKey3);