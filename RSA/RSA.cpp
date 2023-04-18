/*
* Carolina Campos, Eadan Plotnizky and Naama Scandarion
* Course:  CIS5371/CIS 4634
* Professor: Mehrdad Nojoumian 
*
* Description: cpp file for RSA Public-Key Encryption implememtation
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <math.h>
#include "IntFin_lib_h.h"

using namespace std;

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
    //extended euclidean algorithm
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
    //returns coefficient that is inverse of e as+bt congruent 1
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
InfInt unpaddingMsg(InfInt decrMsg, InfInt r) {
    string decrStringMsg = decrMsg.toString();
    int numOfRDigits = r.numberOfDigits();
    string strR = r.toString();
    int length = numOfRDigits + 2;
    decrStringMsg.erase(0, length);
    InfInt unpaddedMsg = decrStringMsg;
    return unpaddedMsg;
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
InfInt generateN(InfInt p, InfInt q) {
    return p * q;
}
vector<InfInt> getPublicKey(InfInt p, InfInt q) {
    //message size is bound by n-1
    InfInt n = p * q;
    //find e
    InfInt e = generateE(p, q);
    vector<InfInt> publicKey;
    //can use this value for faster running
    //InfInt e = 65537;
    publicKey.push_back(n);
    publicKey.push_back(e);
    return publicKey;
}
//publicKey[n, e]
InfInt encryption(vector<InfInt> publicKey, InfInt decMsg, InfInt r) {
    InfInt n = publicKey[0];
    InfInt e = publicKey[1];
    InfInt paddedDecMsg = paddingMsg(decMsg, r);
    cout << "padded: " << paddedDecMsg << "\n";
    InfInt cipherText = SquareAndMultiply(paddedDecMsg, e, n)%n;
    return cipherText;
}

InfInt getPrivateKey(InfInt e, InfInt p, InfInt q) {
    InfInt On = (p-1)*(q-1);
    InfInt d =  modInverse(On, e);
    return d;
}
InfInt decryption(InfInt d, InfInt encMsg, InfInt n, InfInt r) {
    //generate d by finding multiplicative inverse of e
    //by doing extended euclidean alg
    InfInt decrypedNum =SquareAndMultiply(encMsg, d, n)%n;
    InfInt unpaddedDecMsg = unpaddingMsg(decrypedNum, r);
    cout << "unpadded decrypted msg: " << unpaddedDecMsg << "\n";
    return unpaddedDecMsg;
}
/*string ASCIIToString(string decryptedNumString) {
    string cipherplain;
    for (int i = 0; i < decryptedNumString.length(); i++) {
        cipherplain += char(decryptedNumString[i]);
        cout << "letter: " << cipherplain[i] << "\n";
    }
    return cipherplain;
}*/

int main()
{
    cout << "Welcome to RSA Encryption\n";
    string msg;
    cout << "Enter a key to encrypt\n";
    cin >> msg;
    //msg = "CAROLINA";
    InfInt decMsg = convertToASCII(msg);
    cout << "decMSG: " << decMsg << "\n";
    InfInt r = randomGenerator(64);
    //InfInt unpaddedDecMsg = unpaddingMsg(paddedDecMsg, r);
    //cout << "unpadded: " << unpaddedDecMsg << "\n";
    //generate large p and q
    vector<InfInt> pq = generatePandQ();
    InfInt p = pq[0];
    cout << "p: " << p << "\n";
    InfInt q = pq[1];
    cout << "q: " << q << "\n";
    //InfInt p = "3120024110683264947007910858022488502197";
    //InfInt q = "1756653271639622701011982777775599094339";
    InfInt On = (p - 1) * (q - 1);
    InfInt n = p * q;
    
    vector<InfInt> publicKey = getPublicKey(p, q);
    //public key[n, e]
    cout << "e: " << publicKey[1] << "\n";
    cout << "n: " << publicKey[0] << "\n";
    cout << "On: " << On << "\n";
    InfInt encMsg = encryption(publicKey, decMsg, r);
    cout << "encMsg: " << encMsg;
    InfInt privateKey = getPrivateKey(publicKey[1], p, q);
    cout << "d: " << privateKey << "\n";
    InfInt decrypedNum = decryption(privateKey, encMsg, n, r);
    cout << "decrypted num: " << decrypedNum << "\n";
    /*string decryptedString = decrypedNum.toString();
    string decryptedString = ASCIIToString(decryptedString);*/
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
