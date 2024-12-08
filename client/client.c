#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

//function to get ipv4 address structure 
struct sockaddr_in * getIPv4Address(char *ip, int port){

    //defining the structure of the address
    //first we dynamically allocate memory for address structure

    struct sockaddr_in *address = malloc(sizeof(struct sockaddr_in)); 
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    
    inet_pton(AF_INET, ip, &address->sin_addr.s_addr);

    //returning the pointer
    return address;
}

int main(){
    //defining the socket and getting the file descreptor
    int socketFD = socket(AF_INET, SOCK_STREAM, 0);

    //getting the structure of the ip address and port as required by connect()
    struct sockaddr_in *address = getIPv4Address("127.0.0.1", 2000);

    

    int result = connect(socketFD, (struct sockaddr *)address, sizeof(*address));

    //checking if socket is connected to the port
    if(result == 0){
        printf("connection was successful\n");
    }else{
        printf("skill issue");
        perror("connect");
        exit(EXIT_FAILURE);
    }

    free(address);
    close(socketFD);
}