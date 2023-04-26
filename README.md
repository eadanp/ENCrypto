# ENCrypto Chat

***Authors: Eadan Plotnizky, Naama Scandarion, Carolina Campos***

**Programming Language: C++**

## Description:

ENCrypto Chat is a secure communication program designed for two users to exchange messages on an encrypted server. The program offers a variety of encryption schemes, including DES, Triple DES, RSA, and El Gamal, which users can choose from based on their preferences and needs.

**Current version doesn't let you choose the asymetric encryption. The defult asymetric encryption is set to RSA**

**To run the program through VSCode make sure you have a GCC compiler.**

## Dependencies:
InfInt.h by sercantutar - https://github.com/sercantutar/infint
This program uses the InfInt library for simple lightweight large integer opereration and storage.

Windows operation system - The program includes socket programming with WINSOCK that requires windows to run.

## Instructions:
1. open Terminal
2. make sure you are in the right directory

3. type `./mainServer.exe <ip address> <des/3des>` to run the server executable through the terminal.
4. make sure to wait for the RSA keys to generate before executing the client (will display message)
5. type `./mainClient.exe <ip address> <des/3des>` to run the client executable through the terminal.
