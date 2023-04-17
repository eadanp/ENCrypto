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
// Function for extended Euclidean Algorithm
/*InfInt gcdExtended(InfInt a, InfInt b, InfInt* x, InfInt* y)
{

    // Base CaseRe
    if (a == 0) {
        *x = 0, * y = 1;
        return b;
    }

    // To store results of recursive call
    InfInt x1, y1;
    InfInt gcd = gcdExtended(b % a, a, &x1, &y1);

    // Update x and y using results of recursive
    // call
    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}
// Function to find modulo inverse of a
InfInt modInverse(InfInt A, InfInt M)
{
    InfInt x, y;
    InfInt g = gcdExtended(A, M, &x, &y);
    if (g != 1)
        cout << "Inverse doesn't exist";
    else {

        // m is added to handle negative x
        InfInt res = (x % M + M) % M;
        //cout << "Modular multiplicative inverse is " << res;
        return res;
    }
}
*/
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
    while (gcde != 1) {
        e = randomGenerator(On, 1);
        gcde = gcd(e, On);
    }
    return e;
}
vector<InfInt> getPublicKey(InfInt p, InfInt q) {
    //message size is bound by n-1
    InfInt n = p * q;
    //find e
    //InfInt e = generateE(p, q);
    InfInt e = 1753;
    InfInt gcdFactor = (p - 1) * (q - 1);
    bool primeOrNah = false;
    InfInt gcdv = 0;
    while (primeOrNah == false && gcdv != 1) {
        primeOrNah = millerRabin(e, 10);
        gcdv = gcd(e, gcdFactor);
    }
    vector<InfInt> publicKey;
    //n = 3127;
    e = 1753;
    publicKey.push_back(n);
    publicKey.push_back(e);
    return publicKey;
}
//publicKey[n, e]
InfInt encryption(vector<InfInt> publicKey, InfInt decMsg) {
    InfInt n = publicKey[0];
    InfInt e = publicKey[1];
    InfInt cipherText = SquareAndMultiply(decMsg, e, n)%n;
    return cipherText;
}

InfInt getPrivateKey(InfInt e, InfInt n) {
    InfInt d =  modInverse(n, e);
    return d;
}
InfInt decryption(InfInt d, InfInt encMsg, InfInt n) {
    //generate d by finding multiplicative inverse of e
    //by doing extended euclidean alg
    InfInt decrypedNum =SquareAndMultiply(encMsg, d, n)%n;
    return decrypedNum;
}
string ASCIIToString(string decryptedNumString) {
    string cipherplain;
    for (int i = 0; i < decryptedNumString.length(); i++) {
        cipherplain += char(decryptedNumString[i]);
        cout << "letter: " << cipherplain[i] << "\n";
    }
    return cipherplain;
}

int main()
{
   /* InfInt a = 1753;
    InfInt b = 3016;
    cout << (a * b) % 3157 << "\n";*/

    cout << "Welcome to RSA Encryption\n";
    string msg;
    InfInt p = 8039;
    InfInt q = 8011;
    InfInt On = (p - 1) * (q - 1);
    InfInt n = p * q;
    cout << "Enter a message to encrypt\n";
    cin >> msg;
    //msg = "HI";
    InfInt decMsg = convertToASCII(msg);
    cout << "decMSG: " << decMsg << "\n";
    vector<InfInt> publicKey = getPublicKey(p, q);
    //public key[n, e]
    cout << "e: " << publicKey[1] << "\n";
    cout << "n: " << publicKey[0] << "\n";
    cout << "On: " << On << "\n";
    InfInt encMsg = encryption(publicKey, decMsg);
    cout << "encMsg: " << encMsg;
    InfInt privateKey = getPrivateKey(publicKey[1], On);
    cout << "d: " << privateKey << "\n";
    InfInt decrypedNum = decryption(privateKey, encMsg, n);
    cout << "decrypted num: " << decrypedNum << "\n";
    string decryptedString = decrypedNum.toString();
    string decryptedString = ASCIIToString(decryptedString);
    return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
