#include "../include/my_header.h"

void* my_head(char *url, int client_sock)
{
  // détermination du type MIME du fichier
  char* extension = strrchr(url, '.');
  char* content_type;
  printf("%s", extension);
  if (extension != NULL)
  {
    if (strcmp(extension, ".html") == 0 || strcmp(extension, ".htm") == 0)
    {
      content_type = "text/html";
    }
    else if (strcmp(extension, ".json") == 0)
    {
      content_type = "application/json";
    }
    else if (strcmp(extension, ".txt") == 0)
    {
      content_type = "text/plain";
    }
    else if (strcmp(extension, ".jpeg") == 0)
    {
      content_type = "image/jpeg";
    }
    else if (strcmp(extension, ".jpg") == 0)
    {
      content_type = "image/jpeg";
    }
    else if (strcmp(extension, ".png") ==  0)
    {
      content_type = "image/png";
    }
    else if (strcmp(extension, ".txt") == 0)
    {
      content_type = "text/plain";
    }
    else
    {
      content_type = "application/octet-stream";
    }
  }
  else
  {
    content_type = "application/octet-stream";
  }

  // ouverture du fichier demandé dans l'URL
  char file_path[120];
  sprintf(file_path, "web/%s", url);
  FILE* file = fopen(file_path, "r");
  if (file == NULL)
  {
    // fichier non trouvé, envoi d'un code de statut "Not Found" au client
    const char* message = "HTTP/1.1 404 Not Found\r\n\r\n";
    send(client_sock, message, strlen(message), 0);
    return NULL;
  }

  // envoi du header au client
  char response[BUFFER_SIZE];
  sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\n\r\n", content_type);
  send(client_sock, response, strlen(response), 0);
  return NULL;

  fclose(file);

  return NULL;
}
