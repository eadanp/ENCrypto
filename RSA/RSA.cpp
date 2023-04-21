// RSA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <math.h>
#include "IntFin_lib_h.h"

using namespace std;
namespace std {
    string to_string(const InfInt& num);
}

//Function for converting a decimal to its binary form in reverse order
string RevDecToBin(InfInt n) {

    string binary = "";
    InfInt i = 0;
    while (n > 0) {
        binary += (n % 2).toString();
        n = n / 2;
        i++;
    }
    return binary;
}
//Function for converting text to ascii
InfInt convertToASCII(string text)
{
    string result = "";
    for (int i = 0; i < text.length(); i++)
    {
        char x = text[i];
        result += to_string(int(x));
    }
    InfInt number = result;
    return number;
}
//Function that overloads the power function in the math.h library so that works with big integers
InfInt pow(InfInt base, InfInt exponent) {
    InfInt power = 1;
    for (InfInt i = 0; i < exponent; i++) {
        power *= base;
    }
    return power;
}

InfInt SquareAndMultiply(InfInt base, InfInt exponent, InfInt modulus) {
    string binary_exponent = RevDecToBin(exponent);
    InfInt b = 1;
    if (exponent == 0) {
        return b;
    }
    InfInt A = base;
    if (binary_exponent[0] == '1') {
        b = base;
    }
    for (int i = 1; i < binary_exponent.length(); i++) {
        A = pow(A, 2) % modulus;
        if (binary_exponent[i] == '1') {
            b = (A * b) % modulus;
        }
    }
    return b;
}
//Algorithm to convert binary string to decimal value. taken from https://www.geeksforgeeks.org/program-binary-decimal-conversion/
InfInt binaryToDecimal(string n)
{
    string num = n;
    InfInt dec_value = 0;

    // Initializing base value to 1, i.e 2^0
    InfInt base = 1;

    int len = num.length();
    for (int i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }

    return dec_value;
}

//Function for converting a decimal to its binary form 
string DecToBin(InfInt n) {

    string binary = "";
    int i = 0;
    while (n > 0) {
        binary = (n % 2).toString() + binary;
        n = n / 2;
        i++;
    }
    return binary;
}
//Function for generating N bit binary string and uses binaryToDecimal(string n) to returns its decimal value
InfInt randomGenerator(int bitsize) {
    srand(time(NULL));
    string randomNumber = "1";

    for (int i = 0; i < bitsize - 1; i++) {
        int num = ((int)rand() % 2);
        randomNumber += to_string(num);
        //cout << randomNumber.length() << endl;
    }
    InfInt number_string = binaryToDecimal(randomNumber);
    //cout << randomNumber << endl;
    return number_string;
}

//Function that overloads randomGenerator to create upper and lower bounds
InfInt randomGenerator(InfInt upperBound, InfInt lowerBound) {
    InfInt randomNumber = "0";

    InfInt random = randomGenerator(DecToBin(upperBound).length() - 1);
    randomNumber = (random % (upperBound - lowerBound + 1) + lowerBound);
    return randomNumber;
}
bool millerRabin(InfInt e, InfInt t) {
    InfInt s = 0;
    InfInt r = 0;
    InfInt newE = e - 1;
    while (newE %2 != 0) {
        newE = newE / 2;
        s++;
    }
    InfInt upper = e - 2;
    r = newE;
    for (InfInt i = 1; i < t; i++) {
        InfInt a = randomGenerator(upper - 2, upper); //will be a random interger
        InfInt y = SquareAndMultiply(a, r, e);
        if (y != 1 && y != e - 1) {
            InfInt j = 1;
            while (j <= s - 1 && y != e - 1) {
                y = pow(y, 2) % e;
                if (y == 1) {
                    return false;
                }
                j++;
            }
            if (y != e - 1) {
                return false;
            }
        }
    }
    return true;
}
// Function to return gcd of a and b
InfInt gcd(InfInt a, InfInt b)
{
    InfInt result = min(a, b); // Find Minimum of a and b
    while (result > 0) {
        if (a % result == 0 && b % result == 0) {
            break;
        }
        result--;
    }
    return result; // return gcd of a and b
}
InfInt division(InfInt a, InfInt b) {
    InfInt result;
    while (a > 0) {
        result++;
        a = a - b;
       // cout << "a: " << a << "\n";
    }
    return result;
}
InfInt modInverse(InfInt e, InfInt n) {
    /*InfInt newE = pow(e, -1);
    InfInt r = e;
    InfInt s;
    InfInt newN;
    //extended euclidean
    while (r != 1) {
        s = division(n, r);
        newN = 
        r = n % e;
    }
    return r;*/
    InfInt b = e;
    InfInt a = n;
    InfInt d;
    InfInt x;
    InfInt y;
    InfInt x2;
    InfInt y2;
    InfInt x1;
    InfInt y1;
    InfInt q;
    InfInt r;
    if (b == 0) {
        d = a;
        x = 1;
        y = 0;
        cout << "x: " << x << "\n";
        cout << "y: " << y << "\n";
    }
    x2 = 1;
    x1 = 0;
    y2 = 0;
    y1 = 1;
    while (b > 0) {
        q = a / b;
        r = a - q*b;
        x = x2 - q * x1;
        y = y2 - q*y1;
        a = b;
        b = r;
        x2 = x1;
        x1 = x;
        y2 = y1;
        y1 = y;
    }
    d = a;
    x = x2;
    y = y2;

    //gcd = old_r
    cout << "x: " << x << "\n";
    cout << "y: " << y << "\n";
    cout << "d: " << d << "\n";
    InfInt newX = e + x;
    cout << "inverse: " << newX << "\n";
    return newX;
}

InfInt generateE(InfInt p, InfInt q) {
    //e needs to be between 1 and (p-1)*(q-1)
    InfInt gcde = 0;
    InfInt e;
    InfInt On = (p - 1) * (q - 1);
    InfInt n = p * q;
    bool primeOrNah = false;
    while (gcde != 1 && primeOrNah == false) {
        e = randomGenerator(On, 1);
        gcde = gcd(e, On);
        primeOrNah = millerRabin(e, 10);
    }
    return e;
}
//generate public key from p and q
vector<InfInt> getPublicKey(InfInt p, InfInt q) {
    //message size is bound by n-1
    InfInt n = p * q;
    //find e
   // InfInt e = generateE(p, q);
    InfInt r = randomGenerator(64);
    vector<InfInt> publicKey;
    //can use this value for faster running
    InfInt e = 65537;
    publicKey.push_back(n);
    publicKey.push_back(e);
    publicKey.push_back(r);
    return publicKey;
}
string ASCIIToString(string decryptedNumString) {
    string cipherplain;
    for (int i = 0; i < decryptedNumString.length(); i++) {
        cipherplain += char(decryptedNumString[i]);
        cout << "letter: " << cipherplain[i] << "\n";
    }
    return cipherplain;
}
//Function to generate a random prime number of N bit 
InfInt PrimeNumberGenerator(int bitsize) {
    InfInt oddInt;
    do {
        oddInt = randomGenerator(bitsize);
    } while (millerRabin(oddInt, 10) == 0);
    return oddInt;
}
//pq[p, q]
vector<InfInt> generatePandQ() {
    InfInt p = PrimeNumberGenerator(215);
    InfInt q = PrimeNumberGenerator(215);
    vector<InfInt> pq;
    pq.push_back(p);
    pq.push_back(q);
    return pq;
}
//pad plaintext
InfInt paddingMsg(InfInt decMsg, InfInt r) {
    string deciMsg = decMsg.toString();
    //generate random number of 64 bit length
    string strR = r.toString();
    string padding = "002" + strR + "0";
    cout << "padding: " << padding << "\n";
    deciMsg.insert(0, padding);
    InfInt paddedMsg = deciMsg;
    return paddedMsg;
}
//unpad decrypted message
InfInt unpaddingMsg(InfInt decrMsg, InfInt r) {
    string decrStringMsg = decrMsg.toString();
    int numOfRDigits = r.numberOfDigits();
    string strR = r.toString();
    int length = numOfRDigits + 2;
    decrStringMsg.erase(0, length);
    InfInt unpaddedMsg = decrStringMsg;
    return unpaddedMsg;
}
//multiply p and q
InfInt generateN(InfInt p, InfInt q) {
    return p * q;
}
/*void ASCIIToString(InfInt decrNum) {
    string decryptedText;
    string letter;
    for (int i = 0; i < decrNum.size(); i++) {
        letter += decrNum.digitAt(i);
    }
}*/
//finds d which is inverse of e mod phi
InfInt getPrivateKey(InfInt e, InfInt p, InfInt q) {
    InfInt On = (p - 1) * (q - 1);
    InfInt d = modInverse(On, e);
    return d;
}
InfInt decryption(InfInt d, InfInt encMsg, InfInt n, InfInt r) {
    //generate d by finding multiplicative inverse of e
    //by doing extended euclidean alg
    InfInt decrypedNum = SquareAndMultiply(encMsg, d, n) % n;
    cout << "decrypted num: " << decrypedNum;
    InfInt unpaddedDecMsg = unpaddingMsg(decrypedNum, r);
    cout << "unpadded Decrpyted: " << unpaddedDecMsg;
    return unpaddedDecMsg;
}
//publicKey[n, e]
//takes string msg, finds decimal value,  pads it, and encrypts it
InfInt encryption(vector<InfInt> publicKey, string msg) {
    //take binary and convert to decimal
    string num;
    InfInt r = publicKey[2];
    for (int i = 0; i < 8; i++) {
        num += binaryToDecimal(msg.substr(i * 8, 8)).toString();
    }
    cout << "binaryToDecimal: " << num <<"\n";
    InfInt decMsg = num;
    InfInt paddedDecMsg = paddingMsg(decMsg, r);
    cout << "padded: " << paddedDecMsg << "\n";
    InfInt n = publicKey[0];
    InfInt e = publicKey[1];
    InfInt cipherText = SquareAndMultiply(paddedDecMsg, e, n) % n;
    return cipherText;
}
//How to use:
//first generate p and q
// vector<InfInt> pq = generatePandQ();
// InfInt p = pq[0];
// InfInt q = pq[1];
//generate n
// InfInt n = p*q;
//create public key vector publicKey[n, e]
// vector<InfInt> publicKey = getPublicKey(p, q);
//ENCRYPTION
// InfInt encMsg = encryption(publicKey, msg);
//get private key
// InfInt privateKey = getPrivateKey(publicKey[1], p, q);
//DECRYPTION
// InfInt decrypedNum = decryption(privateKey, encMsg, n, publicKey[2]);

