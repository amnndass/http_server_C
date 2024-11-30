#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080


int main(){

    //this sockect() return a file descriptor
    //1-> ipv4; 2-> tcp; 3-> osi layer thingy
    int socketfd = socket(AF_INET,SOCK_STREAM, 0);
    
    //to use connect() we need a pointer to socketaddress and for that we create import sockaddr_in and fill its memebers
    struct sockaddr_in address;

    //making a pointer to abstract ip address
    char *ip = "127.0.0.1";

    //some technical jargon, we need to convert above ip to another form --> inet_presentaionToNetwork does this
    inet_pton(AF_INET, ip, &address.sin_addr.s_addr);

    //defining the member of structure address

    //due to some technical jargon we cannot directly assign 80 as a port we have to convert it into an unsigned short integer
    //for this we use hostTONetwoekShort htons() in which we pass 80 or any port number
    address.sin_port = htons(2000);
    address.sin_family = AF_INET;
    //address.sin_addr.s_addr;
    

 
    //this connect function conncets our socket to a port (maybe)
    //returns a result
    int result = connect(socketfd, (struct sockaddr *)&address, sizeof address);
    
    //checking if connection was successfull
    if(result == 0){
        printf("connection was successfull\n");
    }else{
        printf("connection failed");
    }


    //now the connection is sucessful we need to send a http request with send()

    char *message;
    message = "GET \\ HTTP/1.1\r\nHost:google.com\r\n\r\n";
    send(socketfd, message, strlen(message), 0);

    char buffer[1024];
    recv(socketfd, buffer , 1024, 0);

    printf("response was %s\n", buffer);
}