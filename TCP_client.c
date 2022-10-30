#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>

/*
nc -ltv 8080 (port on server to listen for incoming connections)
Requires server to be active or will fail.
*/

// Method to see if command user typed in is valid.
int validCommand(char command[])
{
    const char *space = " ";
    char *firstWord = strtok(command, space);
    // printf("%s\n", firstWord);

    // comparator for each statement to determine legality
    if (strcmp(firstWord, "QUIT") == 0 || strcmp(firstWord, "SET") == 0|| strcmp(firstWord, "SUBMIT") == 0|| strcmp(firstWord, "LIST") == 0)
    {   printf("\nLegal Command!\n");
        return 1;
    }
    return 0;
}

char *getSecondWord(char command[]){
    memset(&command, 0,sizeof(command));
    const char *space = " ";
    char* secondWord;
    secondWord = malloc(15);

    char secondWordle[15];
    strcpy(secondWordle, strtok(NULL, space));
    
    strcpy(secondWord, secondWordle);


    secondWord[strcspn(secondWord, "\n")] = 0;
    
    printf("\n2nd Word:%s", secondWord);
    return secondWord;
}

void main()
{
    char send_msg[50];

    printf("Sock is being created \n");
    int sock;
    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket error\n");
        return;
    }
    // printf("Socket was created successfully \n");

    struct sockaddr_in dest;
    int sockaddr_size = sizeof(struct sockaddr_in);
    memset(&dest, 0x00, sizeof(dest));

    dest.sin_family = AF_INET;
    dest.sin_addr.s_addr = inet_addr("127.0.0.1");
    dest.sin_port = htons(8080);

    if (connect(sock, (struct sockaddr *)&dest, sockaddr_size) < 0)
    {
        perror("Connection failure\n");
        return;
    }
    // printf("Client connected successfully to server. \n");

    char *welcome_msg;
    welcome_msg = ("Welcome to the server \n"
                   "Type the following: \n"
                   "LIST: Get all the current words in dictionary with current substring \n"
                   "SET: Set the substring. \n"
                   "SUBMIT: Submit word to server and see if it exists in dictionary \n"
                   "QUIT: End the game and get your score! \n"
                   "\n");

    char *illegalMessage;
    illegalMessage = ("That is not a recognized command. \n"
                      "Please type ONLY the following: \n"
                      "LIST \n "
                      "SET \n "
                      "SUBMIT \n"
                      "QUIT \n");
    
    const char *set = "SET";
    const char *submit = "SUBMIT";
    const char *list = "LIST";

    printf("%s", welcome_msg);

    

    while (1)
    {
        memset(send_msg, 0x00, sizeof(send_msg));
        printf("\nType a command: \n");
        fgets(send_msg, sizeof(send_msg), stdin);
        // send_msg[-1] =0
        //Getting rid of '\n'
        
        send_msg[strcspn(send_msg, "\n")] = 0;
        // send_msg[strlen()]

        // Capitalize the message being sent BEFORE sending
        for (int i = 0; i < sizeof(send_msg); i++)
        {
            send_msg[i] = toupper(send_msg[i]);
        }
        char send_msg_copy[15];
        strcpy(send_msg_copy, send_msg);
        printf("Message to see if legal: %s", send_msg);
        if (validCommand(send_msg) == 1)
        {
            send(sock, send_msg_copy, strlen(send_msg_copy), 0);

            // See if message is quit
            const char *quit = "QUIT";
            int cmp = strcmp(quit, send_msg);

            if(strcmp(list, send_msg) == 0){
                printf("LISTING...");
                
                
            }else if(strcmp(set, send_msg) == 0)
            {       char *secondWord;
                    secondWord = getSecondWord(send_msg);
                    

                    
                    printf("We're setting the word to --%s", secondWord);
                    
            }
            else if(strcmp(quit, send_msg) == 0)
            {
                // Also make sure client gets score.
                printf("Thank you for playing. Have a good day. :-) \n");
                break;
            }
        }
        else
        {
            printf("%s", illegalMessage);
        }
    }

    close(sock);
}