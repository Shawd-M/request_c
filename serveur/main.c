#include "../include/my_header.h"

int main(int argc, char** argv)
{
  // vérifier que le nombre d'arguments est correct
  if (argc != 3)
  {
    printf("Usage: %s host port\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // récupération de l'hôte et du port à partir des arguments
  char* host = argv[1];
  int port = atoi(argv[2]);

  // création de la socket avec l'hôte et le port donnés en arguments
  int sock = my_socket(host, port);

  // boucle infinie pour écouter les connexions entrantes
  while (sock)
  {
    fprintf(stderr, "Serveur en mode ecoute:\n");
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // Initialisation de la liste de descripteurs de fichiers pour select
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(sock, &read_fds);

    // Attente d'une activité sur le socket
    int select_result = select(sock + 1, &read_fds, NULL, NULL, NULL);
    if (select_result < 0)
    {
      perror("Erreur lors de l'appel à select");
      continue;
    }

    // acceptation d'une connexion entrante
    int client_sock = accept(sock, (struct sockaddr*) &client_addr, &client_addr_len);
    if (client_sock < 0)
    {
      perror("Erreur lors de l'acceptation de la connexion");
      continue;
    }

    // traitement de la connexion client
    intptr_t client_sock_ptr = (intptr_t) client_sock;
    my_handle_client((void*) client_sock_ptr);
  }

  return 0;
}
