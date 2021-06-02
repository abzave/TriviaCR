/*
 * TEC, Cartago, Escuela de Ingeniería en Computación, Principios de Sistemas Operativos
 * Proyecto: TriviaCR
 * Abraham Meza Vega, 2018168174
 * Lindsay Morales Bonilla, 2018077301
 * 05/06/2021, I Semestre 2021, Prof. Esteban Arias Méndez
*/

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

#define TRANSMITTED_BYTES       1
#define DIFFERENT_CONNECTIONS   2
#define TRANSMITTED_FILES       3
#define QUESTIONS_STATS         4
#define RANKING                 5
#define EXIT_MENU               6

void handleCommand(char* command, int fd);
void logUser();
void serverStatisticsMenu();
int gatherStat(char *stat);

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
    } else if (strcmp(command, "login") == 0) {
        serverStatisticsMenu();
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

void serverStatisticsMenu() {
    logText("Acceso a estadisticas del servidor");

    char* options[6];
    options[0] = "Cantidad de bytes transmitidos";
    options[1] = "Cantidad de conexiones distintas realizadas";
    options[2] = "Cantidad de archivos transmitidos";
    options[3] = "Estadísticas de preguntas";
    options[4] = "Ranking de jugadores";
    options[5] = "Salir";

    int exitMenu = 0;
    int option = 0;
    FILE *serverGlobalStats;
    serverGlobalStats = fopen("globalStats.txt", "r");

    while (!exitMenu) {
        option = showMenu(options, 6);
        switch(option) {
            case TRANSMITTED_BYTES: {
                logText("Consulta para bytes transmitidos");
                int transmitedBytes = gatherStat("transmited_bytes");
                printf("La cantidad de bytes transmitidos por el servidor han sido %d\n\n", transmitedBytes);
                break;
            }
            case DIFFERENT_CONNECTIONS: {
                logText("Consulta para conexiones distintas");
                int differentConnections = gatherStat("different_connections");
                printf("La cantidad de conexiones distintas han sido %d\n\n", differentConnections);
                break;
            }
            case TRANSMITTED_FILES: {
                logText("Consulta para archivos transmitidos");
                int transmitedFiles = gatherStat("transmited_files");
                printf("La cantidad de archivos transmitidos por el servidor han sido %d\n\n", transmitedFiles);
                break;
            }
            case QUESTIONS_STATS: {
                logText("Consulta para estadisticas de preguntas");
                int totalQuestions = gatherStat("played_questions");
                int correctAnswers = gatherStat("correct_answers");
                int incorrectAnswers = totalQuestions - correctAnswers;
                printf("Cantidad de preguntas jugadas %d\n", totalQuestions);
                printf("Cantidad de preguntas contestadas correctamente %d (%f %%)\n", correctAnswers, ((float)correctAnswers/(float)totalQuestions)*100);
                printf("Cantidad de preguntas contestadas incorrectamente %d (%f %%)\n\n", incorrectAnswers, ((float)incorrectAnswers/(float)totalQuestions)*100);
                break;
            }
            case RANKING: {
                logText("Consulta para ranking");
                //open users.csv
                break;
            }
            case EXIT_MENU: {
                logText("Menu de estadisticas cerrado");
                exitMenu = 1;
                break;
            }
        }
    }
}

int gatherStat(char *stat) {
    FILE *serverStatsFile = fopen("globalStats.csv","r");
    char line[256];

    while(fgets(line, sizeof(line), serverStatsFile)) {
        char *splittedLine;
        splittedLine = strtok(line,",");
        if (strcmp(splittedLine,stat) == 0) {
            splittedLine = strtok(NULL, ",");
            int statValue;
            sscanf(splittedLine, "%d", &statValue);
            return statValue;
        }
    }

    return 0;
}
