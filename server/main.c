#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

struct sockaddr_in* createIPv4address(char *ip,int port ){
    struct sockaddr_in *address = malloc(sizeof(struct sockaddr_in));
    address->sin_family = AF_INET;
    address->sin_port = htons(port);

    if(strlen(ip) == 0){
        address->sin_addr.s_addr = INADDR_ANY;
    }else{
        inet_pton(AF_INET, ip, &address->sin_addr.s_addr);
    }

    return address;
}
 
int main(){
    int serverSockedfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in *serverAddress = createIPv4address("", 2000);

    int result = bind(serverSockedfd, (struct sockaddr *)serverAddress, sizeof(*serverAddress));

    if(result == 0){
        printf("server socket was bound successfully\n");
    }else{
        printf("binding failed");
    }

    int listenResult = listen(serverSockedfd, 10);

    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof (struct sockaddr_in);
    int clientSocketFD = accept(serverSockedfd,(struct sockaddr *)&clientAddress, &clientAddressSize);

    char buffer[1024];
    recv(clientSocketFD, buffer , 1024, 0);

    printf("response was %s\n", buffer);

}