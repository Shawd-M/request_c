// // #include "../include/my_header.h"
// #include "../src/my_head.c"
// #include <criterion/criterion.h>
// #include <stdio.h>
// #include <string.h>
// #include <unistd.h>

// #define BUFFER_SIZE 2048

// char* get_sent_message(int client_socket)
// {
//   static char buffer[BUFFER_SIZE];
//   memset(buffer, 0, BUFFER_SIZE);

//   int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
//   if (bytes_received == 0)
//   {
//     return NULL;
//   }

//   return buffer;
// }

// Test(my_head, index_html) {
//   int client_sock = 0;
//   char url[] = "index.html";
//   my_head(url, client_sock);
  
//   char content_type[20];
//   sprintf(content_type, "Content-Type: %s\r\n\r\n", "text/html");
//   char response[BUFFER_SIZE];
//   sprintf(response, "HTTP/1.1 200 OK\r\n%s", content_type);
//   cr_assert_str_eq(response, get_sent_message(client_sock));
// }

// Test(my_head, index_json) {
//   int client_sock = 0;
//   char url[] = "index.json";
//   my_head(url, client_sock);
  
//   char content_type[20];
//   sprintf(content_type, "Content-Type: %s\r\n\r\n", "application/json");
//   char response[BUFFER_SIZE];
//   sprintf(response, "HTTP/1.1 200 OK\r\n%s", content_type);
//   cr_assert_str_eq(response, get_sent_message(client_sock));
// }
