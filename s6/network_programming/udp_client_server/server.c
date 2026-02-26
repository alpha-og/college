#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
  int port = 8080;

  int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(port);

  if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("bind");
    exit(1);
  }

  fprintf(stdout, "Server listening on port %d...\n", port);

  struct sockaddr_in client_addr;
  socklen_t addr_size = sizeof(client_addr);
  ssize_t bytes;
  char buffer[BUFFER_SIZE];
  char response[BUFFER_SIZE];
  char client_ip[INET_ADDRSTRLEN];
  int client_port;

  while (1) {
    bytes = recvfrom(sock_fd, buffer, sizeof(buffer) - 1, 0,
                     (struct sockaddr *)&client_addr, &addr_size);
    buffer[bytes] = '\0';
    inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, client_ip,
              sizeof(client_ip));

    client_port = ntohs(client_addr.sin_port);

    fprintf(stdout, "[%s:%d] |> %s\n", client_ip, client_port, buffer);

    snprintf(response, sizeof(response), "Received \"%s\"", buffer);

    sendto(sock_fd, response, 22, 0, (struct sockaddr *)&client_addr,
           addr_size);
  }
  close(sock_fd);
  exit(0);
}
