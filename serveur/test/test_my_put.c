#include "../src/my_put.c"
#include <criterion/criterion.h>
#include <string.h>

Test(my_put, success_request) {
  int client_sock = 0;
  const char* request = "Content-Length: 11\r\n\r\nhello world";

  char* content_type = my_put(request, client_sock);
  cr_assert_str_eq(content_type, request);
}