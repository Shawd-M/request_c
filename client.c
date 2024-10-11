#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

// déclaration de la fonction
int word_in_buffer(const char* buffer, const char* word) {
  // vérifie si le mot est présent dans le tampon
  return strstr(buffer, word) != NULL;
}

int main(int argc, char** argv)
{
  // vérifier que le nombre d'arguments est correct
  if (argc < 5 || argc > 6)
  {
    printf("Usage: %s host port method url\n", argv[0]);
    return 1;
  }

  // récupération de l'hôte, du port, de la méthode et de l'URL à partir des arguments
  char* host = argv[1];
  int port = atoi(argv[2]);
  char* method = argv[3];
  char* url = argv[4];
  char* body = NULL;

  // retrieve the body if it is provided
  if (argc == 6)
  {
    body = argv[5];
  }

  // création de la socket
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
  {
    perror("Erreur lors de la création de la socket");
    exit(EXIT_FAILURE);
  }

  // configuration de l'adresse du serveur
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  if (inet_pton(AF_INET, host, &server_addr.sin_addr) <= 0)
  {
    perror("Erreur lors de la conversion de l'adresse");
    exit(EXIT_FAILURE);
  }

  // connexion au serveur
  if (connect(sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0)
  {
    perror("Erreur lors de la connexion au serveur");
    exit(EXIT_FAILURE);
  }

  printf("Connexion au serveur réussie !\n");

  // envoi d'un header au serveur avec la méthode et l'URL en argument
  char header[100];

  // prepare the request body as a string
  // char *body = "{\"key\":\"value\"}";

  // determine the length of the request body and the media type
  if (strcmp(method, "POST") == 0 || strcmp(method, "PUT") == 0) {
    int body_length = strlen(body);
    char *content_type = "application/json";

    sprintf(header, "%s %s HTTP/1.1\r\nContent-Length: %d\r\nContent-Type: %s\r\n\r\n", method, url, body_length, content_type);
  }
  else
  {
    sprintf(header, "%s %s HTTP/1.1\r\n\r\n", method, url);
  }

  // send the HTTP header
  send(sock, header, strlen(header), 0);

  if (strcmp(method, "POST") == 0 || strcmp(method, "PUT") == 0) {
    // send the request body
    send(sock, body, strlen(body), 0);
  }

  // set the receive timeout to 3 seconds
  struct timeval timeout;
  timeout.tv_sec = 5;
  timeout.tv_usec = 0;

  if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) < 0)
  {
    perror("Error setting receive timeout");
    close(sock);
    return 0;
  }

  // réception de la réponse du serveur
  char buffer[BUFFER_SIZE];

  // réception de la réponse du serveur
  int received;
  while ((received = recv(sock, buffer, BUFFER_SIZE - 1, 0)) > 0) {
    // ajout du caractère de fin de chaîne
    buffer[received] = '\0';

    // affichage de la réponse
    printf("%s", buffer);
    fflush(stdout);

    // vérification de la chaîne "FIN DE LA TRANSMISSION"
    if (word_in_buffer(buffer, "FIN DE LA TRANSMISSION") > 0) {
      break;  // sortie de la boucle
    }
  }

  // if (received == 0) {
  //   printf("Connexion fermée par le serveur\n");
  // } else if (received < 0) {
  //   perror("Erreur lors de la réception de la réponse");
  //   return 1;
  // }

  // fermeture de la socket
  close(sock);

  return 0;
}
