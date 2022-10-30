#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>

// JOHN IS MY PARTNER

/*
Listen for connections
nc -tv 8080 (any port for server)
ps - all
netstat -ano
*/
void main()
{
    struct sockaddr_in server;
    struct sockaddr_in client;
    int sockaddr_size = sizeof(struct sockaddr_in);

    int sock;
    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket error\n");
        return;
    }

    // Default variables for game logic
    int score = 0;
    int recvNum = 0;
    const char *quit = "QUIT";
    char setWord[25];
    const char *set = "SET";
    const char *submit = "SUBMIT";
    const char *list = "LIST";

    memset(&server, 0x00, sizeof(server));
    server.sin_family = AF_INET; // IPv4
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(8080);

    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("Bind error");
        return;
    }

    listen(sock, 5);
    printf("listening....\n");

    char msg[50];
    memset(msg, 0x00, sizeof(msg));

    int client_sock = accept(sock, (struct sockaddr *)&client, &sockaddr_size);
    printf("Connected to %s:%i\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

    char currentLine[100];
    FILE *dictionary;
    if ((dictionary = fopen("dictionary.txt", "r")) == NULL)
    {
        printf("Error opening file. Problem with path");
        return;
    }


    while (1)
    {
        if (fork() == 0)
        {
            /* Receive message from client already uppercased
                This stops the loop if the message received is nothing.
            */
            recvNum = recv(client_sock,
                           msg,
                           sizeof(msg) - 1,
                           0);

            if (recvNum <= 0)
            {
                close(client_sock);
                break;
            }
            // msg[strcspn(msg, "\n")] = 0;
            printf("Message from client: %s \n", msg);
            // Actual game logic after receiving message
            if(strcmp(msg, list) == 0){
                while (fgets((currentLine), sizeof(currentLine), dictionary) != NULL)
            {
                printf("%s", currentLine); 
            } 
                printf("Continue on this game of life!\n");
            }
            // else if(strcmp(msg, set) == 0){
            //     char secondWord[10];

            //     recv(client_sock, secondWord, sizeof(secondWord)-1,0);
            //     printf("Second Word on Server:%s", secondWord);
            // }
            /*
            Conditions:
            1.) Word cannot be longer than 25 bytes
            Longest word: electroencephalography (22 characters)

            */
            // Set function assuming user types in set
        }
    }
    close(sock);
}