#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

int main(int argc, char **argv){

    string ip = argv[1];
    string des = "..\Schemes\DES\client.exe " + ip;
    if(argv[2] == "des" || argv[2] == "DES"){
        system(des.c_str());
    }

    return 0;
}
