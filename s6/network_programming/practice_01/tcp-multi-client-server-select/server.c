#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8000
#define MAX_CLIENTS 10
#define BACKLOG 5
#define BUFFER_SIZE 1024

struct Client {
  int socket;
  struct sockaddr_in addr;
  socklen_t addr_len;
};

int main() {
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in server_addr;
  socklen_t server_addr_len = sizeof(server_addr);
  memset(&server_addr, 0, server_addr_len);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(server_socket, (struct sockaddr *)&server_addr, server_addr_len) <
      0) {
    perror("ERROR (bind)");
    exit(EXIT_FAILURE);
  }

  if (listen(server_socket, BACKLOG) < 0) {
    perror("ERROR (listen)");
    exit(EXIT_FAILURE);
  }
  printf("[INFO] Server listening on %d\n", PORT);

  struct Client *clients[MAX_CLIENTS] = {NULL};

  fd_set read_fds;
  int max_fd = server_socket;
  int bytes_read = 0;
  char buffer[BUFFER_SIZE] = {0};

  while (1) {
    FD_ZERO(&read_fds);
    FD_SET(server_socket, &read_fds);

    for (int i = 0; i < MAX_CLIENTS; i++) {
      if (clients[i] != NULL) {
        FD_SET(clients[i]->socket, &read_fds);
        if (clients[i]->socket > max_fd) {
          max_fd = clients[i]->socket;
        }
      }
    }

    if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) < 0) {
      perror("ERROR (select)");
      exit(EXIT_FAILURE);
    }

    if (FD_ISSET(server_socket, &read_fds)) {
      struct Client *client = (struct Client *)calloc(1, sizeof(struct Client));
      client->addr_len = sizeof(client->addr);
      if ((client->socket =
               accept(server_socket, (struct sockaddr *)&(client->addr),
                      &(client->addr_len))) < 0) {
        perror("ERROR (accept)");
        continue;
      }

      char ip_addr[INET_ADDRSTRLEN] = {0};
      if (inet_ntop(AF_INET, &client->addr.sin_addr, ip_addr,
                    INET_ADDRSTRLEN) == NULL) {
        perror("[ERROR] (inet_ntop)");
      }

      printf("[INFO] Accepted connection request from %s:%d\n", ip_addr,
             ntohs(client->addr.sin_port));
      for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i] == NULL) {
          clients[i] = client;
          break;
        }
      }
    }

    for (int i = 0; i < MAX_CLIENTS; i++) {
      if (!(clients[i] != NULL && FD_ISSET(clients[i]->socket, &read_fds)))
        continue;
      if ((bytes_read = recv(clients[i]->socket, buffer, BUFFER_SIZE, 0)) <=
          0) {
        if (bytes_read < 0) {
          perror("ERROR (recv)");
          continue;
        } else {
          printf("[DISCONNECTED] client %d\n",
                 ntohs(clients[i]->addr.sin_port));
          free(clients[i]);
          clients[i] = NULL;
          continue;
        }
      }

      for (int j = 0; j < MAX_CLIENTS; j++) {
        if (i == j || clients[j] == NULL)
          continue;
        if (send(clients[j]->socket, buffer, BUFFER_SIZE, 0) < 0) {
          perror("ERROR (send)");
          continue;
        }
      }
    }
  }

  close(server_socket);

  return EXIT_SUCCESS;
}
