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
    // Initialize Winsock
    WSADATA wsaData;
    int wsResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsResult != 0) {
        printf("WSAStartup failed with error %d\n", wsResult);
        return 1;
    }



    //this sockect() return a file descriptor
    int socketfd = socket(AF_INET,SOCK_STREAM, 0);
    
    //to use connect() we need a pointer to socketaddress and for that we create import sockaddr_in and fill its memebers
    struct sockaddr_in address;

    //making a pointer to abstract ip address
    char *ip = "142.250.31.100";

    //some technical jargon, we need to convert above ip to another form --> inet_presentaionToNetwork does this
    inet_pton(AF_INET, ip, &address.sin_addr.s_addr);

    //defining the member of structure address

    //due to some technical jargon we cannot directly assign 80 as a port we have to convert it into an unsigned short interger
    //for this we use hostTONetwoekShort htons() in which we pass 80 or any port number
    address.sin_port = htons(80);
    address.sin_family = AF_INET;
    //address.sin_addr.s_addr;
    

 
    //this connect function conncets our socket to a port (maybe)
    //returns a result
    int result = connect(socketfd, &address, sizeof address);
    
    //checking if connection was successfull
    if(result == 0){
        printf("connection was successfull\n");
    }else{
        printf("connection failed");
    }





    // Cleanup
    closesocket(socketfd);
    WSACleanup();
    return 0;
}