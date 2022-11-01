/**
 * @file client.echo.c
 * @author gabriele chiusano
 * @brief 
 * @version 0.1
 * @date 2020-12-02
 * 
 * @copyright copyleft (c) 2020
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 1234 // server port
#define SOCKET_ERROR ((int)-1) // error code conversion
#define END_RECV 27 // ASCII value for escape character (/ BUTTON)
#define RETURN_CHAR 1
#define RETURN ((int)13) 
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
    char * prompt = malloc(MAX_PROMPT_LENGTH);
    char prompted, recvChar;
    int len, asciiVal;

    // infinite loop used to simulate interactive prompting
    do 
    {
        printf("Send msg: %c to end transmission\n", END_RECV);
        scanf("%s",prompt);
        // ** loop over the 
        
        for (int i = 0; i < sizeof(prompt) ; i++) 
        {
            // ** from prompt
            char prompted = prompt[i] ;
            if(prompted!= RETURN_CHAR && prompted!=RETURN){
            // ** write to server something
            write(in, &prompted,1);
            // ** wait for the answer from the server
            if (read(out, &recvChar,1) > 0) 
            {
                asciiVal=(int)recvChar;
                
                printf("RECV::[%c][%d]\n", recvChar, (unsigned int)asciiVal);
                fflush(stdout); // ** force stdout to write buffer
                
            }
            }
        }

    } while (recvChar != END_RECV); // if arrives / close the connection

    // ** free the malloc'd variables
    free(prompt);
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
    socketClient = socket(AF_INET,SOCK_STREAM,0);

    /** error management: notify the user if something goes horribly wrong */
    if(socketClient==-1)
    {

        printf("\nErrore durante la creazione\n"); 
        return(SOCKET_ERROR);        
    }
    
    clientConf.sin_family = AF_INET;
    clientConf.sin_addr.s_addr = htonl(INADDR_ANY);
    clientConf.sin_port = htons(0);

    /** bind address to transport endpoint */
    /** error management: notify the user if something goes horribly wrong */
    if (bind( socketClient,(struct sockaddr *)&clientConf, sizeof(clientConf))==-1)
    {
        printf("\nErrore durante il bind\n"); 
        /*
        gestione errore
        */
       return SOCKET_ERROR;
    }

    serverConf.sin_family = AF_INET ;
    serverConf.sin_addr.s_addr = inet_addr(serverAddress );
    serverConf.sin_port = htons(serverPort );
    
    /** try to connect the socket to the specified server  */
    /** error management: notify the user if something goes horribly wrong */
    
    if ((socketServer = connect( socketClient,(struct sockaddr *)&serverConf, sizeof(serverConf))) == SOCKET_ERROR) {  //permette la connessione di client al socket
        
        printf("\nErrore durante la connect\n"); //errore
        exit(EXIT_FAILURE);
    }

    send( socketServer , "Hello! Echo server here.\n", 26, 0);

    /** do some printing in order to notify the user */
    /** error management: notify the user if something goes horribly wrong */

    /** telnetClient simulation */
    telnetClient(socketClient, socketServer);
    

    /* socket::close */
    printf("\nsocket::close\n");
    close(socketClient);
    close(socketServer);
    return (0);
