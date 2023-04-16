/*
* Eadan Plotnizky and Naama Scandarion
* Course:  CIS5371/CIS 4634
* Professor: Mehrdad Nojoumian 
*
* Description: ElGamal Public-Key Encryption implememtation
*/

#include "ElGamal.h"

//Initializing Private and Public Key Variable
InfInt p = "0";
InfInt alpha = "0";
InfInt alpha_pow_key = "0";
InfInt a = "0";
InfInt gammma = "0";
InfInt delta = "0";



//Function to get current time
char* whatIsTheTime(){
    time_t now = time(0);
    char* date_time = ctime(&now);

    return date_time;
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

//Function that overloads the power function in the math.h library so that works with big integers
InfInt pow(InfInt base, InfInt exponent){
    InfInt power = 1;
    for(InfInt i = 0; i < exponent; i++){
        power *= base;
    }
    return power;
}

//Function for converting a decimal to its binary form in reverse order
string RevDecToBin (InfInt n){

    string binary = "";
    int i = 0;
    while(n > 0){
        binary += (n % 2).toString();
        n = n / 2;
        i++;
    }
    return binary;
}

//Function for converting a decimal to its binary form 
string DecToBin (InfInt n){

    string binary = "";
    int i = 0;
    while(n > 0){
        binary = (n % 2).toString() + binary;
        n = n / 2;
        i++;
    }
    return binary;
}

//Function for generating N bit binary string and uses binaryToDecimal(string n) to returns its decimal value
InfInt randomGenerator(int bitsize){
    srand(time(NULL));
    string randomNumber = "1";
    
    for (int i = 0; i < bitsize-1; i++){
        int num = ((int)rand() % 2);
        randomNumber += to_string(num);
        //cout << randomNumber.length() << endl;
    }
    InfInt number_string = binaryToDecimal(randomNumber);
    //cout << randomNumber << endl;
    return number_string;
}

//Function that overloads randomGenerator to create upper and lower bounds
InfInt randomGenerator(InfInt upperBound, InfInt lowerBound){
    InfInt randomNumber = "0";

    InfInt random = randomGenerator(DecToBin(upperBound).length() - 1);
    randomNumber = (random % (upperBound - lowerBound + 1) + lowerBound);
    return randomNumber;
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

//Function for converting ascii to text
string asciiToText(InfInt number)
{
    int num = 0;
    string text = "";
    string n = number.toString();
    for (int i = 0; i < n.length(); i++) {
 
        // Append the current digit
        num = num * 10 + (n[i] - '0');
 
        // If num is within the required range
        if (num >= 32 && num <= 122) {
 
            // Convert num to char
            char ch = (char)num;
            text += ch;
 
            // Reset num to 0
            num = 0;
        }
    }
    return text;
}
//Function to perform modular exponentiation using the "Square And Multiply" aproach
InfInt SquareAndMultiply(InfInt base, InfInt exponent, InfInt modulus){
    string binary_exponent = RevDecToBin(exponent);
    InfInt b = 1;
    if(exponent == 0){
        return b;
    }
    InfInt A = base;
    if(binary_exponent[0] == '1'){
        b = base;
    }
    for(int i = 1; i < binary_exponent.length(); i++){
        A = pow(A, 2) % modulus;
        if(binary_exponent[i] == '1'){
            b = (A * b) % modulus;
        }
    }
   return b;
}

//Function to perform a Miller-Rabin primality test on an integer
bool millerRabin(InfInt oddInt){
    InfInt s = 0;
    InfInt r = 0;
    InfInt n = oddInt - 1;
    InfInt t = 50;

    r = n;
 for(InfInt i = 1; i < t; i++){
        InfInt a = randomGenerator(oddInt - 2, 2); //will be a random interger
        InfInt y = SquareAndMultiply(a,r,oddInt);
        if( y != 1 && y != oddInt-1 ){
            InfInt j=1;
            while(j <= s - 1 && y != oddInt - 1){
                y = pow(y, 2) % oddInt;
                if(y == 1){
                    return false;
                }
                j++;
            }
            if(y != oddInt-1){
                return false;
            }
        }
    }
 return true;
}

//Function to generate a random prime number of N bit 
InfInt PrimeNumberGenerator(int bitsize){
    InfInt oddInt = "";
    do{
        oddInt = randomGenerator(bitsize);
    }while(millerRabin(oddInt) == 0);
    return oddInt;
}

//Function for encrypting a message with a N size bit key
void encryption(int bitsize, string message){
    cout << "The message you entered is: " << message << endl;
    cout << "start time: " << whatIsTheTime() << endl;
    p = PrimeNumberGenerator(bitsize);
    cout << "Prime Number: " << p << endl;
    cout << endl << "end time: " << whatIsTheTime() << endl;
    a = randomGenerator(p-2,1);
    cout << "Your private key is: " << a << endl;
    alpha = randomGenerator(p - 1, 1);
    alpha_pow_key = SquareAndMultiply(alpha, a, p);
    InfInt k = randomGenerator(p - 1,1); //random interger between 1 and p-2
    
    InfInt messageNum = convertToASCII(message); // range of {0 till p-1}
    
    
    gammma = SquareAndMultiply(alpha, k, p); // compute gamma = alpa ^ k mod p 
    
    delta = (messageNum * SquareAndMultiply(alpha_pow_key, k, p)) % p; // compute delta = message * (alpa ^ a)^k mod p 


    // return ciphertext which is gamma and delta 
}

//Function for decryption
void decryption(){
    InfInt message = (delta * SquareAndMultiply(gammma, p-1-a, p)) % p;
    cout << endl << "This is the message in decimal format: " << message << endl;
    string textMessage = asciiToText(message);
    cout << endl << "Your decrypted message is: " << textMessage << endl;
    // recover m : gamma ^ negative of a * delta mod p 
    // return plaintext 
}


