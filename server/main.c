#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

//#define PORT 8080

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


void sendHtmlResponse(int clientSocketFD) {
    const char *responseBody = 
        "<!DOCTYPE html>\r\n"
        "<html lang=\"en\">\r\n"
        "<head><meta charset=\"UTF-8\"><title>Welcome</title></head>\r\n"
        "<body><h1>Hello, welcome to my page!</h1></body>\r\n"
        "</html>\r\n";
    
    // Calculate the content length dynamically
    int contentLength = strlen(responseBody);

    char response[1024];
    snprintf(response, sizeof(response),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n", contentLength);

    // Send the headers
    send(clientSocketFD, response, strlen(response), 0);
    // Send the body of the response
    send(clientSocketFD, responseBody, contentLength, 0);
}


int main(){
    //making socket and getting the file descreptor for serverSocket
    int serverSockedfd = socket(AF_INET, SOCK_STREAM, 0);

    //making a socketAddress haddled by a function
    struct sockaddr_in *serverAddress = createIPv4address("", 2000);

    //binding our server to the socket
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

    printf("response was %s\n", buffer);

    while(true){
        ssize_t amountRecived = recv(clientSocketFD, buffer , 1024, 0);

        if(amountRecived > 0){
            buffer[amountRecived] = 0;
            printf("response was %s\n", buffer);
            sendHtmlResponse(clientSocketFD);
            break;
        }

        if(amountRecived == 0){
            break;
        }

        //sendHtmlResponse(clientSocketFD);
    }

    close(clientSocketFD);
    shutdown(serverSockedfd, SHUT_RDWR);

}