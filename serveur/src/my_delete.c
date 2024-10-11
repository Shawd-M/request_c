#include "../include/my_header.h"

void my_delete(char *url, int client_sock)
{
  // ouverture du fichier demandé dans l'URL
  char file_path[120];
  sprintf(file_path, "web/%s", url);
  FILE* file = fopen(file_path, "r");

  // affciher les arguements delete (ca ne delete pas le fichier)
  printf("DELETE : %s\n", url);

  const char* message = "HTTP/1.1 200 OK\r\n\r\n";
  send(client_sock, message, strlen(message), 0);

  fclose(file);
}
