#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define IP_ADDRESS "127.0.0.1"
#define PORT 8000

int main() {
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket < 0) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in server_addr;
  socklen_t server_addr_len = sizeof(server_addr);
  memset(&server_addr, 0, server_addr_len);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
  server_addr.sin_port = htons(PORT);

  if (connect(client_socket, (struct sockaddr *)&server_addr, server_addr_len) <
      0) {
    perror("connect");
    exit(EXIT_FAILURE);
  }

  printf("Connected to %s:%d\n", IP_ADDRESS, PORT);

  int should_quit = 0;
  char buffer[BUFFER_SIZE] = {0};
  char input[BUFFER_SIZE] = {0};
  int bytes_read = 0;

  while (!should_quit) {
    printf("You >> ");
    if (fgets(buffer, BUFFER_SIZE - 1, stdin) == NULL) {
      break;
    }

    strncpy(input, buffer, BUFFER_SIZE);
    input[strcspn(input, "\n")] = '\0';

    if (strcmp(input, "\\q") == 0) {
      should_quit = 1;
      continue;
    }
    if (send(client_socket, buffer, BUFFER_SIZE, 0) < 0) {
      perror("ERROR (send)");
      continue;
    }
    if ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE, 0)) < 0) {
      perror("ERROR (recv)");
      continue;
    }
    buffer[bytes_read] = '\0';
    printf("(Server)>> %s", buffer);
  }

  return EXIT_SUCCESS;
}
