#include "../src/my_socket.c"
#include <criterion/criterion.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Success teste
Test(my_socket, test_success)
{
  int sock = my_socket("127.0.0.1", 8080);
  cr_assert_neq(sock, -1, "La socket n'a pas été créée correctement");

  close(sock);
}

// Hote null
Test(my_socket, test_failure)
{
  int sock = my_socket(NULL, 8080);
  cr_assert_eq(sock, -1, "La socket n'a pas retourné une erreur pour un hôte NULL");
}
