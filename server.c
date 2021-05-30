/*
 * TEC, Cartago, Escuela de Ingeniería en Computación, Principios de Sistemas Operativos
 * Proyecto: TriviaCR
 * Abraham Meza Vega, 2018168174
 * Lindsay Morales Bonilla, 2018077301
 * 05/06/2021, I Semestre 2021, Prof. Esteban Arias Méndez
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <arpa/inet.h>
#include <string.h>
#include "CLI/interface.h"

int main(){
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    int result;
    
    char text[100];
    char logName[100];
    char log[1024];
    char intConversion[100];

    time_t now = time(NULL);

    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    struct tm *t = localtime(&now);

    fd_set readfds, testfds;
    FILE* currentLog;

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(3102);
    server_len = sizeof(server_address);
    
    strftime(text, sizeof(text) - 1, "%Y-%m-%d-%H-%M", t);

    strcpy(logName, "logs/");
    strcat(logName, text);
    strcat(logName, "_log.txt");

    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
    listen(server_sockfd, 5);

    FD_ZERO(&readfds);
    FD_SET(server_sockfd, &readfds);

    while(1) {
        char ch;
        int fd;
        int nread;

        testfds = readfds;

        now = time(NULL);
        t = localtime(&now);
        strftime(text, sizeof(text) - 1, "%Y-%m-%d %H:%M", t);

        strcpy(log, "[");
        strcat(log, text);
        strcat(log, "] server running\n");

        currentLog = fopen(logName, "a+");
        fputs(log, currentLog);
        fclose(currentLog);

        result = select(FD_SETSIZE, &testfds, (fd_set *)0, (fd_set *)0, (struct timeval *) 0);

        if(result < 1) {
            now = time(NULL);
            t = localtime(&now);
            strftime(text, sizeof(text) - 1, "%Y-%m-%d %H:%M", t);
            sprintf(intConversion,"%d",result);

            strcpy(log, "[");
            strcat(log, text);
            strcat(log, "] server failed with code: ");
            strcat(log, intConversion);
            strcat(log, "\n");
            
            currentLog = fopen(logName, "a+");
            fputs(log, currentLog);
            fclose(currentLog);

            exit(1);
        }
        
        for(fd = 0; fd < FD_SETSIZE; fd++) {
            if(FD_ISSET(fd,&testfds)) {
                if(fd == server_sockfd) {
                    client_len = sizeof(client_address);
                    client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);

                    FD_SET(client_sockfd, &readfds);

                    now = time(NULL);
                    t = localtime(&now);
                    strftime(text, sizeof(text) - 1, "%Y-%m-%d %H:%M", t);
                    sprintf(intConversion,"%d",client_sockfd);

                    strcpy(log, "[");
                    strcat(log, text);
                    strcat(log, "] adding client on fd: ");
                    strcat(log, intConversion);
                    strcat(log, "\n");
                    
                    currentLog = fopen(logName, "a+");
                    fputs(log, currentLog);
                    fclose(currentLog);
                } else {
                    ioctl(fd, FIONREAD, &nread);

                    if(nread == 0) {
                        close(fd);
                        FD_CLR(fd, &readfds);

                        now = time(NULL);
                        t = localtime(&now);
                        strftime(text, sizeof(text) - 1, "%Y-%m-%d %H:%M", t);
                        sprintf(intConversion,"%d",fd);

                        strcpy(log, "[");
                        strcat(log, text);
                        strcat(log, "] removing client on fd: ");
                        strcat(log, intConversion);
                        strcat(log, "\n");
                        
                        currentLog = fopen(logName, "a+");
                        fputs(log, currentLog);
                        fclose(currentLog);
                    } else {
                        read(fd, &ch, 1);
                        sleep(5);

                        now = time(NULL);
                        t = localtime(&now);
                        strftime(text, sizeof(text) - 1, "%Y-%m-%d %H:%M", t);
                        sprintf(intConversion,"%d",fd);

                        strcpy(log, "[");
                        strcat(log, text);
                        strcat(log, "] serving client on fd: ");
                        strcat(log, intConversion);
                        strcat(log, "\n");
                        
                        currentLog = fopen(logName, "a+");
                        fputs(log, currentLog);
                        fclose(currentLog);

                        ch++;
                        write(fd, &ch, 1);
                    }
                }
            }
        }
    }
}
