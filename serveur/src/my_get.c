#include "../include/my_header.h"

const char* get_content_type(char* extension) {
  if (strcmp(extension, ".html") == 0 || strcmp(extension, ".htm") == 0) {
    return "text/html";
  } else if (strcmp(extension, ".json") == 0) {
    return "application/json";
  } else if (strcmp(extension, ".txt") == 0) {
    return "text/plain";
  } else if (strcmp(extension, ".jpeg") == 0 || strcmp(extension, ".jpg") == 0) {
    return "image/jpeg";
  } else if (strcmp(extension, ".png") == 0) {
    return "image/png";
  } else if (strcmp(extension, ".txt") == 0) {
    return "text/plain";
  } else {
    return "application/octet-stream";
  }
}

void* send_file(int client_sock, char* file_path, const char* content_type) {
  // ouverture du fichier demandé dans l'URL
  FILE* file = fopen(file_path, "r");
  if (file == NULL) {
    // fichier non trouvé, envoi d'un code de statut "Not Found" au client
    const char* message = "HTTP/1.1 404 Not Found\r\n\r\n";
    send(client_sock, message, strlen(message), 0);
    return NULL;
  }

  // envoi du fichier au client
  char response[BUFFER_SIZE];
  sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\n\r\n", content_type);
  send(client_sock, response, strlen(response), 0);
  int n;
  while ((n = fread(response, 1, BUFFER_SIZE, file)) > 0) {
    send(client_sock, response, n, 0);
  }

  fclose(file);

  return NULL;
}

void* my_get(char* url, int client_sock) {
  // détermination du type MIME du fichier
  char* extension = strrchr(url, '.');
  // prend index.html par défaut si aucun nom de fichier n'est spécifié
  if (strcmp(url, "/") == 0) {
    extension = ".html";
    url = "/index.html";
  }
  if (extension == NULL) {
    extension = ".html";
    url = "/404.html";
  }

  const char *content_type = get_content_type(extension);

  char file_path[120];
  sprintf(file_path, "web/%s", url);
  send_file(client_sock, file_path, content_type);
  return NULL;
}
