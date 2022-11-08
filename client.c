/**
 * @file client.echo.c
 * @author Conedera Jarno, Lampugnano Matteo
 * @brief 
 * @version 0.1
 * @date 2022-11-02
 * 
 * @copyright copyleft (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <errno.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 5001 // server port
#define SOCKET_ERROR ((int)-1) // error code conversion
#define END_RECV 27 // ASCII value for escape character (esc)
#define RETURN_CHAR 10
#define RETURN 13 //define tasto invio
#define MAX_PROMPT_LENGTH 200 //define lunghezza massima delle stringhe

/**
 * @brief simulates the prompt of a telnet client using sockets as
 * input parameters.
 * 
 * @param in socket file descriptor integer used to receive stuffs
 * @param out socket file descriptor integer used to send stuffs
 */
void telnetClient(int in,int out) //inizializzazione funzione telnet
{
    // input string:
    char * prompt = malloc(MAX_PROMPT_LENGTH); //istanza malloc contenente stringhe
    char prompted, recvChar;
    int len, asciiVal;

    // infinite loop used to simulate interactive prompting
    do 
    {
        printf("\nSend msg: ^[ to end transmission\n"); //stampa messaggio per chiusura della transmissione
        fgets(prompt,MAX_PROMPT_LENGTH,stdin); //riceve dati in input (sostituito alla scanf)
        // ** loop over the 
       

        for (int i = 0; i < (strlen(prompt)+1) ; i++) //ciclo while
        {
            // ** from prompt
            char prompted = prompt[i] ;
            if(prompted!= RETURN_CHAR && prompted!=RETURN)
            {
            // ** write to server something
            write(in, &prompted,1);
            // ** wait for the answer from the server
            read(in, &recvChar,1);
    
           if(isprint(recvChar))
            printf("\nEcho:%c",recvChar);  //stampa il carattere ricevuto
            fflush(stdout);      
        }
        }
        
    } while (recvChar != END_RECV); // if arrives / close the connection

    // ** free the malloc'd variables
    free(prompt);
}

int main(int argc, char *argv[]) { //inizializzazione funzione main

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <server ip> <server port>\n", argv[0]); //errore
        exit(1);
    }

    // Server INFO
    char * serverAddress = argv[1];
   //int serverPort = SERVER_PORT;
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
    socketClient = socket(AF_INET,SOCK_STREAM,0); //attributi a socketClient

    /** error management: notify the user if something goes horribly wrong */
    if(socketClient==-1)
    {

        printf("\nErrore durante la creazione\n"); //stampa errore
        return(SOCKET_ERROR);        
    }
    
    /**
     * @brief 
     * Determinazione impostazioni del client
     */
    clientConf.sin_family = AF_INET;    
    clientConf.sin_addr.s_addr = htonl(INADDR_ANY);
    clientConf.sin_port = htons(0);

    /** bind address to transport endpoint */
    /** error management: notify the user if something goes horribly wrong */
    if (bind( socketClient,(struct sockaddr *)&clientConf, sizeof(clientConf))==-1) //bind con tra client e server
    {
        printf("\nErrore durante il bind\n"); //stampa errore bind
        /*
        gestione errore
        */
       return SOCKET_ERROR;
    }
    /**
     * @brief 
     * Determinazione impostazioni del server 
     */
    serverConf.sin_family = AF_INET ;
    serverConf.sin_addr.s_addr = inet_addr(serverAddress );
    serverConf.sin_port = htons(serverPort );
    
    /** try to connect the socket to the specified server  */
    /** error management: notify the user if something goes horribly wrong */
    
    if ((socketServer = connect( socketClient,(struct sockaddr *)&serverConf, sizeof(serverConf))) == SOCKET_ERROR) {  //permette la connessione di client al socket
        
        printf("\nErrore durante la connect\n"); //errore
        exit(EXIT_FAILURE);
    }
    char buffer[10];
    read(socketClient, buffer, sizeof(buffer));
    printf("Welcome msg: %s", buffer);
    
        

    /** do some printing in order to notify the user */
    /** error management: notify the user if something goes horribly wrong */

    /** telnetClient simulation */
    telnetClient(socketClient,socketServer);
    

    /* socket::close */
    printf("\nSocket:close \n"); //messaggio che comunica la chiusura del socket
    fflush(stdout);
    close(socketClient);    //chiude socketClient
    close(socketServer);    //chiude socketServer
    return (0);
}
