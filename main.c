//#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <sys/socket.h>
#include <unistd.h>

#include <winsock2.h>
#include <ws2tcpip.h>


#define PORT 8080


int main(){
    //this sockect() return a file descriptor
    int socketfd = socket(AF_INET,SOCK_STREAM, 0);
    
    //to use connect() we need a pointer to socketaddress and for that we create import sockaddr_in and fill its memebers
    struct sockaddr_in address;;

    address.sin_family = AF_INET;
    address.sin_port = 2000;
    address.

 
    //this connect function conncets our socket to a port (maybe)
    connect(socketfd, )
    
}