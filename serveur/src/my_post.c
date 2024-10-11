#include "../include/my_header.h"

char* my_post(const char* buffer, int client_sock) {
  // chercher la ligne "Content-Length" dans le header
  const char* content_length_header = "Content-Length: ";
  char* content_length_line = strstr(buffer, content_length_header);
  if (content_length_line == NULL) {
    // ligne "Content-Length" non trouvée, envoi d'un code de statut "Bad Request" au client
    const char* message = "HTTP/1.1 400 Bad Request\r\n\r\n";
    send(client_sock, message, strlen(message), 0);
    return NULL;
  }

  // récupération de la valeur de la ligne "Content-Length"
  int content_length = atoi(content_length_line + strlen(content_length_header));
  printf("Content-Length: %d\n", content_length);

  // réception du corps de la requête
  char *p = strstr(buffer, "\r\n\r\n");
  if (p != NULL) {
    p += 4;
    printf("Parameters: %s\n", p);
  }

  // envoi d'un code de statut "OK" au client
  const char* message = "HTTP/1.1 200 OK\r\n\r\n";
  send(client_sock, message, strlen(message), 0);

  return buffer;
}
