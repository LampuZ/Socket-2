/**
 * @file Client-Socket.c
 * @author Jarno Conedera
 * @brief 
 * @version 0.1
 * @date 2022-10-19
 * 
 * @copyright copyleft (c) 2020
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include <errno.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netinet/in.h>

#define SERVER_PORT 1314 // server port
#define CLIENT_PORT 1315 // client port
#define SOCKET_ERROR ((int)-1) // error code conversion
#define END_RECV 47 // ASCII value for escape character (/ BUTTON)
#define RETURN_CHAR 10
#define INPUT_STRING_LENGTH 50


#define MAX_PROMPT_LENGTH 200

/**
 * @brief simulates the prompt of a telnet client using sockets as
 * input parameters.
 * 
 * @param in socket file descriptor integer used to receive stuffs
 * @param out socket file descriptor integer used to send stuffs
 */
void telnetClient(int in, int out)
{
    // input string:
    char * prompt = malloc(INPUT_STRING_LENGTH);
    char prompted, recvChar;
    int len, asciiVal;



    // infinite loop used to simulate interactive prompting
    do {
        printf("Send msg: %c to end transmission\n", ...);
        scanf("%s", prompt);
        
        // ** loop over the 
        for (int i = 0; i < ... ; i++) {
            
            // ** from prompt
            char prompted = ... ;

            // ** write to server something
            write(..., ...,...));

            // ** wait for the answer from the server
            if (read(..., ..., ...) > 0) {

                printf("RECV::[%c][%d]\n", ..., (unsigned int)...);
                fflush(stdout); // ** force stdout to write buffer
            }
        }
    } while (recvChar != END_RECV); // if arrives / close the connection

    // ** free the malloc'd variables
    free(...);
}




int main(int argc, char *argv[]) {

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <server ip> <server port>\n", argv[0]);
        exit(1);
    }

    // Server INFO
    char * serverAddress = argv[1];
    // int serverPort = SERVER_PORT;
    int serverPort = atoi(argv[2]); // FIXME: Warning

    int recvChar;                        // last recv"d char
    struct sockaddr_in clientConf, serverConf;    // socket data structures
    int socketClient, socketServer;                // socket identifier


    /** Transport Endpoint definition 
     * 
     * initialize the socket:
     * AF_INET
     * SOCK_STREAM
     * with default behavior
     * 
    */
    socketClient = socket(AF_INET, SOCK_STREAM, 1);

    /** error management: notify the user if something goes horribly wrong */
    if((socketClient == -1) == SOCKET_ERROR);
   
    clientConf.sin_family = AF_INET;
    clientConf.sin_addr.s_addr = htonl(INADDR_ANY);
    clientConf.sin_port = htons(CLIENT_PORT);

    /** bind address to transport endpoint */
    /** error management: notify the user if something goes horribly wrong */
    ...

    serverConf.sin_family = AF_INET ;
    serverConf.sin_addr.s_addr = inet_addr(serverAddress);
    serverConf.sin_port = htons(SERVER_PORT);
    
    /** try to connect the socket to the specified server  */
    /** error management: notify the user if something goes horribly wrong */
    ...

    /** do some printing in order to notify the user */
    /** error management: notify the user if something goes horribly wrong */

    /** telnetClient simulation */
    telnetClient(..);
    

    /* socket::close */
    printf("\nsocket::close\n");
    close(...);

    return (0);
}