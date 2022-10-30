#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>

void split(){

   char str[80] = "This is - www.tutorialspoint.c--om - website";
   const char s[2] = "-";
   char *token;

   /* get the first token */
   token = strtok(str, s);
   
   /* walk through other tokens */
   while( token != NULL ) {
      printf( "%s\n", token );
        
      token = strtok(NULL, s);
   }
// printf("%s\n", token);
// token = strtok(NULL, s);
// printf("%s\n", token);
   
}


// char getSecondWord() {
// char word2[] = "Hello";
//     char *word = &word2;
//     printf(word);

// return word;
// }



char* get_message ()
{
    char *mymessage;
    mymessage = malloc (sizeof (char) * 15);
    
    strcpy(mymessage, "Hello World");
    
    return mymessage;
}


void pointers(char substring[4]){
// int *pc, c;
// c = 5;
// pc = &c;
// printf("Memory Address of C:%p\n", &c);
// printf("Memory Address of PC: %p\n",&pc );
// printf("Value of C:%i", c);




char *sub = substring;
printf("Value of substring: %s\n",sub);
printf("Memory Address of substring%p", &substring);

}


void main2(){

    char send_msg[15];
    memset(send_msg, 0x00, sizeof(send_msg));
        printf("\nType a command: \n");
        fgets(send_msg, sizeof(send_msg), stdin);

        printf("Send_MSG:%s", send_msg);

        char *firstWord = strtok(send_msg, " ");
        // firstWord = strtok(send_msg, " ");
        printf("FirstWord:%s\n", firstWord);
        char *secondWord = strtok(NULL, " ");
        printf("SecondWord:%s\n", secondWord);

        char secondWordnp[10];
        strcpy(secondWordnp, secondWord);
        char *p = secondWordnp[0];
        printf("SecondWordnp:%s", p);
}

int main(){

    main2();

    char word[4];
    strcpy(word, "abc");
    pointers(word);
    return 0;
}


/*
void main (int argc, char *argv [])
{
    char *message;
    
    message = get_message ();
    
    printf ("%s\n", message); //this returns output of: H

    // free( message );

    
} */

/*
int main()
{


    
    // char *returned_str = getSecondWord();
    // char *message;
    // message = get_message();
    // printf("%c", returned_str);
    /*
    fork();
    if(fork() == 0) {
        printf("Hello World! \n");
    } else {
        printf("Hello World! \n");
    } */

// split();

    

//This reads the dictionary and prints it! WHOO WHOO. 
    /*
    char currentLine[100];
    FILE *dictionary;
    if ((dictionary = fopen("/home/kevin/Desktop/TLM/dictionary.txt", "r")) == NULL)
    {
        printf("Error opening file. Problem with path");
        return;
    }
    while (fgets((currentLine), sizeof(currentLine), dictionary) != NULL)
    {
        printf("%s", currentLine); 
    }
    */   


    // char msg[75] = "Hello World This is Johnny Boi";
    // const char * delim = " ";
    // char * token = strtok(msg, delim);
    // printf("%s", token);
//}*/
