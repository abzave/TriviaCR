#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "logging.h"
#include "../users/userManager.h"

void handleCommand(char* command, int fd);
void logUser();

int main(){
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    int result;

    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    fd_set readfds, testfds;
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(3102);
    server_len = sizeof(server_address);

    prepareNewLog();
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
    listen(server_sockfd, 5);

    FD_ZERO(&readfds);
    FD_SET(server_sockfd, &readfds);

    while(1) {
        int fd;
        int nread;

        testfds = readfds;

        logText("server running");
        result = select(FD_SETSIZE, &testfds, (fd_set *)0, (fd_set *)0, (struct timeval *) 0);

        if(result < 1) {
            logWithInt("server failed with code: %d", result);
            exit(1);
        }
        
        for(fd = 0; fd < FD_SETSIZE; fd++) {
            if(FD_ISSET(fd,&testfds)) {
                if(fd == server_sockfd) {
                    client_len = sizeof(client_address);
                    client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
                    FD_SET(client_sockfd, &readfds);

                    logWithInt("adding client on fd: %d", client_sockfd);
                } else {
                    ioctl(fd, FIONREAD, &nread);

                    if(nread == 0) {
                        close(fd);
                        FD_CLR(fd, &readfds);

                        logWithInt("removing client on fd: %d", fd);
                    } else {
                        char message[1024];
                        read(fd, message, 6);

                        logWithInt("serving client on fd: %d", fd);
                        handleCommand(message, fd);
                    }
                }
            }
        }
    }
}

/**
  * Handle the actions the server should take on the received input by the client
  * @param command {char*}: String recieved from the client
  * @param fd {int}: Socket where the client is served
  */
void handleCommand(char* command, int fd) {
    if (strcmp(command, "login") == 0) {
        logUser(fd);
    }
}

/**
  * Performs the login for a user. Sends to the client a request for the username and
  *   reads the value returned as username
  * @param fd {int}: Socket where the client is served
  */
void logUser(int fd) {
    char message[1024];
    char user[128];
    logWithInt("Login client on fd: %d", fd);

    strcpy(message, "User: ");
    write(fd, message, 7);
    read(fd, user, 8);

    int index = addUser(user);
    logWithInt("User added in position: %d", index);
}