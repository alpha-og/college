#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define IP_ADDRESS "127.0.0.1"
#define PORT 8000
#define BUFFER_SIZE 1024

int main() {
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);
  int client_socket; // socket to store accepted connection's client socket fd

  struct sockaddr_in server_addr;
  socklen_t server_addr_len = sizeof(server_addr);
  memset(&server_addr, 0, server_addr_len);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
  server_addr.sin_port = htons(PORT);

  if (bind(server_socket, (struct sockaddr *)&server_addr, server_addr_len) <
      0) {
    perror("ERROR (bind)");
    exit(EXIT_FAILURE);
  }

  if (listen(server_socket, 5) < 0) {
    perror("ERROR (listen)");
    exit(EXIT_FAILURE);
  }

  printf("LISTENING on %s:%d\n", IP_ADDRESS, PORT);

  struct sockaddr_in client_addr;
  socklen_t client_addr_len = sizeof(client_addr);
  char client_ip_address[INET_ADDRSTRLEN] = {0};

  char buffer[BUFFER_SIZE] = {0};
  int bytes_received = 0;

  while (1) {
    memset(&client_addr, 0, client_addr_len);
    memset(&client_ip_address, 0, INET_ADDRSTRLEN);
    client_socket = -1;

    if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr,
                                &client_addr_len)) < 0) {
      perror("ERROR (accept)");
      continue;
    }

    if (inet_ntop(AF_INET, &client_addr.sin_addr, client_ip_address,
                  INET_ADDRSTRLEN) == NULL) {
      perror("ERROR (inet_pton)");
    }

    printf("ACCEPTED connection request from %s:%d", client_ip_address,
           ntohs(client_addr.sin_port));

    int should_disconnect = 0;

    while (!should_disconnect) {
      if ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0)) < 0) {
        perror("ERROR (recv)");
        should_disconnect = 1;
        continue;
      }

      buffer[bytes_received] = '\0';

      if (strcmp(buffer, "\\q") == 0) {
        should_disconnect = 1;
        continue;
      }

      if (send(client_socket, buffer, BUFFER_SIZE, 0) < 0) {
        perror("ERROR (send)");
        continue;
      }
    }

    close(client_socket);
  }

  return EXIT_SUCCESS;
}
