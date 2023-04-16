/*
* Eadan Plotnizky and Naama Scandarion
* Course:  CIS5371/CIS 4634
* Professor: Mehrdad Nojoumian 
*
* Description: Implemented Data Encryption Standard (DES)
*/

#include "des.h"

//left shift.
const int leftShift[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 }; //vi = 1 for i ∈ {1, 2, 9, 16}; vi = 2 otherwise
const int rightShift[16] = { 0, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 }; //vi = 1 for i ∈ {2, 9, 16}; vi = 2 otherwise
//key schedule bit selections (PC1 and PC2)
//PC1
const int PC1[56] = 
               {57 ,49 ,41 ,33 ,25 ,17 ,9  ,
				1  ,58 ,50 ,42 ,34 ,26 ,18 ,
				10 ,2  ,59 ,51 ,43 ,35 ,27 ,
				19 ,11 ,3  ,60 ,52 ,44 ,36 ,
				63 ,55 ,47 ,39 ,31 ,23 ,15 ,
				7  ,62 ,54 ,46 ,38 ,30 ,22 ,
				14 ,6  ,61 ,53 ,45 ,37 ,29 ,
				21 ,13 ,5  ,28 ,20 ,12 ,4};
//PC2
const int PC2[48] = 
               {14 ,17 ,11 ,24 ,1  ,5  ,
				3  ,28 ,15 ,6  ,21 ,10 ,
				23 ,19 ,12 ,4  ,26 ,8  ,
				16 ,7  ,27 ,20 ,13 ,2  ,
				41 ,52 ,31 ,37 ,47 ,55 ,
				30 ,40 ,51 ,45 ,33 ,48 ,
				44 ,49 ,39 ,56 ,34 ,53 ,
				46 ,42 ,50 ,36 ,29 ,32};

//Initial Permutation table.
const int IP[64] 
         = {58, 50, 42, 34, 26, 18, 10, 2,
            60, 52, 44, 36, 28, 20, 12, 4,
            62, 54, 46, 38, 30, 22, 14, 6,
            64, 56, 48, 40, 32, 24, 16, 8,
            57, 49, 41, 33, 25, 17, 9, 1,
            59, 51, 43, 35, 27, 19, 11, 3,
            61, 53, 45, 37, 29, 21, 13, 5,
            63, 55, 47, 39, 31, 23, 15, 7};

//Reverse Initial Permutation table. (IP^-1)
const int REV_IP[64] 
            = {40, 8, 48, 16, 56, 24, 64, 32,
               39, 7, 47, 15, 55, 23, 63, 31,
               38, 6, 46, 14, 54, 22, 62, 30,
               37, 5, 45, 13, 53, 21, 61, 29,
               36, 4, 44, 12, 52, 20, 60, 28,
               35, 3, 43, 11, 51, 19, 59, 27,
               34, 2, 42, 10, 50, 18, 58, 26,
               33, 1, 41,  9, 49, 17, 57, 25};
//Expansion permutation table
const int EP[48] = 
               {32 ,1  ,2  ,3  ,4  ,5  ,
				4  ,5  ,6  ,7  ,8  ,9  ,
				8  ,9  ,10 ,11 ,12 ,13 ,
				12 ,13 ,14 ,15 ,16 ,17 ,
				16 ,17 ,18 ,19 ,20 ,21 ,
				20 ,21 ,22 ,23 ,24 ,25 ,
				24 ,25 ,26 ,27 ,28 ,29 ,
				28 ,29 ,30 ,31 ,32 ,1};

//permutation table   
const int PT[32] = { 	16 ,7  ,20 ,21 ,
				29 ,12 ,28 ,17 ,
				1  ,15 ,23 ,26 ,
				5  ,18 ,31 ,10 ,
				2  ,8  ,24 ,14 ,
				32 ,27 ,3  ,9  ,
				19 ,13 ,30 ,6  ,
				22 ,11 ,4  ,25 };
// Substitution boxes
const int SBoxes[8][4][16]=  
	{{ 
        14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7, 
        0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8, 
        4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0, 
        15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 
    }, 
    { 
        15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10, 
        3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5, 
        0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15, 
        13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 
    }, 
    { 
        10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8, 
        13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1, 
        13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7, 
        1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 
    }, 
    { 
        7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15, 
        13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9, 
        10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4, 
        3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 
    }, 
    { 
        2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9, 
        14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6, 
        4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14, 
        11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 
    }, 
    { 
        12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11, 
        10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8, 
        9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6, 
        4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 
    }, 
    { 
        4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1, 
        13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6, 
        1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2, 
        6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 
    }, 
    { 
        13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7, 
        1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2, 
        7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8, 
        2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 
    }};
string subKeys[16] = {};
string message = "";

//Converts Decimal to Binary
string DecToBin (int n){

    string binary = "";
    string ordered = "";
    int i = 0;
    while(n > 0){
        binary = to_string(n % 2) + binary;
        n = n / 2;
        i++;
    }
    while(binary.length() < 4){
		binary = "0" + binary;
	}
    return binary;
}
//Function to shift array n positions to the right
string RightShift(string key, int shift){
    string shifted = "";
    if(shift == 1){
        shifted += key[key.length()-1];
        for(int i = 0; i < key.length() - 1; i++){
            shifted += key[i];
        }
    }
    else if(shift == 2){
        shifted += key[key.length() - 2];
        shifted += key[key.length() - 1];
        for(int i = 0; i < key.length() - 2; i++){
            shifted += key[i];
        }
    }
    //cout << endl << "shifting by " << shift;
    return shifted;

}
//Function to shift array n positions to the left
string LeftShift(string key, int shift){
    string shifted = "";
    if(shift == 1){
        for(int i = 1; i < key.length(); i++){
            shifted += key[i];
        }
        shifted += key[0];
    }
    else if(shift == 2){
        for(int i = 2; i < key.length(); i++){
            shifted += key[i];
        }
        shifted += key[0];
        shifted += key[1];
    }
    //cout << endl << "shifting by " << shift;
    return shifted;

}  
//Function to create 16 48bit encryption subkeys
void EncryptionSubKeyGenerator(string masterKey){
    //compress 64bit key to 56bit key
    string permkey = "";
    for(int i = 0; i < 56; i++){ 
		permkey += masterKey[PC1[i]-1]; 
    } 
    //creating subkeys
    string leftSide = permkey.substr(0,28);
    string rightSide = permkey.substr(28, 28);
    for(int i = 0; i < 16; i++){
        leftSide = LeftShift(leftSide, leftShift[i]);
        rightSide = LeftShift(rightSide, leftShift[i]);
        string prePermute = leftSide + rightSide;
        string roundKey = "";
        for(int j = 0; j < 48; j++){ 
		    roundKey += prePermute[PC2[j]-1]; 
        }
        subKeys[i] = roundKey;
        //cout << endl << endl << "Subkey " << i + 1 << ": " << subKeys[i];
    }
}
void DecryptionSubKeyGenerator(string masterKey){
    //compress 64bit key to 56bit key
    string permkey = "";
    for(int i = 0; i < 56; i++){ 
		permkey += masterKey[PC1[i]-1]; 
    } 
    //creating subkeys
    string leftSide = permkey.substr(0,28);
    string rightSide = permkey.substr(28, 28);
    
    string prePermute = leftSide + rightSide;
    string roundKey = "";
    for(int j = 0; j < 48; j++){ 
		roundKey += prePermute[PC2[j]-1]; 
    }
    subKeys[0] = roundKey;
    //cout << endl << endl << "Subkey " << 0 + 1 << ": " << subKeys[0];
    for(int i = 1; i < 16; i++){
        leftSide = RightShift(leftSide, rightShift[i]);
        rightSide = RightShift(rightSide, rightShift[i]);
        prePermute = leftSide + rightSide;
        roundKey = "";
        for(int j = 0; j < 48; j++){ 
		    roundKey += prePermute[PC2[j]-1]; 
        }
        subKeys[i] = roundKey;
        //cout << endl << endl << "Subkey " << i + 1 << ": " << subKeys[i];
    }
}

//Function to convert plaintext message to 8 bit binary string using the bitset library and to_string() method.
string ToBinary64(string messeage){
    string binaryMessage = "";
    for(int i = 0; i < messeage.length(); i++){
        binaryMessage += bitset<8>(messeage[i]).to_string();
    }
    int padding = 64 - (binaryMessage.length() % 64); // calculates how many 0s needs to be add to creates 64 bit blocks.
    //adds the padding to the binary message.
    if(padding != 64){
        binaryMessage += string(padding, '0');
    }
    //cout << endl << endl << "the binary message is:" << binaryMessage;
    return binaryMessage;
    
}
//Converts binary string to ASCII text using Bitset
string BinToText(string bin){
    bitset<8> bits;
    string ascii_string;
    for (size_t i = 0; i < bin.size(); i += 8) {
    bits = bitset<8>(bin.substr(i, 8));
    char c = char(bits.to_ulong());
    ascii_string += c;
    }
    return ascii_string;
}
//Function to create blocks of 64bits and apply initial permutaion on each block
string InitialPermutation(string block64){
    
    string permutedBlocks = "";
    string permuted = "";
    for(int i = 0; i < block64.length(); i  += 64){
        string block = block64.substr(i, 64);
        
        for(int j = 0; j < 64; j++){
            permuted += block[IP[j]-1];
        }
        
    }
   // cout << endl << endl << "Initial Permutaion: " << permuted;
    return permuted;
    
}
//Encryption Functions:

//Expansion Function
string Expansion(string binaryText){
    string expanded ="";
    for(int i = 0; i < 48; i++){
        expanded += binaryText[EP[i]-1];
    }
    //cout << endl << endl << "expanded string: " << expanded;
    return expanded;
}
//XOR Function
string XOR(string a, string b){
    string result = "";
    int size = a.size();
    for(int i =0; i < size; i++){
        if(a[i] != b[i]){
            result += "1";
        }
        else{
            result += "0";
        }
    }
    return result;
}
//f Function
string F32(string plainRight, string subKey){
    string permSbox = "";
    string expanded = Expansion(plainRight);
    string xored = XOR(expanded, subKey);
    int sBoxed;
    
    string binary = "";
    //XOR function call
    
    
    for (int j = 0; j < 8; j++)
    {
            //S-BOXes
            string padded = xored.substr(j*6,1) + xored.substr(j*6 + 5,1);
            string middle = xored.substr(j*6 + 1,1) + xored.substr(j*6 + 2,1) + xored.substr(j*6 + 3,1) + xored.substr(j*6 + 4,1); 
            int padding = stoi(padded, nullptr, 2);//to convert binary to decimal
            //cout << endl << "row is: " << padding << endl;
            int middleVal = stoi(middle, nullptr, 2);//to convert binary to decimal
            //cout << endl << "col is: " << middleVal << endl;
            sBoxed = (SBoxes[j][padding][middleVal]);
            //cout << endl << endl << "SBox location is: " << sBoxed;
            binary += DecToBin(sBoxed);
            //cout << endl << endl << binary;
    }
    //cout << endl << endl << " after SBoxes the string is: " << binary;
    //permutation
    for(int k=0; k<32 ;k++){
        permSbox += binary[PT[k]-1];
    }   
   // cout << endl << endl << "the SBox after permutation is: " << permSbox;
    return permSbox;
}
//Encryption
string Encryption64(string block64){
    
    string permuted = InitialPermutation(block64);
    string left = permuted.substr(0,32);
    string right = permuted.substr(32,32);
    string temp = "";
    for(int i = 0; i < 16; i++){
        temp = right;
        right = XOR(F32(right, subKeys[i]), left);
        left = temp;
    }
    string preCipher = right + left;
    string cipherBinary = "";
    for(int i = 0; i < 64; i++){
        cipherBinary += preCipher[REV_IP[i]-1];
    }
    //cout << endl << endl << "the cipher binary text is: " << cipherBinary;
    
    return cipherBinary;

}
// Function to perform ECB Mode Of Operation
string ECB (){
    string encrypted = "";
    for(int i=0; i<message.length();i+=64){
        string block = message.substr(i,64);
        encrypted += Encryption64(block);  
    }
    return encrypted;
}
//Decryption Function
string Decryption64(string masterKey){
    //Reversing subKeys order
    DecryptionSubKeyGenerator(masterKey);
	string decrypted = ECB();
    return decrypted;
}
//Function to organize binary string to 64bits blocks
void Organize64(string text){
    for(int i = 0; i < text.length(); i += 64){
        string block = text.substr(i, 64);
        cout << block << endl;  
    }
}


