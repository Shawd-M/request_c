#ifndef MY_HEADER_H
#define MY_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/stat.h>
#include <criterion/criterion.h>

/* Constantes utiles */
#define SERVER_MAX_CON    10
#define BUFFER_SIZE       4096

/* Déclaration des fonctions */
int my_socket(char *host, int port);
void* my_handle_client(void* arg);
void* my_get(char *url, int client_sock);
void* my_head(char *url, int client_sock);
char* my_post(const char* buffer, int client_sock);
char* my_put(const char* buffer, int client_sock);
void my_delete(char *url, int client_sock);

/* Déclaration d'une structure */

#endif
