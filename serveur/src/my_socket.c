#include "../include/my_header.h"

/* la fonction crée une socket avec l'hôte et le port donnés en arguments */
int my_socket(char* host, int port)
{
  // création de la socket
  int client_sock, c;
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addr;

  if (host == NULL)
  {
    perror("host ne peut pas etre null");
    return -1;
  }
  if (sock == -1)
  {
    perror("Erreur lors de la création de la socket");
    return sock;
  }

  // configuration de l'adresse de l'hôte
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  inet_pton(AF_INET, host, &addr.sin_addr);

  // liaison de la socket à l'adresse et au port
  if ((bind(sock, (struct sockaddr*) &addr, sizeof(addr))) < 0)
  {
    perror("Erreur lors de la liaison de la socket");
    return -1;
  }

  // mise de la socket en mode d'écoute
  if ((listen(sock, SERVER_MAX_CON)) < 0)
  {
    perror("Erreur lors de la mise en écoute de la socket");
    return -1;
  }

  return sock;
}
