#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
  const char server_ip[BUFFER_SIZE] = "127.0.0.1";
  int port = 8080;

  int sock_fd;
  sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

  int should_quit = 0;
  char buffer[BUFFER_SIZE];
  ssize_t bytes;
  socklen_t addr_len = sizeof(server_addr);

  while (!should_quit) {
    memset(buffer, 0, sizeof(buffer));
    fputs("(you) >> ", stdout);
    if (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
      buffer[strcspn(buffer, "\n")] = '\0';
      if (strcmp(buffer, "\\q") == 0) {
        fprintf(stdout, "Exiting...\n");
        should_quit = 1;
      }
      sendto(sock_fd, buffer, 22, 0, (struct sockaddr *)&server_addr,
             sizeof(server_addr));
    }

    memset(buffer, 0, sizeof(buffer));
    bytes = recvfrom(sock_fd, buffer, sizeof(buffer) - 1, 0,
                     (struct sockaddr *)&server_addr, &addr_len);
    buffer[bytes] = '\0';
    fprintf(stdout, "(server) >> %s\n", buffer);
  }

  exit(0);
}
