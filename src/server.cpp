#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

int main(int argc, char **argv){

    string ip = argv[1];
    string symmetric = argv[2];
    string asymmetric = argv[3];
    string des = "DESserver.exe ";
    des += ip;
    des += " ";
    des += asymmetric;
    string tripleDes = "3DESserver.exe ";
    tripleDes += ip;
    tripleDes += " ";
    tripleDes += asymmetric;
    if(symmetric == "des" || symmetric == "DES"){
        system(des.c_str());
    } 
    else {
        system(tripleDes.c_str());
    }

    return 0;
}
