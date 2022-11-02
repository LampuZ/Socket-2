/**
 * @file server.echo.c
 * @author Jarno Conedera, Matteo Lampugnano
 * @brief usare il plugin di doxygen e inserire il tutto 
 * @version 0.1
 * @date 
 * 
 * @copyright copyleft (c) 2022
 * 
 */

/*!
Verificare i seguenti includes:
pacchetto `sys`
- types.h
- socketh
pacchetto `netinet`
- in.h
controllare ctype.h, unistd.h
*/

/*
includes section
*/
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SOCKET_ERROR ((int)-1)   // error code
#define port ((int)5001)           //socket_port
#define RETURN ((int)13)        //valore ASCII per valore di RETURN/carriage
#define quit ((int)27)          //valore ASCII per chiudere la connessione


int main(unsigned argc, char **argv) //inizializzazione del main
{
        
    int handshakingSocket, commSocket;  //definizione dei due socket

    // Last character read from socket
    int readASCII = 0; //se si avesse voluto prendere stringhe intere, sarebbe stato necessario inizializzare un'array malloc
    int clientSize = 0;

    struct sockaddr_in server, client; // Struct che contiene i byte
    server.sin_family = AF_INET; //Definizione famiglia del socket
    server.sin_addr.s_addr = htonl(INADDR_ANY); //Definizione address
    server.sin_port = htons(port);  //Definizione porta del socket
    /** Transport Endpoint definition */
    if ((handshakingSocket = socket(server.sin_family, SOCK_STREAM, 0)) == SOCKET_ERROR)  //0 = flag 
    {
         printf("\nErrore durante l'handshaking\n"); //Stampa dell'errore
        exit(EXIT_FAILURE); //exit
    }
    if (bind( handshakingSocket,(struct sockaddr *) &server, sizeof (server)))  //indirizzo ip con la quale si svolgerà il bind
    {  
        
        printf("\nErrore durante er bind\n");  //stampa dell'errore
        exit(EXIT_FAILURE);
    }

    /** Put the server in listening mode */
    listen(handshakingSocket,1); //socket e numero di client in coda
    //** debug message
    printf("Echo Server: ready on port [%d]\n", port);  //Porta in stato ready

    clientSize = sizeof(client); //Definita la "funzione" che definisce la dimensione del client per non avere errori riguardanti la memoria

    if ((commSocket = accept(handshakingSocket,(struct sockaddr *)&client, &clientSize)) == SOCKET_ERROR) {  //permette la connessione di client al socket
        
        printf("\nErrore durante l'accept\n"); //errore
        exit(EXIT_FAILURE);
    }

    /** after handshaking, send back to client the greetings message, just for testing purposes */
    send(commSocket, "", 0, 0);

    /** do/while cycle that keeps the communication up */
    do {
        if (recv(commSocket, &readASCII , 1 , 0 )) { //0 è una flag ed 1 la dimensione del valore ricevuto
            int asciiVal = (int) readASCII;    // prende i valori da readASCII e li converte in intero

                if (asciiVal != RETURN && asciiVal != 13)
                {    
                    /**
                     * @brief Stampa dell'output nel socket Server.
                     */

                    if(isprint(asciiVal)) //
                        printf("RECV:[%c][%d] Echoing..\n",readASCII , asciiVal);
                  
                }
            // **  echoing back

        send(commSocket,&readASCII,1,0); //Echo Server ha ricevuto il messaggio dal Client
        }
    } while (readASCII != quit);
    /**
     * @brief Chiudo i due socket
     * 
     */
    close(commSocket); 
    close(handshakingSocket);
    fprintf(stderr, "Server connection closed.\n");
}