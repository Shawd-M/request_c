#include "../src/my_delete.c"
#include <criterion/criterion.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

Test(my_delete, returns_200_OK_when_file_found)
{
  int pipes[2];
  socketpair(AF_UNIX, SOCK_STREAM, 0, pipes);

  int client_sock = pipes[1];
  char url[] = "/index.html";

  my_delete(url, client_sock);

  char response[20];
  int n = recv(pipes[0], response, 20, 0);
  if (n == -1) {
      perror("recv");
      exit(EXIT_FAILURE);
  }
  response[n] = '\0';
  cr_assert_str_eq(response, "HTTP/1.1 200 OK\r\n\r\n");
}