#include <winsock2.h>
#include <iostream>

using namespace std;
struct CLIENT_INFO
{
    SOCKET hClientSocket ;
    struct sockaddr_in clientAddr ;
} ;

char szServerIPAddr[ ] = "10.132.2.1" ;     // Put here the IP address of the server
int nServerPort = 5050 ;                    // The server port that will be used by
                                            // clients to talk with the server

bool InitWinSock2_0( ) ;
BOOL WINAPI ClientThread( LPVOID lpData ) ;

int main( )
{
    if ( ! InitWinSock2_0( ) )
    {
        cout << "Unable to Initialize Windows Socket environment" << WSAGetLastError( ) << endl ;
        return -1 ;
    }

    SOCKET hServerSocket ;

    hServerSocket = socket(
        AF_INET,        // The address family. AF_INET specifies TCP/IP
        SOCK_STREAM,    // Protocol type. SOCK_STREM specified TCP
        0               // Protoco Name. Should be 0 for AF_INET address family
        ) ;
    if ( hServerSocket == INVALID_SOCKET )
    {
        cout << "Unable to create Server socket" << endl ;
        // Cleanup the environment initialized by WSAStartup()
        WSACleanup( ) ;
        return -1 ;
    }

    // Create the structure describing various Server parameters
    struct sockaddr_in serverAddr ;

    serverAddr . sin_family = AF_INET ;     // The address family. MUST be AF_INET
    serverAddr . sin_addr . s_addr = inet_addr( szServerIPAddr ) ;
    serverAddr . sin_port = htons( nServerPort ) ;

    // Bind the Server socket to the address & port
    if ( bind( hServerSocket, ( struct sockaddr * ) &serverAddr, sizeof( serverAddr ) ) == SOCKET_ERROR )
    {
        cout << "Unable to bind to " << szServerIPAddr << " port " << nServerPort << endl ;
        // Free the socket and cleanup the environment initialized by WSAStartup()
        closesocket( hServerSocket ) ;
        WSACleanup( ) ;
        return -1 ;
    }

    // Put the Server socket in listen state so that it can wait for client connections
    if ( listen( hServerSocket, SOMAXCONN ) == SOCKET_ERROR )
    {
        cout << "Unable to put server in listen state" << endl ;
        // Free the socket and cleanup the environment initialized by WSAStartup()
        closesocket( hServerSocket ) ;
        WSACleanup( ) ;
        return -1 ;
    }

    // Start the infinite loop
    while ( true )
    {
        // As the socket is in listen mode there is a connection request pending.
        // Calling accept( ) will succeed and return the socket for the request.
        SOCKET hClientSocket ;
        struct sockaddr_in clientAddr ;
        int nSize = sizeof( clientAddr ) ;

        hClientSocket = accept( hServerSocket, ( struct sockaddr *) &clientAddr, &nSize ) ;
        if ( hClientSocket == INVALID_SOCKET )
        {
            cout << "accept( ) failed" << endl ;
        }
        else
        {
            HANDLE hClientThread ;
            struct CLIENT_INFO clientInfo ;
            DWORD dwThreadId ;

            clientInfo . clientAddr = clientAddr ;
            clientInfo . hClientSocket = hClientSocket ;

            cout << "Client connected from " << inet_ntoa( clientAddr . sin_addr ) << endl ;

            // Start the client thread
            hClientThread = CreateThread( NULL, 0,
                ( LPTHREAD_START_ROUTINE ) ClientThread,
                ( LPVOID ) &clientInfo, 0, &dwThreadId ) ;
            if ( hClientThread == NULL )
            {
                cout << "Unable to create client thread" << endl ;
            }
            else
            {
                CloseHandle( hClientThread ) ;
            }
        }
    }
    

    closesocket( hServerSocket ) ;
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

BOOL WINAPI ClientThread( LPVOID lpData )
{
    CLIENT_INFO *pClientInfo = ( CLIENT_INFO * ) lpData ;
    char szBuffer[ 1024 ] ;
    int nLength ;

    while ( 1 )
    {
        nLength = recv( pClientInfo -> hClientSocket, szBuffer, sizeof( szBuffer ), 0 ) ;
        if ( nLength > 0 )
        {
            szBuffer[ nLength ] = '\0' ;
            cout << "Received " << szBuffer << " from " << inet_ntoa( pClientInfo -> clientAddr . sin_addr ) << endl ;

            // Convert the string to upper case and send it back, if its not QUIT
            strupr( szBuffer ) ;
            if ( strcmp( szBuffer, "QUIT" ) == 0 )
            {
                closesocket( pClientInfo -> hClientSocket ) ;
                return TRUE ;
            }
            // send( ) may not be able to send the complete data in one go.
            // So try sending the data in multiple requests
            
            cout << "Enter the string to send (QUIT) to stop: ";
            cin.getline(szBuffer, 1024);
            
            int nLength = strlen( szBuffer );
            cout << endl << szBuffer << " " << nLength << endl;
            int nCntSend = 0 ;
            char *pBuffer = szBuffer ;

            while ( ( nCntSend = send( pClientInfo -> hClientSocket, pBuffer, nLength, 0 ) != nLength ) )
            {
                if ( nCntSend == -1 )
                {
                    cout << "Error sending the data to " << inet_ntoa( pClientInfo -> clientAddr . sin_addr ) << endl ;
                    break ;
                }
                if ( nCntSend == nLength )
                    break ;

                pBuffer += nCntSend ;
                nLength -= nCntSend ;
            }
        }
        else
        {
            cout << "Error reading the data from " << inet_ntoa( pClientInfo -> clientAddr . sin_addr ) << endl ;
        }
    }

    return TRUE ;
}