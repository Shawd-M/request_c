#include "../include/my_header.h"

char* my_put(const char* buffer, int client_sock) {
  // search for "Content-Length" header line
  const char* content_length_header = "Content-Length: ";
  char* content_length_line = strstr(buffer, content_length_header);
  if (content_length_line == NULL) {
    // "Content-Length" line not found, send "Bad Request" status code to client
    const char* message = "HTTP/1.1 400 Bad Request\r\n\r\n";
    send(client_sock, message, strlen(message), 0);
    return NULL;
  }

  // retrieve the value of "Content-Length" line
  int content_length = atoi(content_length_line + strlen(content_length_header));
  printf("Content-Length: %d\n", content_length);

  // receive the request body
  char *p = strstr(buffer, "\r\n\r\n");
  if (p != NULL) {
    p += 4;
    printf("Parameters: %s\n", p);
  }

  // send "OK" status code to client
  const char* message = "HTTP/1.1 200 OK\r\n\r\n";
  send(client_sock, message, strlen(message), 0);

  return buffer;
}
