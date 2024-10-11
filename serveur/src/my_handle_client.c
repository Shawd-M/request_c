#include "../include/my_header.h"

void close_socket(int client_sock)
{
  // Fermeture de l'écriture sur le socket
  shutdown(client_sock, SHUT_WR);

  // // Fermeture complète du socket
  close(client_sock);
}

void my_extract_header_info(char* buffer, char* method, char* url, char* version) {
  sscanf(buffer, "%s %s %s", method, url, version);
}

int my_receive_header(int client_sock, char* buffer) {
  int received = recv(client_sock, buffer, BUFFER_SIZE - 1, 0);
  if (received < 0) {
    perror("Erreur lors de la réception du header");
    return received;
  }

  buffer[received] = '\0';
  return received;
}

void my_handle_invalid_method(int client_sock) {
  const char* message = "HTTP/1.1 405 Method Not Allowed\r\n\r\n";
  send(client_sock, message, strlen(message), 0);
}

void my_handle_method(char* method, char* url, char* buffer, int client_sock) {
  if (strcmp(method, "GET") == 0) {
    my_get(url, client_sock);
  }
  if (strcmp(method, "HEAD") == 0) {
    my_head(url, client_sock);
  }
  if (strcmp(method, "POST") == 0) {
    my_post(buffer, client_sock);
  }
  if (strcmp(method, "PUT") == 0) {
    my_put(buffer, client_sock);
  }
  if (strcmp(method, "DELETE") == 0) {
    my_delete(url, client_sock);
  }
}

void* my_handle_client(void* arg)
{
  intptr_t client_sock = (intptr_t)arg;
  int client_sock_int = (int)client_sock;

  // réception du header du client
  char buffer[BUFFER_SIZE];
  int received = my_receive_header(client_sock, buffer);
  if (received < 0) {
    perror("Erreur lors de la réception du header");
    return NULL;
  }

  // ajout du caractère de fin de chaîne
  buffer[received] = '\0';

  // extraction de la méthode, de l'URL et de la version HTTP du header
  char method[10];
  char url[100];
  char version[10];
  my_extract_header_info(buffer, method, url, version);

  // vérification de la méthode HTTP
  if (strcmp(method, "GET") != 0 && strcmp(method, "POST") != 0 && strcmp(method, "PUT") != 0 && strcmp(method, "DELETE") != 0 && strcmp(method, "HEAD") != 0)
  {
    my_handle_invalid_method(client_sock);
    close_socket(client_sock);
    return NULL;
  }

  printf("\nMéthode : %s\n", method);
  printf("URL : %s\n", url);
  printf("Version HTTP : %s\n", version);

  my_handle_method(method, url, buffer, client_sock);

  close_socket(client_sock);

  return NULL;
}
