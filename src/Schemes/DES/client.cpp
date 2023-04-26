#include <winsock2.h>
#include <iostream>
#include <fstream>
#include "des.h"
#include "../RSA/RSA.h"
using namespace std;

char szServerIPAddr[ 20 ] = "10.132.2.1" ;     // Put here the IP address of the server
int nServerPort = 5050 ;                    // The server port that will be used by                                            // clients to talk with the server
InfInt masterKey = randomGenerator(64);
string key = DecToBin(masterKey.toString());


bool InitWinSock2_0( ) ;

int main(int argc, char **argv)
{
    //cout << "Enter the server IP Address: " ;
    //cin >> szServerIPAddr ;
    //cout << "Enter the server port number: " ;
    //cin >> nServerPort ;

    if ( ! InitWinSock2_0( ) )
    {
        cout << "Unable to Initialize Windows Socket environment" << WSAGetLastError( ) << endl ;
        return -1 ;
    }

    SOCKET hClientSocket ;

    hClientSocket = socket(
        AF_INET,        // The address family. AF_INET specifies TCP/IP
        SOCK_STREAM,    // Protocol type. SOCK_STREM specified TCP
        0               // Protoco Name. Should be 0 for AF_INET address family
        ) ;
    if ( hClientSocket == INVALID_SOCKET )
    {
        cout << "Unable to create Server socket" << endl ;
        // Cleanup the environment initialized by WSAStartup()
        WSACleanup( ) ;
        return -1 ;
    }


    // Create the structure describing various Server parameters
    struct sockaddr_in serverAddr ;

    serverAddr . sin_family = AF_INET ;     // The address family. MUST be AF_INET
    serverAddr . sin_addr . s_addr = inet_addr( argv[1] ) ;
    serverAddr . sin_port = htons( nServerPort ) ;

    // Connect to the server
    if ( connect( hClientSocket, ( struct sockaddr * ) &serverAddr, sizeof( serverAddr ) ) < 0 )
    {
        cout << "Unable to connect to " << argv[1] << " on port " << nServerPort << endl ;
        closesocket( hClientSocket ) ;
        WSACleanup( ) ;
        return -1 ;
    }

    char szBuffer[ 1024 ] = "" ;
    cout << "Type 'QUIT' and then use Ctrl + C to end program" << endl;
    ofstream fout("backend.txt");

    //recieve rsa public key from server
    int nLength = strlen( szBuffer ) ;
    nLength = recv( hClientSocket, szBuffer, 1024, 0 ) ;
    InfInt n = szBuffer;
    nLength = recv( hClientSocket, szBuffer, 1024, 0 ) ;
    InfInt e = szBuffer;
    nLength = recv( hClientSocket, szBuffer, 1024, 0 ) ;
    InfInt r = szBuffer;

    //send encrypted des key to server
    string encrypteKey = encryption(n, e, r, key).toString();
    strcpy(szBuffer, encrypteKey.c_str());
    int nCntSend = 0 ;
    char *pBuffer = szBuffer ;
    nCntSend = send( hClientSocket, pBuffer, 1024, 0 );
    
    while ( strcmp( szBuffer, "QUIT" ) != 0 )
    {
       
        cout << "ALICE: " ;
        cin.getline(szBuffer, 1024);

        EncryptionSubKeyGenerator(key);
        strcpy(szBuffer, ECB(ToBinary64(szBuffer)).c_str());
        
        fout << "ALICE: " << szBuffer << endl;
        
        int nLength = strlen( szBuffer ) ;

        // send( ) may not be able to send the complete data in one go.
        // So try sending the data in multiple requests
        int nCntSend = 0 ;
        char *pBuffer = szBuffer ;

        while ( ( nCntSend = send( hClientSocket, pBuffer, 1024, 0 ) != 1024 ) )
        {
            if ( nCntSend == -1 )
            {
                cout << "Error sending the data to server" << endl ;
                break ;
            }
            if ( nCntSend == nLength )
                break ;

            pBuffer += nCntSend ;
            nLength -= nCntSend ;
        }

        strupr( szBuffer ) ;
        if ( strcmp( szBuffer, "QUIT" ) == 0 )
        {
            break ;
        }

        nLength = recv( hClientSocket, szBuffer, 1024, 0 ) ;
        if ( nLength > 0 )
        {
            szBuffer[ nLength ] = '\0' ;
            fout << "BOB: " << szBuffer << endl;
            string str(szBuffer);
            strcpy(szBuffer, BinToText(Decryption64(key, str)).c_str());
            cout << "BOB: " << szBuffer << endl ;
        }
        
    }
    closesocket( hClientSocket ) ;
    WSACleanup( ) ;
    return 0 ;
}

bool InitWinSock2_0( )
{
    WSADATA wsaData ;
    WORD wVersion = MAKEWORD( 2, 0 ) ;

    if ( ! WSAStartup( wVersion, &wsaData ) )
        return true ;

    return false ;
}